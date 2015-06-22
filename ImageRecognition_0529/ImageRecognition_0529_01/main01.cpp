#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("k1.png",0);	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}

	//�O���t������f�[�^�̊i�[����
	int histdata[256];
	for(int i=0;i<256;i++){
		histdata[i] = 0;
	}

	//�f�[�^���v�Z
	for(int y=0; y< img.rows;y++){
		for(int x=0; x<img.cols; x++){
			histdata[(int)(img.at<uchar>(y,x))]++;
		}
	}

	//�f�[�^�̃t�@�C���o��
	std::ofstream ofs("hist.csv");
	for(int i=0;i<256;i++){
		ofs << i << "," << histdata[i] << std::endl;
	}
	
	return 0;
}