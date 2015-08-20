#include <iostream>
#include <opencv2\opencv.hpp>

cv::Mat matchTemp(cv::Mat tar,cv::Mat tmp,int form);

int main(int argc, const char * argv[]){
	cv::Mat tarimg[8];
	for(int i=0;i<8;i++){
		tarimg[i] = cv::imread("Dice.png");	//target画像ファイルの読み込み
	if (tarimg[i].empty())	//ファイルの読み込み失敗
	{
		std::cout << "tarファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}
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

	//結果の保持配列
	cv::Mat resimg[8];
	double maxval[8];	//最大値
	cv::Point maxloc[8];	//最大位置

	for(int i=0;i<8;i++){
		//DiceTmp1によるテンプレートマッチング
		if(i<4){
			resimg[i] = matchTemp(tarimg[i],tmpimg,i);
		}else{//DiceTmp2によるテンプレートマッチング
			resimg[i] = matchTemp(tarimg[i],tmp2img,i-4);
		}
		cv::minMaxLoc(resimg[i],NULL,&maxval[i],NULL,&maxloc[i]);
		cv::rectangle(tarimg[i],cv::Point(maxloc[i].x,maxloc[i].y),cv::Point(maxloc[i].x+tmp2img.rows,maxloc[i].y+tmp2img.cols),cv::Scalar(0,0,255),3,4);
		std::cout << maxval[i] << "," << maxloc[i] << std::endl;
		//画像の保存
		if(cv::imwrite(std::to_string(i) + "res.png", resimg[i]) == false){	//保存の成否判定
			std::cout << "ファイルの保存に失敗" << std::endl;
			return -1;
		}
	}
	return 0;
}
//テンプレートの種類を引数で場合分けするための関数
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