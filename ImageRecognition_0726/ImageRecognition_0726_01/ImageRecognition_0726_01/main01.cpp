#include <iostream>
#include <opencv2\/opencv.hpp>
#include <sstream>	//ostringstream

int main(int argc, const char * argv[]){
	cv::Mat origin[4];

	//�t�@�C���̓ǂݍ���
	for(int i=0;i<4;i++){
		std::ostringstream oss;
		oss << "image_0" << (i+1) << ".jpg";
		origin[i] = cv::imread(oss.str(),0); //�K���摜�ǂݍ���
		if (origin[i].empty())	//�t�@�C���̓ǂݍ��ݎ��s
		{
			std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂����F" << i << std::endl;
			return -1;
		}
	}

	//����image01-image02
	cv::Mat sub_12(origin[0].rows,origin[0].cols,CV_8UC1);
	cv::absdiff(origin[0],origin[1],sub_12);	//�O���[�X�P�[���摜���獷���𒊏o
	cv::imwrite("sub12_1.bmp", sub_12);			//�����摜���o��
	cv::threshold(sub_12,sub_12,13.0,255.0,CV_THRESH_BINARY);	//�����摜��2�l��
	cv::imwrite("sub12_2.bmp", sub_12);			//2�l�������摜���o��

	//����image03-image04
	cv::Mat sub_34(origin[2].rows,origin[3].cols,CV_8UC1);
	cv::absdiff(origin[2],origin[3],sub_34);	//�O���[�X�P�[���摜���獷���𒊏o
	cv::imwrite("sub34_1.bmp", sub_34);			//�����摜���o��
	cv::threshold(sub_34,sub_34,30.0,255.0,CV_THRESH_BINARY);	//�����摜��2�l��
	cv::imwrite("sub34_2.bmp", sub_34);			//2�l�������摜���o��

	//cv::namedWindow("image");	//�E�B���h�E�̐���
	//cv::imshow("image", sub_34);	//�摜�̕`��
	return 0;
}