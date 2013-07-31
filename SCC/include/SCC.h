#include <opencv2/opencv.hpp>
#include <vector>
#include "Util.h"
#include "sparseCoding.h"

using std::vector;
using namespace cv;
using namespace MatrixUtils;
using namespace SparseCoding;

namespace SCC{
Mat L1QP_FeatureSign_Set_Zhang(const Mat& X, const Mat& B, const Mat& p, const Mat& sigma, double beta, double gamma);
//Mat L1QP_FeatureSign_Set_Yang(double lambda, const Mat& A, const Mat& b);

Mat CCCP(const Mat& X, const Mat& B, const Mat& W, const Mat& sigma, double beta, double gamma1, double gamma2);

vector<Mat> semantic_neighbours(const Mat qfea, const Mat f, const Mat W, const Mat sigma, double beta, double gamma1, double gamma2);

double retrievalScore( const InputArray& queryFea,
		const InputArray& candidateFea,
		const InputArray& codebook );
}
