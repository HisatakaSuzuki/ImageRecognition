#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("ABC.png",0);	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}	

	//元画像の表示
	cv::namedWindow("Original Image");	//ウィンドウの生成
	
	cv::threshold(img,img,100.0,255.0,CV_THRESH_BINARY);	//2値化
	//メディアンフィルタリング
	cv::medianBlur(img, img, 5);
	

	//N=2でクロージング
	//膨張
	for(int i=0;i<2;i++){
	cv::dilate(img,img,cv::Mat());
	}
	//収縮
	for(int i=0;i<2;i++){
	cv::erode(img,img,cv::Mat());
	}
	if(cv::imwrite("output.bmp", img) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}
	cv::imshow("Original Image",img);	//画像の描画
	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}