#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("RasterScan.png", 0);
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
	
	for(int y=0; y< img.rows;y++){
		for(int x=0; x<img.cols; x++){
			std::cout << (int)(img.at<uchar>(y,x)) << ",";
		}
		std::cout << std::endl;
	}
	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}