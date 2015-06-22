#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img[2] = 
		{cv::imread("Blur.bmp", 0),cv::imread("GaussianBlur.bmp", 0)};
	
	for(int i=0;i<2;i++){
		if (img[i].empty())	//ƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İ¸”s
		{
			std::cout << "ƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½" << std::endl;
			return -1;
		}
	}
	
	//Œ³‰æ‘œ‚Ì•\¦
	cv::namedWindow("Blur Image");	//ƒEƒBƒ“ƒhƒE‚Ì¶¬
	cv::imshow("Blur Image",img[0]);	//‰æ‘œ‚Ì•`‰æ
	cv::namedWindow("GaussianBlur Image");	//ƒEƒBƒ“ƒhƒE‚Ì¶¬
	cv::imshow("GaussianBlur Image",img[1]);	//‰æ‘œ‚Ì•`‰æ

	//ƒJ[ƒlƒ‹‚Ì€”õ
	cv::Mat kernel = cv::Mat::ones(3,3,CV_32F);
	double defk = 1.0;
	double k[3][3] = {{-defk,-defk,-defk},{-defk,1 + 8*defk,-defk},{-defk,-defk,-defk}};

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			kernel.at<float>(i,j) *= k[i][j];
		}
	}
	//o—Í‰æ‘œ‚Ì€”õ
	cv::Mat distimg;

	//•½‹Ï‰»‰æ‘œ‚Ì‘N‰s‰»
	cv::filter2D(img[0], distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image1_1.bmp", distimg) == false){	//•Û‘¶‚Ì¬”Û”»’è
		std::cout << "ƒtƒ@ƒCƒ‹‚Ì•Û‘¶‚É¸”s" << std::endl;
		return -1;
	}
	
	//‘N‰s‰»‰æ‘œ‚Ì‘N‰s‰»
	cv::filter2D(distimg, distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image1_2.bmp", distimg) == false){	//•Û‘¶‚Ì¬”Û”»’è
		std::cout << "ƒtƒ@ƒCƒ‹‚Ì•Û‘¶‚É¸”s" << std::endl;
		return -1;
	}


	//ƒKƒEƒVƒAƒ“‰æ‘œ‚Ì‘N‰s‰»
	cv::filter2D(img[1], distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image2_1.bmp", distimg) == false){	//•Û‘¶‚Ì¬”Û”»’è
		std::cout << "ƒtƒ@ƒCƒ‹‚Ì•Û‘¶‚É¸”s" << std::endl;
		return -1;
	}

	//‘N‰s‰»‰æ‘œ‚Ì‘N‰s‰»
	cv::filter2D(distimg, distimg, 0,kernel);
	if(cv::imwrite("Sharpened Image2_2.bmp", distimg) == false){	//•Û‘¶‚Ì¬”Û”»’è
		std::cout << "ƒtƒ@ƒCƒ‹‚Ì•Û‘¶‚É¸”s" << std::endl;
		return -1;
	}
	cv::waitKey();	//ƒL[‚ª‰Ÿ‚³‚ê‚é‚Ü‚Å‘Ò‚Â
	return 0;
}