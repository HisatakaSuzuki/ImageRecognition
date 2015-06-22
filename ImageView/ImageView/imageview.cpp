#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("kurage.jpg");	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}

	cv::namedWindow("image");	//ウィンドウの生成
	cv::imshow("image", img);	//画像の描画

	cv::waitKey();	//キーが押されるまで待つ

	//画像の保存
	if(cv::imwrite("outputimage.bmp", img) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}
	return 0;
}