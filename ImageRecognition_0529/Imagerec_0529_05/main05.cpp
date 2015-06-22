#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>

#define M_PI 3.14159265358979 /* 円周率 */

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("Eggplant.png",0);	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}

	cv::threshold(img,img,127.0,255.0,CV_THRESH_BINARY_INV);	//2値化

	//元画像の表示
	cv::namedWindow("Closed Image");	//ウィンドウの生成
	//cv::imshow("Original Image",img);	//画像の描画

	//N=4でクロージング
	//膨張
	for(int i=0;i<4;i++){
	cv::dilate(img,img,cv::Mat());
	}

	//収縮
	for(int i=0;i<4;i++){
	cv::erode(img,img,cv::Mat());
	}
	
	cv::imshow("Closed Image",img);	//画像の描画
	
	//輪郭の座標格納用
	std::vector< std::vector< cv::Point > > contours;

	//輪郭検出
	cv::findContours(img,contours,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//面積
	double area = cv::contourArea(cv::Mat(contours[0]));

	//周囲長
	double perimeter = cv::arcLength(cv::Mat(contours[0]),true);

	//モーメント計算
	cv::Moments m = cv::moments(img,true);

	//重心
	double x_g = m.m10 / m.m00;	//x重心座標
	double y_g = m.m01 / m.m00; //y重心座標

	//円形度
	double circle = 4 * M_PI * area / perimeter * perimeter;

	//主軸角度
	double theta = std::atan(2*m.m11/(m.m20-m.m02))/2;

	std::cout << "area=" << area << "\nperimeter=" << perimeter << "\n(x,y)=(" << x_g << "," << y_g << ")\n"
		<< "circle=" << circle << "\nθ=" << theta;

	cv::waitKey();

	return 0;
}