#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>

#define M_PI 3.14159265358979 /* �~���� */

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("Eggplant.png",0);	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}

	cv::threshold(img,img,127.0,255.0,CV_THRESH_BINARY_INV);	//2�l��

	//���摜�̕\��
	cv::namedWindow("Closed Image");	//�E�B���h�E�̐���
	//cv::imshow("Original Image",img);	//�摜�̕`��

	//N=4�ŃN���[�W���O
	//�c��
	for(int i=0;i<4;i++){
	cv::dilate(img,img,cv::Mat());
	}

	//���k
	for(int i=0;i<4;i++){
	cv::erode(img,img,cv::Mat());
	}
	
	cv::imshow("Closed Image",img);	//�摜�̕`��
	
	//�֊s�̍��W�i�[�p
	std::vector< std::vector< cv::Point > > contours;

	//�֊s���o
	cv::findContours(img,contours,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//�ʐ�
	double area = cv::contourArea(cv::Mat(contours[0]));

	//���͒�
	double perimeter = cv::arcLength(cv::Mat(contours[0]),true);

	//���[�����g�v�Z
	cv::Moments m = cv::moments(img,true);

	//�d�S
	double x_g = m.m10 / m.m00;	//x�d�S���W
	double y_g = m.m01 / m.m00; //y�d�S���W

	//�~�`�x
	double circle = 4 * M_PI * area / perimeter * perimeter;

	//�厲�p�x
	double theta = std::atan(2*m.m11/(m.m20-m.m02))/2;

	std::cout << "area=" << area << "\nperimeter=" << perimeter << "\n(x,y)=(" << x_g << "," << y_g << ")\n"
		<< "circle=" << circle << "\n��=" << theta;

	cv::waitKey();

	return 0;
}