#include <iostream>
#include <opencv2\opencv.hpp>

//��ŃJ���[������
int main(int argc, const char * argv[]){
	cv::Mat k2img = cv::imread("k2.png");	//target�摜�t�@�C���̓ǂݍ���
	if (k2img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "k2�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
    //2�l�摜��
    cv::Mat k2imggray;
    //RGB�摜���O���[�X�P�[����
	cv::cvtColor(k2img,k2imggray,CV_BGR2GRAY);
    //Canny�̃G�b�W���o
    cv::Mat resimg; //�o�͉摜
    cv::Canny(k2imggray,resimg,170.0,200.0,3);

    //�n�t�ϊ�(�������o)
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(resimg,lines,1.0,CV_PI/90,80,30,10);
	for(size_t i=0; i<lines.size(); i++){
		line(k2img, cv::Point(lines[i][0],lines[i][1]), 
			cv::Point(lines[i][2],lines[i][3]),cv::Scalar(0,0,255));
	}


    cv::Mat coinimg = cv::imread("coins.png");	//target�摜�t�@�C���̓ǂݍ���
	if (coinimg.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "coin�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
    //2�l�摜��
    cv::Mat coinimggray;
    //RGB�摜���O���[�X�P�[����
	cv::cvtColor(coinimg,coinimggray,CV_BGR2GRAY);


    //�n�t�ϊ�(�~���o)
    std::vector<cv::Vec3f> circles;
	cv::HoughCircles(coinimggray,circles,CV_HOUGH_GRADIENT,10,coinimggray.rows/4,230,100);
	for(size_t i=0; i<circles.size(); i++){
		cv::Point center((int)circles[i][0],(int)circles[i][1]);
		int radius = (int)circles[i][2];
		cv::circle(coinimg,center,radius,cv::Scalar(0,0,255),2);
	}

     //�摜�̕ۑ�
	if(cv::imwrite("18.png", coinimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
}