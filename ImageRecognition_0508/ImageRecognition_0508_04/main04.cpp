#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("smile.png");	//�摜�t�@�C���̓ǂݍ���
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
	//���f�B�A���t�B���^�����O
	for(int i=3; i<8; i =i+2){
		cv::medianBlur(img, distimg, i);
		std::string winname = "MedianBlur Image("+ std::to_string(i)+"_"+std::to_string(i)+")";
		cv::namedWindow(winname);	//�E�B���h�E�̐���
		cv::imshow(winname, distimg);	//�摜�̕`��
		if(cv::imwrite(winname+".bmp", distimg) == false){	//�ۑ��̐��۔���
			std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
		}
	}
	cv::waitKey();	//�L�[���������܂ő҂�
	return 0;
}