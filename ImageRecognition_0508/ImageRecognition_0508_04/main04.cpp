#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("smile.png");	//画像ファイルの読み込み
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
	//メディアンフィルタリング
	for(int i=3; i<8; i =i+2){
		cv::medianBlur(img, distimg, i);
		std::string winname = "MedianBlur Image("+ std::to_string(i)+"_"+std::to_string(i)+")";
		cv::namedWindow(winname);	//ウィンドウの生成
		cv::imshow(winname, distimg);	//画像の描画
		if(cv::imwrite(winname+".bmp", distimg) == false){	//保存の成否判定
			std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
		}
	}
	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}