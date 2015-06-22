#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("k1.png",0);	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}

	//グラフ化するデータの格納準備
	int histdata[256];
	for(int i=0;i<256;i++){
		histdata[i] = 0;
	}

	//データを計算
	for(int y=0; y< img.rows;y++){
		for(int x=0; x<img.cols; x++){
			histdata[(int)(img.at<uchar>(y,x))]++;
		}
	}

	//データのファイル出力
	std::ofstream ofs("hist.csv");
	for(int i=0;i<256;i++){
		ofs << i << "," << histdata[i] << std::endl;
	}
	
	return 0;
}