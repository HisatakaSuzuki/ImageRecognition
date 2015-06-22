#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("Giraffe.png",0);	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
	//ヒストグラム内の最小値・最大値・画素数・平均を求めておく
	int w_max=0; int w_min=0;
	int w_sum = img.rows * img.cols;	//全画素数
	double w_ave=0.0;

	//グラフ化するデータの格納準備
	int histdata[256];
	for(int i=0;i<256;i++){
		histdata[i] = 0;
	}

	//データを計算
	for(int y=0; y< img.rows;y++){
		for(int x=0; x<img.cols; x++){
			int i =(int)(img.at<uchar>(y,x));	//加算する値を保持
			histdata[i]++;	//ヒストグラムに加算
			if(w_max < i){w_max = i;}	//最大値格納
			if(w_min > i){w_min = i;}	//最小値格納
			w_ave += (double)i;	//平均計算用に加算
		}
	}
	w_ave = w_ave / w_sum;	//全画素平均を求めておく

	//分離度が最大になるしきい値を求める→クラス間分散が最大になる
	//しきい値tの値を求める
	double distb_max = -1.0;	//最大のクラス間分散
	//↓最大クラス間分散時の↓
	int t_max = 0;	//しきい値t
	int n1_max=0;	int n2_max=0;	//各クラスの画素の数
	double ave1_max=0.0; double ave2_max=0.0; //各クラスの平均値
	double dis1_max=0.0; double dis2_max=0.0; //各クラスの分散値

	for(int t =0; t<256;t++){
		int num1=0; //クラス1の画素数
		double ave1=0.0;	//クラス1の画素平均
		double dis1=0.0;	//クラス1の分散
		int tmp=0;	//平均を求めるための作業変数
		//クラス1内のヒストグラム
		for(int i=0;i<t;i++){
			num1 += histdata[i];
			tmp += i * histdata[i];
		}
		//クラス1平均値
		ave1 = (double)tmp/num1;
		for(int i=0;i<t;i++){
			dis1 = dis1 + ((i-ave1)*(i-ave1)/num1);
		}
		//分散を求める
		dis1 = dis1 / num1;

		//クラス2も同様に求める
		tmp = 0;
		int num2=0; //クラス2の画素数
		double ave2=0.0;	//クラス2の画素平均
		double dis2=0.0;	//クラス2の分散
		//クラス2内のヒストグラム
		for(int i=t;i<256;i++){
			num2 += histdata[i];
			tmp += i * histdata[i];
		}
		//クラス2平均値
		ave2 = (double)tmp/num2;
		for(int i=t;i<256;i++){
			dis2 = dis2 + ((i-ave2)*(i-ave2)/num2);
		}
		//分散を求める
		dis2 = dis2 / num2;

		//クラス間分散
		double distb = num1*num2*(ave1-ave2)*(ave1-ave2) / (num1+num2)*(num1+num2);
		if(distb_max < distb){
			distb_max = distb;
			t_max = t;
			n1_max = num1;	n2_max = num2;
			ave1_max = ave1;	ave2_max = ave2;
			dis1_max = dis1;	dis2_max = dis2;
		}
	}
	
	//各値を出力する
	std::cout << "しきい値：" << t_max << std::endl;
	std::cout << "\nクラス1\n";
	std::cout << "画素数：" << n1_max << std::endl;
	std::cout << "平均値：" << ave1_max << std::endl;
	std::cout << "分散値：" << dis1_max << std::endl;
	std::cout << "\nクラス2\n";
	std::cout << "画素数：" << n2_max << std::endl;
	std::cout << "平均値：" << ave2_max << std::endl;
	std::cout << "分散値：" << dis2_max << std::endl;
	std::cout << "\nクラス間分散" << distb_max << std::endl;

	cv::threshold(img,img,t_max,255.0,CV_THRESH_BINARY);	//2値化
	if(cv::imwrite("output.bmp", img) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}
	cv::waitKey();
	return 0;
}
