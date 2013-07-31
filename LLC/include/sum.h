#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat sumcol(Mat X);

Mat sumrow(Mat X);
Mat MatCeil(Mat X);

Mat Maxrow(Mat X,Mat Y,int bId,int com);
Mat Sort(Mat X);
double sumtrace(Mat X);
Mat Col(Mat X);
