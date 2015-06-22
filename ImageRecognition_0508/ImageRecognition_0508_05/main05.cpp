#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("k1.png");	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
	//元画像の表示
	cv::namedWindow("Original Image");	//ウィンドウの生成
	cv::imshow("Original Image",img);	//画像の描画

	//出力画像の準備
	cv::Mat distimg;
	cv::Mat tmp;	//作業用

	//横方向の3*3ソーベルフィルタ
	cv::Sobel(img, tmp, CV_32F,1,0,3);
	cv::convertScaleAbs(tmp,distimg);	//各画素値の絶対値を求める
	cv::namedWindow("Horizontal Sobel");	//ウィンドウの生成
	cv::imshow("Horizontal Sobel", distimg);	//画像の描画
	if(cv::imwrite("Horizontal Sobel.bmp", distimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}
	
	//縦方向の3*3ソーベルフィルタ
	cv::Sobel(img, tmp, CV_32F,0,1,3);
	cv::convertScaleAbs(tmp,distimg);	//各画素値の絶対値を求める
	cv::namedWindow("Vertcal Sobel");	//ウィンドウの生成
	cv::imshow("Vertcal Sobel", distimg);	//画像の描画
	if(cv::imwrite("Vertcal Sobel.bmp", distimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}

	//3*3ラプラシアンフィルタ
	cv::Laplacian(img, tmp, CV_32F,3);
	cv::convertScaleAbs(tmp,distimg);	//各画素値の絶対値を求める
	cv::namedWindow("Laplacian");	//ウィンドウの生成
	cv::imshow("Laplacian", distimg);	//画像の描画
	if(cv::imwrite("Laplacian.bmp", distimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}

	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}