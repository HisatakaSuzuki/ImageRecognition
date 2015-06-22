#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("Giraffe.png",0);	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
	//�q�X�g�O�������̍ŏ��l�E�ő�l�E��f���E���ς����߂Ă���
	int w_max=0; int w_min=0;
	int w_sum = img.rows * img.cols;	//�S��f��
	double w_ave=0.0;

	//�O���t������f�[�^�̊i�[����
	int histdata[256];
	for(int i=0;i<256;i++){
		histdata[i] = 0;
	}

	//�f�[�^���v�Z
	for(int y=0; y< img.rows;y++){
		for(int x=0; x<img.cols; x++){
			int i =(int)(img.at<uchar>(y,x));	//���Z����l��ێ�
			histdata[i]++;	//�q�X�g�O�����ɉ��Z
			if(w_max < i){w_max = i;}	//�ő�l�i�[
			if(w_min > i){w_min = i;}	//�ŏ��l�i�[
			w_ave += (double)i;	//���όv�Z�p�ɉ��Z
		}
	}
	w_ave = w_ave / w_sum;	//�S��f���ς����߂Ă���

	//�����x���ő�ɂȂ邵�����l�����߂遨�N���X�ԕ��U���ő�ɂȂ�
	//�������lt�̒l�����߂�
	double distb_max = -1.0;	//�ő�̃N���X�ԕ��U
	//���ő�N���X�ԕ��U���́�
	int t_max = 0;	//�������lt
	int n1_max=0;	int n2_max=0;	//�e�N���X�̉�f�̐�
	double ave1_max=0.0; double ave2_max=0.0; //�e�N���X�̕��ϒl
	double dis1_max=0.0; double dis2_max=0.0; //�e�N���X�̕��U�l

	for(int t =0; t<256;t++){
		int num1=0; //�N���X1�̉�f��
		double ave1=0.0;	//�N���X1�̉�f����
		double dis1=0.0;	//�N���X1�̕��U
		int tmp=0;	//���ς����߂邽�߂̍�ƕϐ�
		//�N���X1���̃q�X�g�O����
		for(int i=0;i<t;i++){
			num1 += histdata[i];
			tmp += i * histdata[i];
		}
		//�N���X1���ϒl
		ave1 = (double)tmp/num1;
		for(int i=0;i<t;i++){
			dis1 = dis1 + ((i-ave1)*(i-ave1)/num1);
		}
		//���U�����߂�
		dis1 = dis1 / num1;

		//�N���X2�����l�ɋ��߂�
		tmp = 0;
		int num2=0; //�N���X2�̉�f��
		double ave2=0.0;	//�N���X2�̉�f����
		double dis2=0.0;	//�N���X2�̕��U
		//�N���X2���̃q�X�g�O����
		for(int i=t;i<256;i++){
			num2 += histdata[i];
			tmp += i * histdata[i];
		}
		//�N���X2���ϒl
		ave2 = (double)tmp/num2;
		for(int i=t;i<256;i++){
			dis2 = dis2 + ((i-ave2)*(i-ave2)/num2);
		}
		//���U�����߂�
		dis2 = dis2 / num2;

		//�N���X�ԕ��U
		double distb = num1*num2*(ave1-ave2)*(ave1-ave2) / (num1+num2)*(num1+num2);
		if(distb_max < distb){
			distb_max = distb;
			t_max = t;
			n1_max = num1;	n2_max = num2;
			ave1_max = ave1;	ave2_max = ave2;
			dis1_max = dis1;	dis2_max = dis2;
		}
	}
	
	//�e�l���o�͂���
	std::cout << "�������l�F" << t_max << std::endl;
	std::cout << "\n�N���X1\n";
	std::cout << "��f���F" << n1_max << std::endl;
	std::cout << "���ϒl�F" << ave1_max << std::endl;
	std::cout << "���U�l�F" << dis1_max << std::endl;
	std::cout << "\n�N���X2\n";
	std::cout << "��f���F" << n2_max << std::endl;
	std::cout << "���ϒl�F" << ave2_max << std::endl;
	std::cout << "���U�l�F" << dis2_max << std::endl;
	std::cout << "\n�N���X�ԕ��U" << distb_max << std::endl;

	cv::threshold(img,img,t_max,255.0,CV_THRESH_BINARY);	//2�l��
	if(cv::imwrite("output.bmp", img) == false){	//�ۑ��̐��۔���
		std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
	cv::waitKey();
	return 0;
}
