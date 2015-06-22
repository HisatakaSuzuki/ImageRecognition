#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img[3] = 
		{cv::imread("GaussianBlur Image(3_3).bmp", 0),cv::imread("GaussianBlur Image(5_5).bmp", 0),cv::imread("GaussianBlur Image(7_7).bmp", 0)};
	
	for(int i=0;i<3;i++){
		if (img[i].empty())	//�t�@�C���̓ǂݍ��ݎ��s
		{
			std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
			return -1;
		}
	}

	//�K�E�V�A���t�B���^��K�p�����摜�͉ۑ�1�̃v���O�����Ő���
	//���͂�3�摜�ɑ΂���K�̒l��0.5�`2.0�܂ł�0.5���ω������A
	//�ek�̒l�̂Ƃ��ɘA������10��N�s���t�B���^���������摜���o�͂���


	//�I���W�i���摜���R�s�[����
	cv::Mat copy[3];
	for(int i=0;i<3;i++){
		copy[i] = img[i];
	}

	//�摜���o��
	//�o�͉摜�̖��O�́uImageNum_KNum_TimeNum.bmp�v�Ƃ���
	for(int i=0;i<3;i++){
		cv::Mat distimg;	//�o�͉摜�̏���
		double defk = 0.5;	//k�̒l�̏�����
		//k�̒l�����߂��
		do{
			//�J�[�l���̏���
			cv::Mat kernel = cv::Mat::ones(3,3,CV_32F);
			double k[3][3] = {{-defk,-defk,-defk},{-defk,1 + 8*defk,-defk},{-defk,-defk,-defk}};
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					kernel.at<float>(i,j) *= k[i][j];
				}
			}

			//�摜��10��o��
			for(int j=0;j<10;j++){
				cv::filter2D(img[i], distimg, 0,kernel);
				std::string winname = "Image("+ std::to_string(i)+")_K("+std::to_string(defk)+"_Time("+std::to_string(j+1)+")";	//�t�@�C����
				if(cv::imwrite(winname+".bmp", distimg) == false){	//�ۑ��̐��۔���
					std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
					return -1;
				}else{
					std::cout << winname + "���o�͂��܂����B" << std::endl;
				}
				img[i] = distimg;	//�Ō�Ɏ��Ƀt�B���^�[��������摜���A���݂̏o�͌��ʂōX�V
			}
			img[i] = copy[i]; //img�̒��g�����摜�ŏ㏑��
			defk += 0.5;
		}while(defk<=2.0);
	}

	cv::waitKey();	//�L�[���������܂ő҂�
	return 0;
}