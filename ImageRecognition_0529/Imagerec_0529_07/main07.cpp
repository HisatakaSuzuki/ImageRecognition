#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("ABC.png",0);	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}	

	//���摜�̕\��
	cv::namedWindow("Original Image");	//�E�B���h�E�̐���
	
	cv::threshold(img,img,100.0,255.0,CV_THRESH_BINARY);	//2�l��
	//���f�B�A���t�B���^�����O
	cv::medianBlur(img, img, 5);
	

	//N=2�ŃN���[�W���O
	//�c��
	for(int i=0;i<2;i++){
	cv::dilate(img,img,cv::Mat());
	}
	//���k
	for(int i=0;i<2;i++){
	cv::erode(img,img,cv::Mat());
	}
	if(cv::imwrite("output.bmp", img) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	cv::imshow("Original Image",img);	//�摜�̕`��
	cv::waitKey();	//�L�[���������܂ő҂�
	return 0;
}