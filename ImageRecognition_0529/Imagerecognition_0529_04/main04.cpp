#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("A.png",0);	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}	

	//収縮
	cv::Mat disterode;
	cv::erode(img,disterode,cv::Mat());
	if(cv::imwrite("erode1.bmp", disterode) == false){	//保存の成否判定
		std::cout << "erode1ファイルの保存に失敗" << std::endl;
		return -1;
	}
	cv::erode(disterode,disterode,cv::Mat());
	if(cv::imwrite("erode2.bmp", disterode) == false){	//保存の成否判定
		std::cout << "erode2ファイルの保存に失敗" << std::endl;
		return -1;
	}

	//膨張
	cv::Mat distdilate;
	cv::dilate(img,distdilate,cv::Mat());
	if(cv::imwrite("dilate1.bmp", distdilate) == false){	//保存の成否判定
		std::cout << "dilate1ファイルの保存に失敗" << std::endl;
		return -1;
	}
	cv::dilate(distdilate,distdilate,cv::Mat());
	if(cv::imwrite("dilate2.bmp", distdilate) == false){	//保存の成否判定
		std::cout << "dilate2ファイルの保存に失敗" << std::endl;
		return -1;
	}

	//先ほど2回収縮した画像のオープニング
	cv::Mat etod;
	cv::dilate(disterode,etod,cv::Mat());	//1回目
	cv::dilate(etod,etod,cv::Mat());		//2回目
	if(cv::imwrite("etod.bmp", etod) == false){	//保存の成否判定
		std::cout << "etodファイルの保存に失敗" << std::endl;
		return -1;
	}


	//先ほど2回膨張した画像のクロージング
	cv::Mat dtoe;
	cv::erode(distdilate,dtoe,cv::Mat());	//1回目
	cv::erode(dtoe,dtoe,cv::Mat());			//2回目
	if(cv::imwrite("dtoe.bmp", dtoe) == false){	//保存の成否判定
		std::cout << "dtoeファイルの保存に失敗" << std::endl;
		return -1;
	}
	
	return 0;
}