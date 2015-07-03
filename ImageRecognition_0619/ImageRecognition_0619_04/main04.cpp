#include <iostream>
#include <opencv2\opencv.hpp>

cv::Mat matchTemp(cv::Mat tar,cv::Mat tmp,int form);

int main(int argc, const char * argv[]){
	cv::Mat tarimg = cv::imread("Dice.png");	//target画像ファイルの読み込み
	if (tarimg.empty())	//ファイルの読み込み失敗
	{
		std::cout << "tarファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
	cv::Mat tmpimg = cv::imread("DiceTmp1.png");	//tmp画像ファイルの読み込み
	if (tmpimg.empty())	//ファイルの読み込み失敗
	{
		std::cout << "tmpファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
    cv::Mat tmp2img = cv::imread("DiceTmp2.png");	//tmp2画像ファイルの読み込み
	if (tmpimg.empty())	//ファイルの読み込み失敗
	{
		std::cout << "tmp2ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
    
    //DiceTmp1によるテンプレートマッチング
	cv::Mat result = matchTemp(tarimg,tmp2img,3);
	
	double minval, maxval;   //最大/最小値
	cv::Point minloc, maxloc;   //最大/最小位置
    cv::minMaxLoc(result, &minval, &maxval, &minloc, &maxloc);
    //矩形描画
	cv::rectangle(tarimg,cv::Point(maxloc.x,maxloc.y),cv::Point(maxloc.x+tmp2img.rows,maxloc.y+tmp2img.cols),cv::Scalar(0,0,255),1,4);
	std::cout << maxval << std::endl;
    //画像の保存
	//if(cv::imwrite("7.png", tarimg) == false){	//保存の成否判定
	//    std::cout << "ファイルの保存に失敗" << std::endl;
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