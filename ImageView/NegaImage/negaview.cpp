#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("kurage.jpg");	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}

	for(int y=0; y< img.rows;y++){
		for(int x=0; x<img.cols; x++){
			for(int i=0;i<3;i++){
				img.at<cv::Vec3b>(y,x)[i] = 255 - (int)(img.at<cv::Vec3b>(y,x)[i]);
			}
		}
	}

	cv::namedWindow("image");	//ウィンドウの生成
	cv::imshow("image", img);	//画像の描画

	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}