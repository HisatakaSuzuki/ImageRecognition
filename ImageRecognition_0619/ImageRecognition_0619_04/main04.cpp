#include <iostream>
#include <opencv2\opencv.hpp>

cv::Mat matchTemp(cv::Mat tar,cv::Mat tmp,int form);

int main(int argc, const char * argv[]){
	cv::Mat tarimg[8];
	for(int i=0;i<8;i++){
		tarimg[i] = cv::imread("Dice.png");	//target�摜�t�@�C���̓ǂݍ���
	if (tarimg[i].empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "tar�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
	}
	
	cv::Mat tmpimg = cv::imread("DiceTmp1.png");	//tmp�摜�t�@�C���̓ǂݍ���
	if (tmpimg.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "tmp�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
    cv::Mat tmp2img = cv::imread("DiceTmp2.png");	//tmp2�摜�t�@�C���̓ǂݍ���
	if (tmpimg.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "tmp2�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}

	//���ʂ̕ێ��z��
	cv::Mat resimg[8];
	double maxval[8];	//�ő�l
	cv::Point maxloc[8];	//�ő�ʒu

	for(int i=0;i<8;i++){
		//DiceTmp1�ɂ��e���v���[�g�}�b�`���O
		if(i<4){
			resimg[i] = matchTemp(tarimg[i],tmpimg,i);
		}else{//DiceTmp2�ɂ��e���v���[�g�}�b�`���O
			resimg[i] = matchTemp(tarimg[i],tmp2img,i-4);
		}
		cv::minMaxLoc(resimg[i],NULL,&maxval[i],NULL,&maxloc[i]);
		cv::rectangle(tarimg[i],cv::Point(maxloc[i].x,maxloc[i].y),cv::Point(maxloc[i].x+tmp2img.rows,maxloc[i].y+tmp2img.cols),cv::Scalar(0,0,255),3,4);
		std::cout << maxval[i] << "," << maxloc[i] << std::endl;
		//�摜�̕ۑ�
		if(cv::imwrite(std::to_string(i) + "res.png", resimg[i]) == false){	//�ۑ��̐��۔���
			std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
			return -1;
		}
	}
	return 0;
}
//�e���v���[�g�̎�ނ������ŏꍇ�������邽�߂̊֐�
cv::Mat matchTemp(cv::Mat tar,cv::Mat tmp,int form){
	cv::Mat result;
    switch(form){
	    case 0: cv::matchTemplate(tar,tmp,result,CV_TM_CCORR);break;
	    case 1: cv::matchTemplate(tar,tmp,result,CV_TM_CCORR_NORMED);break;
        case 2: cv::matchTemplate(tar,tmp,result,CV_TM_CCOEFF);break;
        case 3: cv::matchTemplate(tar,tmp,result,CV_TM_CCOEFF_NORMED);break;
	}
	return result;
}