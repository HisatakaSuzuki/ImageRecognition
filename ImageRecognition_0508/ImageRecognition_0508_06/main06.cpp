#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img[2] = 
		{cv::imread("Blur.bmp", 0),cv::imread("GaussianBlur.bmp", 0)};
	
	for(int i=0;i<2;i++){
		if (img[i].empty())	//ファイルの読み込み失敗
		{
			std::cout << "ファイルの読み込みに失敗しました" << std::endl;
			return -1;
		}
	}
	
	//元画像の表示
	cv::namedWindow("Blur Image");	//ウィンドウの生成
	cv::imshow("Blur Image",img[0]);	//画像の描画
	cv::namedWindow("GaussianBlur Image");	//ウィンドウの生成
	cv::imshow("GaussianBlur Image",img[1]);	//画像の描画

	//カーネルの準備
	cv::Mat kernel = cv::Mat::ones(3,3,CV_32F);
	double defk = 1.0;
	double k[3][3] = {{-defk,-defk,-defk},{-defk,1 + 8*defk,-defk},{-defk,-defk,-defk}};

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			kernel.at<float>(i,j) *= k[i][j];
		}
	}
	//出力画像の準備
	cv::Mat distimg;

	//平均化画像の鮮鋭化
	cv::filter2D(img[0], distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image1_1.bmp", distimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}
	
	//鮮鋭化画像の鮮鋭化
	cv::filter2D(distimg, distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image1_2.bmp", distimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}


	//ガウシアン画像の鮮鋭化
	cv::filter2D(img[1], distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image2_1.bmp", distimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}

	//鮮鋭化画像の鮮鋭化
	cv::filter2D(distimg, distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image2_2.bmp", distimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}
	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}