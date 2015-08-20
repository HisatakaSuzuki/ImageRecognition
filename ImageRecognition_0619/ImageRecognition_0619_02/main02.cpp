#include <iostream>
#include <opencv2\opencv.hpp>
#include "Timer.h"

//関数のプロトタイプ宣言
void sadTemplate(cv::InputArray tar, cv::InputArray tmp, cv::OutputArray res, int *minx, int *miny);

int main(int argc, const char * argv[]){
	cv::Mat tarimg = cv::imread("Dice.png");	//target画像ファイルの読み込み
	if (tarimg.empty())	//ファイルの読み込み失敗
	{
		std::cout << "tarファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
	cv::Mat tmpimg = cv::imread("DiceTmp1.png");	//tmp画像ファイルの読み込み
	if (tmpimg.empty())	//ファイルの読み込み失敗
	{
		std::cout << "tmpファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
	
	//2値画像化
    cv::Mat targray;
    //RGB画像をグレースケール化
	cv::cvtColor(tarimg,targray,CV_BGR2GRAY);
	//2値画像化
    cv::Mat tmpgray;
    //RGB画像をグレースケール化
	cv::cvtColor(tmpimg,tmpgray,CV_BGR2GRAY);

	//結果画像のサイズを計算
	int resrow = tarimg.rows - tmpimg.rows+1;
	int rescol = tarimg.cols - tmpimg.cols+1;
	cv::Mat resimg(resrow,rescol,CV_8UC1);	//マッチングの結果を保持する
	int minx, miny;	//点の位置を描画用に格納する
	
	//テンプレートマッチング
	Timer tm;	//処理時間計測用
	sadTemplate(targray,tmpgray,resimg,&minx,&miny);	//マッチング関数
	double time = tm.elapsed();	//処理時間ストップ
	std::cout << "経過時間は" << time << "かかりました。\n";

	//矩形描画
	cv::rectangle(tarimg,cv::Point(minx,miny),cv::Point(minx+tmpimg.rows,miny+tmpimg.cols),cv::Scalar(0,0,255),1,4);

	//画像の保存
	if(cv::imwrite("result.png", tarimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}

	return 0;
}

void sadTemplate(cv::InputArray tar, cv::InputArray tmp, cv::OutputArray res, int *minx, int *miny){
	//引数の入力をMatとして受け取る
	cv::Mat tarM = tar.getMat();	
	cv::Mat tmpM = tmp.getMat();
	cv::Mat resM = res.getMat();

	//sadが最小値のところがマッチングしたい箇所なので
	int minsad = std::numeric_limits<int>::max();	
	int sad = 0;  //各回のsadを格納
	int diff;	//sadに加算する前の作業変数
	int tarx,tary;	//目的のxy座標


	for(int y=0;y<tarM.rows - tmpM.rows;y++){
		for(int x=0;x<tarM.cols - tmpM.cols;x++){
			sad = 0;	//次の領域の計算の前に初期化
			//探索
			for(int yt = 0; yt < tmpM.rows; yt++){
				for(int xt = 0; xt < tmpM.cols; xt++){
					diff = (int)(tarM.at<uchar>(y+yt,x+xt) - tmpM.at<uchar>(yt,xt));
					if(diff < 0){  //負なら正に変換
						diff = -diff;
					}
					sad += diff;
					////残差逐次検定法
					if(sad > minsad){
						yt = tmpM.rows;	
						break;
					}
				}
			}

			//探索結果：sadが今までで最小なら
			if(sad < minsad){
				minsad = sad;	//最小値を更新
				//目的のxyを格納
				tarx = x;
				tary = y;
			}
		}
	}

	//outputに出力
	for(int y=0;y<resM.rows;y++){
		for(int x=0;x<resM.cols;x++){
			if(x==tarx && y==tary){
				resM.at<uchar>(y,x) = (uchar)0;
			}else{
				resM.at<uchar>(y,x) = (uchar)255;
			}
		}
	}
	std::cout << "最小値＝" << minsad << std::endl;
	std::cout << "最小点＝[" << tarx << ", " << tary << "]" <<  std::endl;
	*minx = tarx;
	*miny = tary;
}

