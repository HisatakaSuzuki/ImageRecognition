#include <iostream>
#include <opencv2\/opencv.hpp>
#include <sstream>	//ostringstream
#include <math.h>

int main(int argc, const char * argv[]){
	cv::Mat backAB =  cv::imread("background_AB.jpg"); //�K���摜�ǂݍ���
	cv::Mat backC =  cv::imread("background_C.jpg"); //�K���摜�ǂݍ���
	if (backAB.empty() || backC.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����F"  << std::endl;
		return -1;
	}
	cv::VideoCapture capA("movie_A.mp4");
	cv::VideoCapture capB("movie_B.mp4");
	cv::VideoCapture capC("movie_C.mp4");
	
	//�t���[���ێ�
	cv::Mat frm;
	cv::Mat sub;
	cv::cvtColor(backAB, backAB,CV_RGB2GRAY);//�O���[�X�P�[���ϊ�
	int frame = capA.get(CV_CAP_PROP_FRAME_COUNT);


	// �摜�\���p�̃E�B���h�E�𐶐�����
	cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
	//do{
	//	capA >> frmA;
	//	cv::Mat gfrmA;
	//	cv::cvtColor(frmA, gfrmA,CV_RGB2GRAY);//�O���[�X�P�[���ϊ�	

	//	//����image01-image02
	//	cv::absdiff(backAB,gfrmA,sub);
	//	cv::threshold(sub,sub,40.0,255.0,CV_THRESH_BINARY);	//2�l��
	//	
	//	////�}�X�N����
	//	cv::Mat dist;
	//	frmA.copyTo(dist,sub);
	//	//sub.copyTo(frmA,sub);

	//	//// �擾�����摜�f�[�^���E�B���h�E�\������
	//	cv::imshow("image", dist);
	//	if (i == 30){
	//		cv::imwrite("result.bmp", dist);
	//	}
	//	i++;
	//	if(cv::waitKey(30) >= 0) break;
	//}while(capA.grab() == true);
	cv::VideoWriter vw("movie.avi",CV_FOURCC('W','M','V','2'),capB.get(CV_CAP_PROP_FPS),cv::Size(capB.get(CV_CAP_PROP_FRAME_WIDTH),capB.get(CV_CAP_PROP_FRAME_HEIGHT)));
	for(int i=0;i<frame;i++){
		capB >> frm;
		cv::Mat gfrm;
		cv::cvtColor(frm, gfrm,CV_RGB2GRAY);//�O���[�X�P�[���ϊ�	

		//����
		cv::absdiff(backAB,gfrm,sub);
		cv::threshold(sub,sub,40.0,255.0,CV_THRESH_BINARY);	//2�l��
		
		////�}�X�N����
		cv::Mat dist;
		frm.copyTo(dist,sub);
		//sub.copyTo(frmA,sub);

		vw << dist;

		//// �擾�����摜�f�[�^���E�B���h�E�\������
		cv::imshow("image", dist);
		if (i == 30){
			cv::imwrite("result__.bmp", dist);
		}
		if(cv::waitKey(30) >= 0) break;
	}

}