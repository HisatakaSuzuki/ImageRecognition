#include <iostream>
#include <opencv2\/opencv.hpp>
#include <sstream>	//ostringstream

int main(int argc, const char * argv[]){
	cv::Mat origin[4];

	//ファイルの読み込み
	for(int i=0;i<4;i++){
		std::ostringstream oss;
		oss << "image_0" << (i+1) << ".jpg";
		origin[i] = cv::imread(oss.str(),0); //階調画像読み込み
		if (origin[i].empty())	//ファイルの読み込み失敗
		{
			std::cout << "ファイルの読み込みに失敗しました：" << i << std::endl;
			return -1;
		}
	}

	//差分image01-image02
	cv::Mat sub_12(origin[0].rows,origin[0].cols,CV_8UC1);
	cv::absdiff(origin[0],origin[1],sub_12);	//グレースケール画像から差分を抽出
	cv::imwrite("sub12_1.bmp", sub_12);			//差分画像を出力
	cv::threshold(sub_12,sub_12,13.0,255.0,CV_THRESH_BINARY);	//差分画像を2値化
	cv::imwrite("sub12_2.bmp", sub_12);			//2値化差分画像を出力

	//差分image03-image04
	cv::Mat sub_34(origin[2].rows,origin[3].cols,CV_8UC1);
	cv::absdiff(origin[2],origin[3],sub_34);	//グレースケール画像から差分を抽出
	cv::imwrite("sub34_1.bmp", sub_34);			//差分画像を出力
	cv::threshold(sub_34,sub_34,30.0,255.0,CV_THRESH_BINARY);	//差分画像を2値化
	cv::imwrite("sub34_2.bmp", sub_34);			//2値化差分画像を出力

	//cv::namedWindow("image");	//ウィンドウの生成
	//cv::imshow("image", sub_34);	//画像の描画
	return 0;
}