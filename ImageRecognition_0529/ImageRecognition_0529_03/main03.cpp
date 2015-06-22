#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("Pentagons.png");	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}	
	//�֊s�`��p�̉摜
	cv::Mat ans1 = img;	//�S�֊s��Ԃŕ`��
	cv::Mat ans2 = img;	//�ő��΁A�ŏ������F�ŕ`��

	//RGB�摜���O���[�X�P�[����
	cv::cvtColor(img,img,CV_BGR2GRAY);

	//�֊s�̍��W�i�[�p
	std::vector< std::vector< cv::Point > > contours;
	//�֊s���o
	cv::findContours(img,contours,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//�ő�ʐς�ΐF�A�ŏ��ʐς����F�ŕ`��
	double area[6];	//�e�̈�̖ʐϊi�[
	for(int i=0;i<6;i++){
		area[i] = cv::contourArea(cv::Mat(contours[i]));
	}
	//�ő�ŏ��̓Y�������擾
	int max=0;		int min =0;
	//��Ɨp�z��
	double tmp[6];
	for(int i=0;i<6;i++){
		tmp[i] = area[i];
	}
	//�ő�̈�̓Y����
	for(int i=1;i<6;i++){
	    if(tmp[0]<=tmp[i]){
			tmp[0] = tmp[i];
			max = i;
		}	
	}

	//��Ɨp�z��̃��t���b�V��
	for(int i=0;i<6;i++){
		tmp[i] = area[i];
	}
	//�ŏ��̈�̓Y����
	for(int i=1;i<6;i++){
	    if(tmp[0]>=tmp[i]){
			tmp[0] = tmp[i];
			min = i;
		}	
	}

	//�΂Ɖ��F�ŗ֊s����`��
	cv::drawContours(ans2,contours,max,cv::Scalar(0,255,0));
	cv::drawContours(ans2,contours,min,cv::Scalar(0,255,255));
	if(cv::imwrite("toutput.bmp", ans2) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}

	// ���o���ꂽ�֊s����Ԃŕ`��
	cv::drawContours(ans1,contours,-1,cv::Scalar(0, 0, 255));

	if(cv::imwrite("woutput.bmp", ans1) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	
	//�ő�ŏ��̈�̖ʐςƎ��͒�
	//���͒������߂�
	double maxperimeter = cv::arcLength(cv::Mat(contours[max]),true);
	double minperimeter = cv::arcLength(cv::Mat(contours[min]),true);
	std::cout << "�ő�̈�F�@�ʐρ�" << area[max] << ", ���͒���" << maxperimeter << std::endl;
	std::cout << "�ŏ��̈�F�@�ʐρ�" << area[min] << ", ���͒���" << minperimeter << std::endl;

	cv::waitKey();	//�L�[���������܂ő҂�
	return 0;
}