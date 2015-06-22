#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("A.png",0);	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}	
}