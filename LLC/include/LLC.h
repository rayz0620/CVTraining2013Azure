#include <opencv2/opencv.hpp>
#include "FeatureItem.h"
#include "sum.h"

namespace LLC
{
	cv::Mat LLC_pooling( FeatureItem feaSet,Mat B,Mat pyramid,int knn );
	cv::Mat LLC_coding_appr( Mat B,Mat X,int knn );
}