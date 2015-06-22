#include <iostream>
#include <opencv2\opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("G.png", 0);	//�K���摜�Ƃ��ēǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
	int col = img.cols;
	int row = img.rows;

	//�o�͉摜�̏���
	cv::Mat img1(row,col, CV_8UC1);	//�㉺���]
	cv::Mat img2(row,col, CV_8UC1);	//���E���]
	cv::Mat img3(row,col, CV_8UC1);	//�㉺���]+���E���]
	
	//�㉺���]�ƍ��E���]�摜�𐶐�
	for(int y=0; y < row; y++){
		for(int x=0; x< col; x++){
			img1.at<uchar>(row-1-y,x) = img.at<uchar>(y,x); //�㉺���]
			img2.at<uchar>(y,col-1-x) = img.at<uchar>(y,x);	//���E���]
		}
	}

	//�㉺���]�摜������ɍ��E���]�摜�ɂ���
	for(int y=0; y < row; y++){
		for(int x=0; x< col; x++){
			img3.at<uchar>(y,col-1-x) = img1.at<uchar>(y,x); //���E���]
		}
	}

	cv::namedWindow("image");	//�E�B���h�E�̐���
	cv::imshow("image", img);	//�摜�̕`��

	cv::namedWindow("image1");	//�E�B���h�E�̐���
	cv::imshow("image1", img1);	//�摜�̕`��

	cv::namedWindow("image2");	//�E�B���h�E�̐���
	cv::imshow("image2", img2);	//�摜�̕`��

	cv::namedWindow("image3");	//�E�B���h�E�̐���
	cv::imshow("image3", img3);	//�摜�̕`��

	cv::waitKey();	//�L�[���������܂ő҂�

	return 0;
}