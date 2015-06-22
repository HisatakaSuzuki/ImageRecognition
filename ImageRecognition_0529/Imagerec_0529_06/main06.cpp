#include <iostream>
#include <opencv2\/opencv.hpp>

void Thinning(cv::Mat &img)
{
  const int width = img.cols;
  const int height = img.rows;
 
  cv::rectangle(img, cv::Point(0, 0), cv::Point(width - 1, height - 1), CV_RGB(0, 0, 0));
 
       
  // 4近傍用縮退処理用のカーネルを生成
  cv::Mat four_neighbor = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
 
  int step = 0; // 繰り返し数
  while (1) {
    step++;             // 繰り返し数を1増やす
 
    // 候補画素 = 4近傍に0画素が一つ以上存在する1画素 を選び出す
 
    cv::Mat candidate = img.clone();
    cv::erode(candidate, candidate, four_neighbor);
    candidate = img - candidate;
 
    // 左上から順次走査して、削れるか、削れないかを判断する
    int num_delete = 0;         // 削った画素の数を保持
    for (int y = 1; y < height - 1; y++) {
      for (int x = 1; x < width - 1; x++) {
          if (candidate.at<uchar>(y, x) == 0) { // 自分が候補?
          continue;     // そうでなければ次の画素の処理へ
        }
        // 周辺画素の状態を調べる
        int dx[8] = {1,  1,  0, -1, -1, -1,  0,  1};
        int dy[8] = {0, -1, -1, -1,  0,  1,  1,  1};
        unsigned char n[8];     // 隣接画素の状態
        int num = 0;                    // 隣接画素数
        for (int i = 0; i < 8; i++) {
          n[i] = img.at<uchar>(y + dy[i], x + dx[i]) ? 1 : 0;
          num += n[i];
        }
        // 8近傍に"1"が三つ以上なかったら、消去できないので次の画素へ
        if (num < 3) {
          continue;
        }
        // 連結数を調べる
        int m = 0;      // 連結数
        for (int i = 0; i < 4; i++) {
          int k0 = i * 2;
          int k1 = (k0 + 1) % 8;
          int k2 = (k1 + 1) % 8;
          m += n[k0] * (1 - n[k1] * n[k2]);
        }
        // 連結数が1ならその画素は消去可能なので、消去する
        if (m == 1) {
          img.at<uchar>(y, x) = 0;
          num_delete++;
        }
      }
    }
 
    // 終了判定
    if (num_delete == 0) {              // 一画素も削らなかったら
      break;                                    // 終了
    }
  }
}

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("G.png",0);	//画像ファイルの読み込み
	if (img.empty())	//ファイルの読み込み失敗
	{
		std::cout << "ファイルの読み込みに失敗しました" << std::endl;
		return -1;
	}	
 
    // 細線化
    Thinning(img);
	if(cv::imwrite("output.bmp", img) == false){	//保存の成否判定
		std::cout << "erode2ファイルの保存に失敗" << std::endl;
		return -1;
	}
   return 0;
}

