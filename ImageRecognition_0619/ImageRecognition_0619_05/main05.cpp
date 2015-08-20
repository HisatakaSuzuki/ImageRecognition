#include <iostream>
#include <opencv2\opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("coins.png",0);	//target�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}

    //Canny�̃G�b�W���o
    cv::Mat resimg; //�o�͉摜
	cv::Canny(img,resimg,120.0,240.0,3);

    //�摜�̕ۑ�
	if(cv::imwrite("coinout.png",resimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
}