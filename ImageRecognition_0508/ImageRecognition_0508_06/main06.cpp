#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img[2] = 
		{cv::imread("Blur.bmp", 0),cv::imread("GaussianBlur.bmp", 0)};
	
	for(int i=0;i<2;i++){
		if (img[i].empty())	//�t�@�C���̓ǂݍ��ݎ��s
		{
			std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
			return -1;
		}
	}
	
	//���摜�̕\��
	cv::namedWindow("Blur Image");	//�E�B���h�E�̐���
	cv::imshow("Blur Image",img[0]);	//�摜�̕`��
	cv::namedWindow("GaussianBlur Image");	//�E�B���h�E�̐���
	cv::imshow("GaussianBlur Image",img[1]);	//�摜�̕`��

	//�J�[�l���̏���
	cv::Mat kernel = cv::Mat::ones(3,3,CV_32F);
	double defk = 1.0;
	double k[3][3] = {{-defk,-defk,-defk},{-defk,1 + 8*defk,-defk},{-defk,-defk,-defk}};

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			kernel.at<float>(i,j) *= k[i][j];
		}
	}
	//�o�͉摜�̏���
	cv::Mat distimg;

	//���ω��摜�̑N�s��
	cv::filter2D(img[0], distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image1_1.bmp", distimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	
	//�N�s���摜�̑N�s��
	cv::filter2D(distimg, distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image1_2.bmp", distimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}


	//�K�E�V�A���摜�̑N�s��
	cv::filter2D(img[1], distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image2_1.bmp", distimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}

	//�N�s���摜�̑N�s��
	cv::filter2D(distimg, distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image2_2.bmp", distimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	cv::waitKey();	//�L�[���������܂ő҂�
	return 0;
}