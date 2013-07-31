#include <opencv2/opencv.hpp>
#include "FeatureItem.h"
#include <string>
#include <vector>
#include "sparseCoding.h"
using std::string;
using cv::Mat;

namespace SparseCoding{
	class SparseCoder{
	public:
		SparseCoder();
		vector<Mat> encode(const Mat X, const string& outFilename = "");

		void loadConfig(const string& filename);
		void saveConfig(const string& filename);

		int num_bases;
		Mat Sigma;
		double beta;
		double gamma;
		int num_iters;
		bool isParallel;
		int threads;
	private:
	};
}
