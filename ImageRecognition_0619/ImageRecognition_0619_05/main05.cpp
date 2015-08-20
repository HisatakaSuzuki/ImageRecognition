#include <iostream>
#include <opencv2\opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("coins.png",0);	//target画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}

    //Cannyのエッジ検出
    cv::Mat resimg; //出力画像
	cv::Canny(img,resimg,120.0,240.0,3);

    //画像の保存
	if(cv::imwrite("coinout.png",resimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}
}