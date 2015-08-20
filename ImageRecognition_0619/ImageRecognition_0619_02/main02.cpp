#include <iostream>
#include <opencv2\opencv.hpp>
#include "Timer.h"

//�֐��̃v���g�^�C�v�錾
void sadTemplate(cv::InputArray tar, cv::InputArray tmp, cv::OutputArray res, int *minx, int *miny);

int main(int argc, const char * argv[]){
	cv::Mat tarimg = cv::imread("Dice.png");	//target�摜�t�@�C���̓ǂݍ���
	if (tarimg.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "tar�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
	cv::Mat tmpimg = cv::imread("DiceTmp1.png");	//tmp�摜�t�@�C���̓ǂݍ���
	if (tmpimg.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "tmp�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
	
	//2�l�摜��
    cv::Mat targray;
    //RGB�摜���O���[�X�P�[����
	cv::cvtColor(tarimg,targray,CV_BGR2GRAY);
	//2�l�摜��
    cv::Mat tmpgray;
    //RGB�摜���O���[�X�P�[����
	cv::cvtColor(tmpimg,tmpgray,CV_BGR2GRAY);

	//���ʉ摜�̃T�C�Y���v�Z
	int resrow = tarimg.rows - tmpimg.rows+1;
	int rescol = tarimg.cols - tmpimg.cols+1;
	cv::Mat resimg(resrow,rescol,CV_8UC1);	//�}�b�`���O�̌��ʂ�ێ�����
	int minx, miny;	//�_�̈ʒu��`��p�Ɋi�[����
	
	//�e���v���[�g�}�b�`���O
	Timer tm;	//�������Ԍv���p
	sadTemplate(targray,tmpgray,resimg,&minx,&miny);	//�}�b�`���O�֐�
	double time = tm.elapsed();	//�������ԃX�g�b�v
	std::cout << "�o�ߎ��Ԃ�" << time << "������܂����B\n";

	//��`�`��
	cv::rectangle(tarimg,cv::Point(minx,miny),cv::Point(minx+tmpimg.rows,miny+tmpimg.cols),cv::Scalar(0,0,255),1,4);

	//�摜�̕ۑ�
	if(cv::imwrite("result.png", tarimg) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}

	return 0;
}

void sadTemplate(cv::InputArray tar, cv::InputArray tmp, cv::OutputArray res, int *minx, int *miny){
	//�����̓��͂�Mat�Ƃ��Ď󂯎��
	cv::Mat tarM = tar.getMat();	
	cv::Mat tmpM = tmp.getMat();
	cv::Mat resM = res.getMat();

	//sad���ŏ��l�̂Ƃ��낪�}�b�`���O�������ӏ��Ȃ̂�
	int minsad = std::numeric_limits<int>::max();	
	int sad = 0;  //�e���sad���i�[
	int diff;	//sad�ɉ��Z����O�̍�ƕϐ�
	int tarx,tary;	//�ړI��xy���W


	for(int y=0;y<tarM.rows - tmpM.rows;y++){
		for(int x=0;x<tarM.cols - tmpM.cols;x++){
			sad = 0;	//���̗̈�̌v�Z�̑O�ɏ�����
			//�T��
			for(int yt = 0; yt < tmpM.rows; yt++){
				for(int xt = 0; xt < tmpM.cols; xt++){
					diff = (int)(tarM.at<uchar>(y+yt,x+xt) - tmpM.at<uchar>(yt,xt));
					if(diff < 0){  //���Ȃ琳�ɕϊ�
						diff = -diff;
					}
					sad += diff;
					////�c����������@
					if(sad > minsad){
						yt = tmpM.rows;	
						break;
					}
				}
			}

			//�T�����ʁFsad�����܂łōŏ��Ȃ�
			if(sad < minsad){
				minsad = sad;	//�ŏ��l���X�V
				//�ړI��xy���i�[
				tarx = x;
				tary = y;
			}
		}
	}

	//output�ɏo��
	for(int y=0;y<resM.rows;y++){
		for(int x=0;x<resM.cols;x++){
			if(x==tarx && y==tary){
				resM.at<uchar>(y,x) = (uchar)0;
			}else{
				resM.at<uchar>(y,x) = (uchar)255;
			}
		}
	}
	std::cout << "�ŏ��l��" << minsad << std::endl;
	std::cout << "�ŏ��_��[" << tarx << ", " << tary << "]" <<  std::endl;
	*minx = tarx;
	*miny = tary;
}

