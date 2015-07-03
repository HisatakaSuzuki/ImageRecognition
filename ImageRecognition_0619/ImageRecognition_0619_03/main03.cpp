#include <iostream>
#include <opencv2\opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat tarimg = cv::imread("target.png");	//target画像ファイルの読み込み
	if (tarimg.empty())	//ファイルの読み込み失敗
	{
		std::cout << "tarファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
}