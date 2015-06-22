#include <iostream>
#include <opencv2\/opencv.hpp>

void Thinning(cv::Mat &img)
{
  const int width = img.cols;
  const int height = img.rows;
 
  cv::rectangle(img, cv::Point(0, 0), cv::Point(width - 1, height - 1), CV_RGB(0, 0, 0));
 
       
  // 4�ߖT�p�k�ޏ����p�̃J�[�l���𐶐�
  cv::Mat four_neighbor = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
 
  int step = 0; // �J��Ԃ���
  while (1) {
    step++;             // �J��Ԃ�����1���₷
 
    // ����f = 4�ߖT��0��f����ȏ㑶�݂���1��f ��I�яo��
 
    cv::Mat candidate = img.clone();
    cv::erode(candidate, candidate, four_neighbor);
    candidate = img - candidate;
 
    // ���ォ�珇���������āA���邩�A���Ȃ����𔻒f����
    int num_delete = 0;         // �������f�̐���ێ�
    for (int y = 1; y < height - 1; y++) {
      for (int x = 1; x < width - 1; x++) {
          if (candidate.at<uchar>(y, x) == 0) { // ���������?
          continue;     // �����łȂ���Ύ��̉�f�̏�����
        }
        // ���Ӊ�f�̏�Ԃ𒲂ׂ�
        int dx[8] = {1,  1,  0, -1, -1, -1,  0,  1};
        int dy[8] = {0, -1, -1, -1,  0,  1,  1,  1};
        unsigned char n[8];     // �אډ�f�̏��
        int num = 0;                    // �אډ�f��
        for (int i = 0; i < 8; i++) {
          n[i] = img.at<uchar>(y + dy[i], x + dx[i]) ? 1 : 0;
          num += n[i];
        }
        // 8�ߖT��"1"���O�ȏ�Ȃ�������A�����ł��Ȃ��̂Ŏ��̉�f��
        if (num < 3) {
          continue;
        }
        // �A�����𒲂ׂ�
        int m = 0;      // �A����
        for (int i = 0; i < 4; i++) {
          int k0 = i * 2;
          int k1 = (k0 + 1) % 8;
          int k2 = (k1 + 1) % 8;
          m += n[k0] * (1 - n[k1] * n[k2]);
        }
        // �A������1�Ȃ炻�̉�f�͏����\�Ȃ̂ŁA��������
        if (m == 1) {
          img.at<uchar>(y, x) = 0;
          num_delete++;
        }
      }
    }
 
    // �I������
    if (num_delete == 0) {              // ���f�����Ȃ�������
      break;                                    // �I��
    }
  }
}

int main(int argc, const char * argv[]){
	cv::Mat img = cv::imread("G.png",0);	//�摜�t�@�C���̓ǂݍ���
	if (img.empty())	//�t�@�C���̓ǂݍ��ݎ��s
	{
		std::cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return -1;
	}	
 
    // �א���
    Thinning(img);
	if(cv::imwrite("output.bmp", img) == false){	//�ۑ��̐��۔���
		std::cout << "erode2�t�@�C���̕ۑ��Ɏ��s" << std::endl;
		return -1;
	}
   return 0;
}

