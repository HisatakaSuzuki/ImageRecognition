#include <iostream>
#include <opencv2\/opencv.hpp>

int main(int argc, const char * argv[]){
	cv::Mat img[3] = 
		{cv::imread("GaussianBlur Image(3_3).bmp", 0),cv::imread("GaussianBlur Image(5_5).bmp", 0),cv::imread("GaussianBlur Image(7_7).bmp", 0)};
	
	for(int i=0;i<3;i++){
		if (img[i].empty())	//ファイルの読み込み失敗
		{
			std::cout << "ファイルの読み込みに失敗しました" << std::endl;
			return -1;
		}
	}

	//ガウシアンフィルタを適用した画像は課題1のプログラムで生成
	//入力の3画像に対してKの値を0.5～2.0までで0.5ずつ変化させ、
	//各kの値のときに連続して10回鮮鋭化フィルタをかけた画像を出力する


	//オリジナル画像をコピーする
	cv::Mat copy[3];
	for(int i=0;i<3;i++){
		copy[i] = img[i];
	}

	//画像を出力
	//出力画像の名前は「ImageNum_KNum_TimeNum.bmp」とする
	for(int i=0;i<3;i++){
		cv::Mat distimg;	//出力画像の準備
		double defk = 0.5;	//kの値の初期化
		//kの値を決める回数
		do{
			//カーネルの準備
			cv::Mat kernel = cv::Mat::ones(3,3,CV_32F);
			double k[3][3] = {{-defk,-defk,-defk},{-defk,1 + 8*defk,-defk},{-defk,-defk,-defk}};
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					kernel.at<float>(i,j) *= k[i][j];
				}
			}

			//画像を10回出力
			for(int j=0;j<10;j++){
				cv::filter2D(img[i], distimg, 0,kernel);
				std::string winname = "Image("+ std::to_string(i)+")_K("+std::to_string(defk)+"_Time("+std::to_string(j+1)+")";	//ファイル名
				if(cv::imwrite(winname+".bmp", distimg) == false){	//保存の成否判定
					std::cout << "ファイルの保存に失敗" << std::endl;
					return -1;
				}else{
					std::cout << winname + "を出力しました。" << std::endl;
				}
				img[i] = distimg;	//最後に次にフィルターをかける画像を、現在の出力結果で更新
			}
			img[i] = copy[i]; //imgの中身を元画像で上書き
			defk += 0.5;
		}while(defk<=2.0);
	}

	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}