#include <iostream>
#include <opencv2\opencv.hpp>

cv::Mat matchTemp(cv::Mat tar,cv::Mat tmp,int form);

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
    cv::Mat tmp2img = cv::imread("DiceTmp2.png");	//tmp2�摜�t�@�C���̓ǂݍ���
	if (tmpimg.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "tmp2�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}
    
    //DiceTmp1�ɂ��e���v���[�g�}�b�`���O
	cv::Mat result = matchTemp(tarimg,tmp2img,3);
	
	double minval, maxval;   //�ő�/�ŏ��l
	cv::Point minloc, maxloc;   //�ő�/�ŏ��ʒu
    cv::minMaxLoc(result, &minval, &maxval, &minloc, &maxloc);
    //��`�`��
	cv::rectangle(tarimg,cv::Point(maxloc.x,maxloc.y),cv::Point(maxloc.x+tmp2img.rows,maxloc.y+tmp2img.cols),cv::Scalar(0,0,255),1,4);
	std::cout << maxval << std::endl;
    //�摜�̕ۑ�
	//if(cv::imwrite("7.png", tarimg) == false){	//�ۑ��̐��۔���
	//    std::cout << "�t�@�C���̕ۑ��Ɏ��s" << std::endl;
	//    return -1;
	//}

}

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