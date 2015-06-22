#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("Pentagons.png");	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}	
	//輪郭描画用の画像
	cv::Mat ans1 = img;	//全輪郭を赤で描画
	cv::Mat ans2 = img;	//最大を緑、最小を黄色で描画

	//RGB画像をグレースケール化
	cv::cvtColor(img,img,CV_BGR2GRAY);

	//輪郭の座標格納用
	std::vector< std::vector< cv::Point > > contours;
	//輪郭検出
	cv::findContours(img,contours,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//最大面積を緑色、最小面積を黄色で描画
	double area[6];	//各領域の面積格納
	for(int i=0;i<6;i++){
		area[i] = cv::contourArea(cv::Mat(contours[i]));
	}
	//最大最小の添え字を取得
	int max=0;		int min =0;
	//作業用配列
	double tmp[6];
	for(int i=0;i<6;i++){
		tmp[i] = area[i];
	}
	//最大領域の添え字
	for(int i=1;i<6;i++){
	    if(tmp[0]<=tmp[i]){
			tmp[0] = tmp[i];
			max = i;
		}	
	}

	//作業用配列のリフレッシュ
	for(int i=0;i<6;i++){
		tmp[i] = area[i];
	}
	//最小領域の添え字
	for(int i=1;i<6;i++){
	    if(tmp[0]>=tmp[i]){
			tmp[0] = tmp[i];
			min = i;
		}	
	}

	//緑と黄色で輪郭線を描画
	cv::drawContours(ans2,contours,max,cv::Scalar(0,255,0));
	cv::drawContours(ans2,contours,min,cv::Scalar(0,255,255));
	if(cv::imwrite("toutput.bmp", ans2) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}

	// 検出された輪郭線を赤で描画
	cv::drawContours(ans1,contours,-1,cv::Scalar(0, 0, 255));

	if(cv::imwrite("woutput.bmp", ans1) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}
	
	//最大最小領域の面積と周囲長
	//周囲長を求める
	double maxperimeter = cv::arcLength(cv::Mat(contours[max]),true);
	double minperimeter = cv::arcLength(cv::Mat(contours[min]),true);
	std::cout << "最大領域：　面積＝" << area[max] << ", 周囲長＝" << maxperimeter << std::endl;
	std::cout << "最小領域：　面積＝" << area[min] << ", 周囲長＝" << minperimeter << std::endl;

	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}