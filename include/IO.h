#include <opencv2/opencv.hpp>
#include <map>
#include <string>
#include <boost/filesystem.hpp>
#include <iostream>

using namespace std;
using namespace cv;
using namespace boost::filesystem;

namespace IOUtils{
	Mat readMatrixFromYML( const path filename );

	void saveMatrixToYML( const path filename, const Mat& m );
}
