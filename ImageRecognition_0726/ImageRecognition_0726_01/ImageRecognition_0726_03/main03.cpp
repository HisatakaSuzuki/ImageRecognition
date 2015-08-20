#include <iostream>
#include <opencv2\/opencv.hpp>
#include <sstream>	//ostringstream

void maskedVideo(cv::VideoCapture video,cv::VideoWriter vw,double thres,int framerate);

int main(){
	//����ǂݍ���
	cv::VideoCapture capA("movie_A.mp4");	
	cv::VideoCapture capB("movie_B.mp4");
	cv::VideoCapture capC("movie_C.mp4");
	if(!capA.isOpened() || !capB.isOpened() || !capC.isOpened()){
		std::cout << "����t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
		return -1;
	}

	//���C�^�[����
	//cv::VideoWriter vwA("movieA.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));
	//cv::VideoWriter vwB("movieB.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));
	cv::VideoWriter vwC("movieC.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));

	int fr = 10;

	//maskedVideo(capA,vwA,40.0,fr);
	//maskedVideo(capB,vwB,40.0,fr);
	maskedVideo(capC,vwC,40.0,fr);

	return 0;
}

void maskedVideo(cv::VideoCapture video,cv::VideoWriter vw,double thres,int framerate){
	cv::Mat frame_A, frame_B, frame_C, difference_image_AB, difference_image_BC, 
			difference_image, binary_image, gray_image, output;

	for(;;){
		video >> frame_A;
		video.set(CV_CAP_PROP_POS_FRAMES, video.get(CV_CAP_PROP_POS_FRAMES) + framerate);
		video >> frame_B;
		video.set(CV_CAP_PROP_POS_FRAMES, video.get(CV_CAP_PROP_POS_FRAMES) + framerate);
		video >> frame_C;
		video.set(CV_CAP_PROP_POS_FRAMES, video.get(CV_CAP_PROP_POS_FRAMES) - ((framerate + 1) * 2.0));
		if(frame_A.empty() || frame_B.empty() || frame_C.empty() || video.get(CV_CAP_PROP_POS_AVI_RATIO) == 1){
			break;
		}

		cv::absdiff(frame_A, frame_B, difference_image_AB);
		cv::absdiff(frame_B, frame_C, difference_image_BC);
		cv::bitwise_and(difference_image_AB, difference_image_BC, difference_image);

		cv::cvtColor(difference_image, gray_image, CV_BGR2GRAY);
		cv::threshold(gray_image, binary_image, thres, 255, cv::THRESH_BINARY);

		output = cv::Scalar::all(0);
		frame_A.copyTo(output, binary_image);

		vw << output;

	}
}

//void maskedVideo(cv::VideoCapture video,cv::VideoWriter vw,double thres,int framerate){
//	cv::Mat frame_A, frame_B, frame_C, difference_image_AB, difference_image_BC, 
//			difference_image, binary_image, gray_image, output;
//	cv::namedWindow("frameA");	//�E�B���h�E�̐���
//	//cv::namedWindow("frameB");	//�E�B���h�E�̐���
//	//cv::namedWindow("frameC");	//�E�B���h�E�̐���
//
//	double t = 0.0;
//	for(;;){
//		video.set(CV_CAP_PROP_POS_FRAMES, t + framerate);
//		video >> frame_A;
//		video.set(CV_CAP_PROP_POS_FRAMES, (t+1) + framerate);
//		video >> frame_B;
//		video.set(CV_CAP_PROP_POS_FRAMES, (t+2) + framerate);
//		video >> frame_C;
//		
//		if(frame_A.empty() || frame_B.empty() || frame_C.empty() || video.get(CV_CAP_PROP_POS_AVI_RATIO) == 1){
//			break;
//		}
//
//		cv::Mat gray_A,gray_B,gray_C;
//		cv::cvtColor(frame_A, gray_A,CV_RGB2GRAY);//�O���[�X�P�[���ϊ�
//		cv::cvtColor(frame_B, gray_B,CV_RGB2GRAY);//�O���[�X�P�[���ϊ�
//		cv::cvtColor(frame_C, gray_C,CV_RGB2GRAY);//�O���[�X�P�[���ϊ�
//
//		cv::absdiff(gray_A, gray_B, difference_image_AB);
//		cv::absdiff(gray_B, gray_C, difference_image_BC);
//		cv::bitwise_and(difference_image_AB, difference_image_BC, difference_image);
//
//		cv::imshow("frameA", frame_A);	//�摜�̕`��
//		cv::imshow("frameB", frame_B);	//�摜�̕`��
//		cv::imshow("frameC", frame_C);	//�摜�̕`��
//
//		//cv::threshold(difference_image, binary_image, thres, 255, cv::THRESH_BINARY);
//		t++;
//		std::cout << t << std::endl;
//		//output = cv::Scalar::all(0);
//		//�t���[��B�ɂ�����o��
//		//frame_B.copyTo(output, binary_image);
//		//vw << output;
//
//	}
//}