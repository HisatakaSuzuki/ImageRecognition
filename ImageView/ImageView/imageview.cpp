#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("kurage.jpg");	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}

	cv::namedWindow("image");	//�E�B���h�E�̐���
	cv::imshow("image", img);	//�摜�̕`��

	cv::waitKey();	//�L�[���������܂ő҂�

	//�摜�̕ۑ�
	if(cv::imwrite("outputimage.bmp", img) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	return 0;
}