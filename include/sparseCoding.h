#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <nlopt.hpp>
#include "Util.h"

using namespace std;
using namespace cv;
using namespace MatrixUtils;
using namespace nlopt;

namespace SparseCoding{
	vector<Mat> reg_sparse_coding(const Mat X, int num_bases, const Mat Sigma, double beta, double gamma, int num_iters, bool isParallel = false);

	Mat L1QP_FeatureSign_Set(const Mat X, const Mat B, const Mat Sigma, double beta, double gamma);

	Mat L1QP_FeatureSign_Set_Parallel(const Mat X, const Mat B, const Mat Sigma, double beta, double gamma, int threads = 8);

	void L1QP_FeatureSign_Set_Rng(int rngStart, int rngEnd, const Mat X, const Mat B, const Mat Sigma, Mat S, double beta, double gamma);

	Mat L1QP_FeatureSign_Yang(double lambda, const Mat A, const Mat b );

	Mat l2ls_learn_basis_dual(Mat X, Mat S, int l2norm);

	double f(const std::vector<double> &x, std::vector<double> &grad, void* f_data);

	double getObj(Mat X, Mat B, Mat S, Mat Sigma, double beta, double gamma);

	double fobj_basis_dual(const std::vector<double> &x, std::vector<double> &grad, void* f_data);

	struct ObjParam{
		Mat dual_lambda;
		Mat SSt;
		Mat Xst;
		double c;
		double trXXt;
	};

// 	Mat conjugateGradient(Mat dual_lambda, Mat SSt, Mat Xst, double c, double trXXt)
// 	{
// 		int dim = dual_lambda.rows;
// 		int k = 0;
// 		Mat d;
// 		Mat v;
// 		Mat x = dual_lambda;
// 		vector<double> grad(dim);
// 		Mat gradient;
// 		ObjParam param;
// 		param.c = c;
// 		param.dual_lambda = dual_lambda;
// 		param.SSt = SSt;
// 		param.trXXt = trXXt;
// 		param.Xst = Xst;
// 
// 		do 
// 		{
// 			double obj = fobj_basis_dual(x, grad, &param);
// 			gradient = Mat(grad);
// 			v = gradient + (gradient.t());
// 		} while (sum(gradient).val[0] > 1.0e-6);
// 	}
}