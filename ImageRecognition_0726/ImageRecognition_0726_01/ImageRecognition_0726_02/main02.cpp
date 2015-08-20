#include <iostream>
#include <opencv2\/opencv.hpp>
#include <sstream>	//ostringstream

void maskedVideo(cv::Mat back,cv::VideoCapture video,cv::VideoWriter vw,double thres);

int main(){
	//画像読み込み
	cv::Mat backAB =  cv::imread("background_AB.jpg"); 
	cv::Mat backC =  cv::imread("background_C.jpg"); 
	if (backAB.empty() || backC.empty())	//ファイルの読み込み失敗
	{
		std::cout << "画像ファイルの読み込みに失敗しました："  << std::endl;
		return -1;
	}

	//動画読み込み
	cv::VideoCapture capA("movie_A.mp4");	
	cv::VideoCapture capB("movie_B.mp4");
	cv::VideoCapture capC("movie_C.mp4");
	if(!capA.isOpened() || !capB.isOpened() || !capC.isOpened()){
		std::cout << "動画ファイルの読み込みに失敗しました";
		return -1;
	}

	//ライター準備
	cv::VideoWriter vwA("movieA.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));
	cv::VideoWriter vwB("movieB.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));
	cv::VideoWriter vwC("movieC.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));

	maskedVideo(backAB,capA,vwA,40.0);
	maskedVideo(backAB,capB,vwB,40.0);
	maskedVideo(backC,capC,vwC,40.0);

	return 0;
}

void maskedVideo(cv::Mat back,cv::VideoCapture video,cv::VideoWriter vw,double thres){
	cv::cvtColor(back, back,CV_RGB2GRAY);//グレースケール変換
	for(;;){
		cv::Mat frame;
		video >> frame;
		if(frame.empty() || video.get(CV_CAP_PROP_POS_AVI_RATIO)==1){
			break;
		}
		cv::Mat gframe; //グレースケール
		cv::cvtColor(frame, gframe,CV_RGB2GRAY);//グレースケール変換

		//差分image01-image02
		cv::Mat sub(back.rows,back.cols,CV_8UC1);
		cv::absdiff(back,gframe,sub);
		cv::threshold(sub,sub,thres,255.0,CV_THRESH_BINARY);	//2値化

		//マスク処理
		cv::Mat dist;
		frame.copyTo(dist,sub);

		vw << dist;
		cv::imshow("test",frame);
	}
}