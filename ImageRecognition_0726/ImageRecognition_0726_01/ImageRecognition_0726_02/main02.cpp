#include <iostream>
#include <opencv2\/opencv.hpp>
#include <sstream>	//ostringstream

void maskedVideo(cv::Mat back,cv::VideoCapture video,cv::VideoWriter vw,double thres);

int main(){
	//�摜�ǂݍ���
	cv::Mat backAB =  cv::imread("background_AB.jpg"); 
	cv::Mat backC =  cv::imread("background_C.jpg"); 
	if (backAB.empty() || backC.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����F"  << std::endl;
		return -1;
	}

	//����ǂݍ���
	cv::VideoCapture capA("movie_A.mp4");	
	cv::VideoCapture capB("movie_B.mp4");
	cv::VideoCapture capC("movie_C.mp4");
	if(!capA.isOpened() || !capB.isOpened() || !capC.isOpened()){
		std::cout << "����t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
		return -1;
	}

	//���C�^�[����
	cv::VideoWriter vwA("movieA.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));
	cv::VideoWriter vwB("movieB.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));
	cv::VideoWriter vwC("movieC.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));

	maskedVideo(backAB,capA,vwA,40.0);
	maskedVideo(backAB,capB,vwB,40.0);
	maskedVideo(backC,capC,vwC,40.0);

	return 0;
}

void maskedVideo(cv::Mat back,cv::VideoCapture video,cv::VideoWriter vw,double thres){
	cv::cvtColor(back, back,CV_RGB2GRAY);//�O���[�X�P�[���ϊ�
	for(;;){
		cv::Mat frame;
		video >> frame;
		if(frame.empty() || video.get(CV_CAP_PROP_POS_AVI_RATIO)==1){
			break;
		}
		cv::Mat gframe; //�O���[�X�P�[��
		cv::cvtColor(frame, gframe,CV_RGB2GRAY);//�O���[�X�P�[���ϊ�

		//����image01-image02
		cv::Mat sub(back.rows,back.cols,CV_8UC1);
		cv::absdiff(back,gframe,sub);
		cv::threshold(sub,sub,thres,255.0,CV_THRESH_BINARY);	//2�l��

		//�}�X�N����
		cv::Mat dist;
		frame.copyTo(dist,sub);

		vw << dist;
		cv::imshow("test",frame);
	}
}