#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("k1.png");	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
	//���摜�̕\��
	cv::namedWindow("Original Image");	//�E�B���h�E�̐���
	cv::imshow("Original Image",img);	//�摜�̕`��

	//�o�͉摜�̏���
	cv::Mat distimg;
	cv::Mat tmp;	//��Ɨp

	//��������3*3�\�[�x���t�B���^
	cv::Sobel(img, tmp, CV_32F,1,0,3);
	cv::convertScaleAbs(tmp,distimg);	//�e��f�l�̐�Βl�����߂�
	cv::namedWindow("Horizontal Sobel");	//�E�B���h�E�̐���
	cv::imshow("Horizontal Sobel", distimg);	//�摜�̕`��
	if(cv::imwrite("Horizontal Sobel.bmp", distimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	
	//�c������3*3�\�[�x���t�B���^
	cv::Sobel(img, tmp, CV_32F,0,1,3);
	cv::convertScaleAbs(tmp,distimg);	//�e��f�l�̐�Βl�����߂�
	cv::namedWindow("Vertcal Sobel");	//�E�B���h�E�̐���
	cv::imshow("Vertcal Sobel", distimg);	//�摜�̕`��
	if(cv::imwrite("Vertcal Sobel.bmp", distimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}

	//3*3���v���V�A���t�B���^
	cv::Laplacian(img, tmp, CV_32F,3);
	cv::convertScaleAbs(tmp,distimg);	//�e��f�l�̐�Βl�����߂�
	cv::namedWindow("Laplacian");	//�E�B���h�E�̐���
	cv::imshow("Laplacian", distimg);	//�摜�̕`��
	if(cv::imwrite("Laplacian.bmp", distimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}

	cv::waitKey();	//�L�[���������܂ő҂�
	return 0;
}