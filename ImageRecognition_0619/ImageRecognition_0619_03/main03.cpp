#include <iostream>
#include <opencv2\opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat tarimg = cv::imread("target.png");	//target�摜�t�@�C���̓ǂݍ���
	if (tarimg.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "tar�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
}