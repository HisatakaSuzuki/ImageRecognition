#include <iostream>
#include <fstream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img[6] = 
		{cv::imread("Blur Image(3_3).bmp", 0),cv::imread("Blur Image(5_5).bmp", 0),
		 cv::imread("Blur Image(7_7).bmp", 0),cv::imread("GaussianBlur Image(3_3).bmp", 0),
		 cv::imread("GaussianBlur Image(5_5).bmp", 0),cv::imread("GaussianBlur Image(7_7).bmp", 0)};
	
	//ファイルの読み込み確認
	for(int i=0;i<6;i++){
		if (img[i].empty())	//ファイルの読み込み失敗
		{
			std::cout << std::to_string(i+1)+"番目のファイルの読み込みに失敗しました" << std::endl;
			return -1;
		}
	}
	
	//データの出力/ファイルにも出力
	std::ofstream ofs("output.txt");
	for(int i=0;i<6;i++){
		std::cout << std::to_string(i+1)+"番 : ";	//コンソール出力
		ofs << std::to_string(i+1)+"番 : ";	//ファイル出力
		for(int x=0; x<34; x++){
			std::cout << (int)(img[i].at<uchar>(15,x)) << ",";	//コンソール出力
			ofs << (int)(img[i].at<uchar>(15,x)) << ",";	//ファイル出力
		}
		std::cout << std::endl;	//コンソール出力
		ofs << std::endl;	//ファイル出力
	}
	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}