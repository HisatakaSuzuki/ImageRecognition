#include <iostream>
#include <opencv2\/opencv.hpp>
#include <math.h>
#include <fstream>

#define M_PI 3.14159265358979 /* 円周率 */

double gaussianDis(double sigma, int x, int y){
	double cal1 = exp(-1*((x*x + y*y) / (2 * sigma *sigma)));
	double ans = cal1 / (2 * M_PI * sigma * sigma);
	return ans;
}

int main(int argc, const char * argv[]){
	std::ofstream ofs("output.txt");
	ofs << "σ=0.8, x={-1,0,1}, y={-1,0,1}のときの値：\n";
	double ans1[3][3];
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			ans1[i][j] = gaussianDis(0.8,(i-1),(j-1));
			ofs  << ans1[i][j] << ",";
		}
		ofs << "\n";
	}
	//データの出力/ファイルにも出力
	
	ofs << "σ=1.0, x={-2,-1,0,1,2}, y={-2,-1,0,1,2}のときの値：\n";
	double ans2[5][5];
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			ans2[i][j] = gaussianDis(1.0,(i-2),(j-2));
			ofs << ans2[i][j] << ",";
		}
		ofs << "\n";
	}
	cv::waitKey();	//キーが押されるまで待つ
	return 0;
}