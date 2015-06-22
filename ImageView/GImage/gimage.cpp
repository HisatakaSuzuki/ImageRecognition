#include <iostream>
#include <opencv2\opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("G.png", 0);	//階調画像として読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
	int col = img.cols;
	int row = img.rows;

	//出力画像の準備
	cv::Mat img1(row,col, CV_8UC1);	//上下反転
	cv::Mat img2(row,col, CV_8UC1);	//左右反転
	cv::Mat img3(row,col, CV_8UC1);	//上下反転+左右反転
	
	//上下反転と左右反転画像を生成
	for(int y=0; y < row; y++){
		for(int x=0; x< col; x++){
			img1.at<uchar>(row-1-y,x) = img.at<uchar>(y,x); //上下反転
			img2.at<uchar>(y,col-1-x) = img.at<uchar>(y,x);	//左右反転
		}
	}

	//上下反転画像をさらに左右反転画像にする
	for(int y=0; y < row; y++){
		for(int x=0; x< col; x++){
			img3.at<uchar>(y,col-1-x) = img1.at<uchar>(y,x); //左右反転
		}
	}

	cv::namedWindow("image");	//ウィンドウの生成
	cv::imshow("image", img);	//画像の描画

	cv::namedWindow("image1");	//ウィンドウの生成
	cv::imshow("image1", img1);	//画像の描画

	cv::namedWindow("image2");	//ウィンドウの生成
	cv::imshow("image2", img2);	//画像の描画

	cv::namedWindow("image3");	//ウィンドウの生成
	cv::imshow("image3", img3);	//画像の描画

	cv::waitKey();	//キーが押されるまで待つ

	return 0;
}