#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>
#include <cstdio>
#include "FeatureItem.h"

using namespace std;
using namespace cv;

namespace SIFT{
	const double pi=3.1415926;

	Mat mcos(Mat src);
	Mat matan2(Mat src1,Mat src2);
	float totalSumO(Mat src);//计算所有元素的总和;

	Mat gradientX(Mat src);
	Mat gradientY(Mat src);

	Mat sum_every_col(Mat src);
	Mat getNum(Mat src,int y_lo,int y_hi,int x_lo,int x_hi);
	Mat Less(Mat src,float num);

	Mat compare(Mat src,float num);
	Mat compareB(Mat src,float num);
	void assign(Mat dst,Mat var,Mat src);
	Mat suppresss(Mat src,float num);
	Mat search(Mat src,Mat dst);//把dst中为1的src中对应行找出来，返回;
	Mat sum_row(Mat src);
	Mat change(Mat src);
	Mat repmat(Mat src,int height,int width);
	Mat Add(Mat src, float x);

	Mat create(float start,float end,float step);
	Mat reshapeX(Mat I);//变为一维矩阵;
	Mat reshapeY(Mat I);//变为n维矩阵;

	Mat meshgrid_X(Mat I1,Mat I2);
	Mat meshgrid_Y(Mat I1,Mat I2);
	Mat deleteO(Mat src);
	Mat gaussian(int wid,float sigma);
	Mat im2double(Mat src);
	Mat square(Mat src);//对每个元素求平方;
	Mat filter2(Mat mask,Mat src);
	Mat sp_find_sift_grid(Mat I,Mat gridX,Mat gridY,int patchSize, float sigma_edge);

	Mat sp_normalize_sift_len(Mat sift_arr);

	Mat sp_normalize_sift_arr(Mat sift_arr,float threshold);
	FeatureItem CalculateSiftDescriptor(Mat Img, int gridSpacing, int patchSize, int maxImSize, float nrml_threshold);
	FeatureItem CalculateSiftDescriptorFromFile(const string& filename, int gridSpacing, int patchSize, int maxImSize, float nrml_threshold);
}
