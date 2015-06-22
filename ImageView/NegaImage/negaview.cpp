#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("kurage.jpg");	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}

	for(int y=0; y< img.rows;y++){
		for(int x=0; x<img.cols; x++){
			for(int i=0;i<3;i++){
				img.at<cv::Vec3b>(y,x)[i] = 255 - (int)(img.at<cv::Vec3b>(y,x)[i]);
			}
		}
	}

	cv::namedWindow("image");	//�E�B���h�E�̐���
	cv::imshow("image", img);	//�摜�̕`��

	cv::waitKey();	//�L�[���������܂ő҂�
	return 0;
}