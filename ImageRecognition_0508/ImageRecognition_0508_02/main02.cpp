#include <iostream>
#include <fstream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img[6] = 
		{cv::imread("Blur Image(3_3).bmp", 0),cv::imread("Blur Image(5_5).bmp", 0),
		 cv::imread("Blur Image(7_7).bmp", 0),cv::imread("GaussianBlur Image(3_3).bmp", 0),
		 cv::imread("GaussianBlur Image(5_5).bmp", 0),cv::imread("GaussianBlur Image(7_7).bmp", 0)};
	
	//�t�@�C���̓ǂݍ��݊m�F
	for(int i=0;i<6;i++){
		if (img[i].empty())	//�t�@�C���̓ǂݍ��ݎ��s
		{
			std::cout << std::to_string(i+1)+"�Ԗڂ̃t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
			return -1;
		}
	}
	
	//�f�[�^�̏o��/�t�@�C���ɂ��o��
	std::ofstream ofs("output.txt");
	for(int i=0;i<6;i++){
		std::cout << std::to_string(i+1)+"�� : ";	//�R���\�[���o��
		ofs << std::to_string(i+1)+"�� : ";	//�t�@�C���o��
		for(int x=0; x<34; x++){
			std::cout << (int)(img[i].at<uchar>(15,x)) << ",";	//�R���\�[���o��
			ofs << (int)(img[i].at<uchar>(15,x)) << ",";	//�t�@�C���o��
		}
		std::cout << std::endl;	//�R���\�[���o��
		ofs << std::endl;	//�t�@�C���o��
	}
	cv::waitKey();	//�L�[���������܂ő҂�
	return 0;
}