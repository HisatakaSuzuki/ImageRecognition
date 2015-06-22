#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("A.png",0);	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}	

	//���k
	cv::Mat disterode;
	cv::erode(img,disterode,cv::Mat());
	if(cv::imwrite("erode1.bmp", disterode) == false){	//�ۑ��̐��۔���
		std::cout << "erode1�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	cv::erode(disterode,disterode,cv::Mat());
	if(cv::imwrite("erode2.bmp", disterode) == false){	//�ۑ��̐��۔���
		std::cout << "erode2�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}

	//�c��
	cv::Mat distdilate;
	cv::dilate(img,distdilate,cv::Mat());
	if(cv::imwrite("dilate1.bmp", distdilate) == false){	//�ۑ��̐��۔���
		std::cout << "dilate1�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	cv::dilate(distdilate,distdilate,cv::Mat());
	if(cv::imwrite("dilate2.bmp", distdilate) == false){	//�ۑ��̐��۔���
		std::cout << "dilate2�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}

	//��ق�2����k�����摜�̃I�[�v�j���O
	cv::Mat etod;
	cv::dilate(disterode,etod,cv::Mat());	//1���
	cv::dilate(etod,etod,cv::Mat());		//2���
	if(cv::imwrite("etod.bmp", etod) == false){	//�ۑ��̐��۔���
		std::cout << "etod�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}


	//��ق�2��c�������摜�̃N���[�W���O
	cv::Mat dtoe;
	cv::erode(distdilate,dtoe,cv::Mat());	//1���
	cv::erode(dtoe,dtoe,cv::Mat());			//2���
	if(cv::imwrite("dtoe.bmp", dtoe) == false){	//�ۑ��̐��۔���
		std::cout << "dtoe�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	
	return 0;
}