#include "sparseCoding.h"
#include "IO.h"
#include <ctime>
#include <sstream>
#include <boost/thread.hpp>
#include <boost/threadpool.hpp>
#define MAT_TYPE CV_32F
using namespace IOUtils;

vector<Mat> SparseCoding::reg_sparse_coding( const Mat X, int num_bases, const Mat Sigma, double beta, double gamma, int num_iters, bool isParallel /*= false*/ )
{
	// Statistics not implemented
	int mat_type = X.type();
	int patch_size = X.rows;

	int batch_size = X.cols;
	string filename;

	int VAR_basis = 1;

	// Initialize basis
	Mat initB(patch_size, num_bases, mat_type);
	randn(initB, 0, 1);
	for (int i = 0; i < initB.size().width; i++)
	{
		normalize(initB.col(i), initB.col(i));
	}

	{
		Mat sqrtB;
		cv::sqrt(colSum(initB.mul(initB)), sqrtB);
		initB = initB * Mat::diag(1/sqrtB);
	}
	//saveMatrixToYML("initB.yml", initB);
	Mat B = initB;
	Mat S;

//
// 	Mat seqPerm(X.cols, 1, X.type());
//
// 	for (int i = 0; i < seqPerm.rows; i++)
// 	{
// 		seqPerm.at<MatElem>(i, 0) = i;
// 	}

	auto now = time(NULL);
	printf("Beginning Coding, total %d iterations\n", num_iters);
	for (int i = 0; i < num_iters; i++)
	{
// 		auto idxPerm = seqPerm;
// 		randShuffle(idxPerm);
//
// 		auto batch_idx = idxPerm;
		Mat Xb = shuffleCol(X);

		for (int batch = 0; batch < X.size().width / batch_size; batch++)
		{
			// Data for this step

			if (isParallel)
				S = L1QP_FeatureSign_Set_Parallel(Xb, B, Sigma, beta, gamma);
			else
				S = L1QP_FeatureSign_Set(Xb, B, Sigma, beta, gamma);

			printf("%dth coefficient learning completed\n", batch + 1);

			stringstream s;
			string filename;
			s << "S_" << now << "_" << i << ".yml";
			s >> filename;
			s.clear();

			//saveMatrixToYML(filename, S);

			double objective = getObj(Xb, B, S, Sigma, beta, gamma);
			printf("Obj: %lf\n", objective);

			B = l2ls_learn_basis_dual(Xb, S, VAR_basis);

			s << "B_" << now << "_" << i <<".yml";
			s >> filename;
			s.clear();

			//saveMatrixToYML(filename, B);

			printf("%dth basis learning completed\n", batch + 1);

		}
		printf("Iteration %d completed\n", i + 1);
	}
	vector<Mat> result;
	result.push_back(B);
	result.push_back(S);
	return result;
}

Mat SparseCoding::L1QP_FeatureSign_Set( const Mat X, const Mat B, const Mat Sigma, double beta, double gamma )
{

	int nSmp = X.cols;
	int nBases = B.cols;

	Mat S(nBases, nSmp, X.type());
	Mat A = B.t() * B + 2 * beta * Sigma;
	Mat negBt = -B.t();
	for (int i = 0; i < nSmp; i++)
	{
		if (1)
			printf("Feature sign of col %d\n", i);
		Mat b = negBt * X.col(i);
		Mat featureSignResult = L1QP_FeatureSign_Yang(gamma, A, b);
		featureSignResult.copyTo(S.col(i));
/*		assignCol(S, i, featureSignResult);*/
	}
	return S;
}


cv::Mat SparseCoding::L1QP_FeatureSign_Set_Parallel( const Mat X, const Mat B, const Mat Sigma, double beta, double gamma, int threads /*= 8*/ )
{

	int nSmp = X.cols;
	int nBases = B.cols;

	Mat S(nBases, nSmp, X.type());
	Mat A = B.t() * B + 2 * beta * Sigma;
	Mat negBt = -B.t();
	boost::threadpool::pool pool(threads);


	if (nSmp > threads)
	{
		int rngLength = nSmp / threads;
		int rngStart = 0, rngEnd = rngLength;
		for (int i = 0; i < threads - 1; i++)
		{
			pool.schedule(boost::bind(&L1QP_FeatureSign_Set_Rng,
				rngStart, rngEnd, X, B, Sigma, S, beta, gamma));
			rngStart += rngLength;
			rngEnd += rngLength;
		}
		// The last partition may be smaller than rngLength
		pool.schedule(boost::bind(&L1QP_FeatureSign_Set_Rng,
			rngStart, nSmp, X, B, Sigma, S, beta, gamma));
		pool.wait(0);
	}else
	{
		pool.schedule(boost::bind(&L1QP_FeatureSign_Set_Rng,
			0, nSmp, X, B, Sigma, S, beta, gamma));
	}
	return S;
}


void SparseCoding::L1QP_FeatureSign_Set_Rng( int rngStart, int rngEnd, const Mat X, const Mat B, const Mat Sigma, Mat S, double beta, double gamma )
{
	Mat negBt = -B.t();
	Mat A = B.t() * B + 2 * beta * Sigma;
	for (int i = rngStart; i < rngEnd; i++)
	{
		Mat b = negBt * X.col(i);
		Mat featureSignResult = L1QP_FeatureSign_Yang(gamma, A, b);
		featureSignResult.copyTo(S.col(i));
// 		if ((i - rngStart) % 50 == 0)
// 			printf("FeatureSign %d to %d completed\n", rngStart, i);
	}
}



Mat SparseCoding::L1QP_FeatureSign_Yang( double lambda, const Mat A, const Mat b )
{
	Mat a;
	Mat x_min, o_min;
	double loss;
	double EPS = 1e-9;

	Mat x = Mat::zeros(A.rows, 1, MAT_TYPE);	//coeff
	Mat gradient = A * x + b;
	double maxValue;
	int maxIndex[2];
	Mat xZero = MatMemberwiseIsZero(x);

	// Find max element in gradient
	minMaxIdx(abs(gradient).mul(xZero), NULL, &maxValue, NULL, maxIndex);

	int outerCount = 0;
	while (true && outerCount < 100)
	{
		int mi = maxIndex[0];
		MatElem gradMax = gradient.at<MatElem>(maxIndex[0], 0);
		if (gradMax > lambda + EPS)
			x.at<MatElem>(mi, 0) = (lambda - gradMax) / A.at<MatElem>(mi, mi);
		else if (gradMax < -lambda - EPS)
			x.at<MatElem>(mi, 0) = (-lambda - gradMax) / A.at<MatElem>(mi, mi);
		else if (isZeroMatrix(x))
			break;

		int innerCount = 0;
		while (true && innerCount < 100)
		{
			//TODO: deal with when active set is empty
			a = MatMemberwiseIsNonZero(x);

			Mat Aa = LogicSubDiagonal(A, a, a);
			Mat ba = LogicSubVector(b, a);
			Mat xa = LogicSubVector(x, a);
			Mat vect = -lambda * MatrixSign(xa) - ba;
			Mat x_new = Aa.inv() *  vect;

			Mat idx = find(x_new);

			Mat x_new_i = SubVector(x_new, idx);
			Mat o_new = (SubVector(vect, idx) / 2
				+ SubVector(ba, idx)).t()
				* x_new_i
				+ lambda * sum(abs(x_new_i));

			// 			Mat o_new = (SubVector(vect, idx, noArray()) / 2
			// 				+ SubVector(ba, idx, noArray())).t()
			// 				* SubVector(x_new, idx, noArray())
			// 				+ lambda * sum(abs(SubVector(x_new, idx, noArray())));

			// Cost based on changing sign
			Mat s = find(MatMemberwiseNonPositive(xa.mul(x_new)));
			if (s.empty())
			{
				LogicMultiAssign(x, a, x_new);
// 				for (int i = 0; i < a.size().height; i++)
// 				{
// 					if (a.at<MatElem>(i, 0) != 0)
// 					{
// 						x.at<MatElem>(i, 0) = x_new.at<MatElem>(count++, 0);
// 					}
// 				}
				loss = o_new.at<MatElem>(0, 0);
				break;
			}
			x_min = x_new;
			o_min = o_new;
			Mat d = x_new - xa;
			Mat t = d.mul(1/xa);
			Mat st = s.t();

			MatConstIterator_<MatElem> it = st.begin<MatElem>(),
				itEnd = st.end<MatElem>();
			for (; it != itEnd; it++)
			{
				int zd = *it;
				Mat x_s = xa - d / t.at<MatElem>(zd, 0);
				x_s.at<MatElem>(zd, 0) = 0;
				Mat idx = find(x_s);
				Mat x_si = SubVector(x_s, idx);

				Mat o_s = (SubDiagonal(Aa, idx, idx) * x_si / 2
					+ SubVector(ba, idx)).t() * x_si
					+ lambda * sum(abs(x_si));

				// 				Mat o_s = (SubDiagonal(Aa, idx, idx) * SubVector(x_s, idx) / 2
				// 					+ SubVector(ba, idx)).t() * SubVector(x_s, idx)
				// 					+ lambda * sum(abs(SubVector(x_s, idx)));

				if (o_s.at<MatElem>(0, 0) < o_min.at<MatElem>(0, 0))
				{
					x_min = x_s;
					o_min = o_s;
				}
			}
			LogicMultiAssign(x, a, x_min);
			loss = o_min.at<MatElem>(0, 0);
			innerCount++;
		}

		gradient = A * x + b;
		xZero = MatMemberwiseIsZero(x);
		minMaxIdx(abs(gradient).mul(xZero), NULL, &maxValue, NULL, maxIndex);
		if (maxValue <= lambda + EPS)
			break;
		outerCount++;
	}
	//printf("Feature sign finished at outer loop %d\n", outerCount);
	return x;
}

Mat SparseCoding::l2ls_learn_basis_dual( Mat X, Mat S, int l2norm )
{


	int M = S.size().height;

	Mat SSt = S * S.t();
	Mat XSt = X * S.t();

	Mat dual_lambda(M, 1, X.type());
	randn(dual_lambda, 5, 3);
	dual_lambda = abs(dual_lambda);

	double trXXt = sum(X.mul(X)).val[0];
	Mat lb = Mat::zeros(dual_lambda.size(), dual_lambda.type());

	nlopt::opt opt(nlopt::LD_MMA, 128);

	ObjParam param;
	param.c = l2norm * l2norm;
	param.dual_lambda = dual_lambda;
	param.SSt = SSt;
	param.Xst = XSt;
	param.trXXt = trXXt;

	//saveMatrixToYML("SSt.yml", SSt);
	//saveMatrixToYML("Xst.yml", XSt);

	vector<double> result;
	opt.set_min_objective(fobj_basis_dual, &param);
	opt.set_lower_bounds(0);
	opt.set_ftol_rel(1.0e-6);
	//opt.optimize(result);
	result = opt.optimize(dual_lambda);

	dual_lambda = Mat(result, true);
	dual_lambda.convertTo(dual_lambda, MAT_TYPE);
	Mat Bt = ((SSt + Mat::diag(dual_lambda)).inv() * XSt.t()).t();
	return Bt;
}

double SparseCoding::fobj_basis_dual( const std::vector<double> &x, std::vector<double> &grad, void* f_data )
{
	// Extra parameters
	auto param = (ObjParam*)f_data;
	Mat Xst = param->Xst;
	Mat dual_lambda = Mat(x, true);
	dual_lambda.convertTo(dual_lambda, MAT_TYPE);
	Mat SSt = param->SSt;
	double trXXt = param->trXXt;
	double c = param->c;

	int L = Xst.size().height;
	int M = dual_lambda.size().width > dual_lambda.size().height ?
		dual_lambda.size().width : dual_lambda.size().height;
	Mat SSt_inv = (SSt + Mat::diag(dual_lambda)).inv(DECOMP_SVD);

	double f;
	if (L > M)
	{
		f = -trace(SSt_inv * (Xst.t() * Xst)).val[0] + trXXt - c * sum(dual_lambda).val[0];
	}else
	{
		f = -trace(Xst * SSt_inv * Xst.t()).val[0] + trXXt - c * sum(dual_lambda).val[0];
	}

	//gradient
	Mat temp = Xst * SSt_inv;
	Mat g = -(colSum(temp.mul(temp)) - c);
	grad = g;
	//printf("Dual objective value: %lf\n", -f);
	return -f;
}

double SparseCoding::getObj( Mat X, Mat B, Mat S, Mat Sigma, double beta, double gamma )
{
	Mat err = X - B * S;
	double fresidue = 0.5 * sumOfMemWiseMultiply(err, err);
	double sparsity = gamma * sumOfAbs(S);
	double fregs = 0;
	for (int i = 0; i < S.cols; i++)
	{
		Mat f = beta * S.col(i).t() * Sigma * S.col(i);
		fregs += f.at<MatElem>(0, 0);
	}
	return fresidue + sparsity + fregs;
}

