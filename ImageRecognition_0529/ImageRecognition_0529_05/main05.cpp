#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("A.png",0);	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}	
}