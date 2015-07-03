#include <iostream>
#include <opencv2\opencv.hpp>

//後でカラー化する
int main(int argc, const char * argv[]){
	cv::Mat k2img = cv::imread("k2.png");	//target画像ファイルの読み込み
	if (k2img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "k2ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
    //2値画像化
    cv::Mat k2imggray;
    //RGB画像をグレースケール化
	cv::cvtColor(k2img,k2imggray,CV_BGR2GRAY);
    //Cannyのエッジ検出
    cv::Mat resimg; //出力画像
    cv::Canny(k2imggray,resimg,170.0,200.0,3);

    //ハフ変換(直線検出)
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(resimg,lines,1.0,CV_PI/90,80,30,10);
	for(size_t i=0; i<lines.size(); i++){
		line(k2img, cv::Point(lines[i][0],lines[i][1]), 
			cv::Point(lines[i][2],lines[i][3]),cv::Scalar(0,0,255));
	}


    cv::Mat coinimg = cv::imread("coins.png");	//target画像ファイルの読み込み
	if (coinimg.empty())	//ファイルの読み込み失敗
	{
		std::cout << "coinファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
    //2値画像化
    cv::Mat coinimggray;
    //RGB画像をグレースケール化
	cv::cvtColor(coinimg,coinimggray,CV_BGR2GRAY);


    //ハフ変換(円検出)
    std::vector<cv::Vec3f> circles;
	cv::HoughCircles(coinimggray,circles,CV_HOUGH_GRADIENT,10,coinimggray.rows/4,230,100);
	for(size_t i=0; i<circles.size(); i++){
		cv::Point center((int)circles[i][0],(int)circles[i][1]);
		int radius = (int)circles[i][2];
		cv::circle(coinimg,center,radius,cv::Scalar(0,0,255),2);
	}

     //画像の保存
	if(cv::imwrite("18.png", coinimg) == false){	//保存の成否判定
		std::cout << "ファイルの保存に失敗" << std::endl;
		return -1;
	}
}