#include "SCC.h"

Mat SCC::CCCP( const Mat& X, const Mat& B, const Mat& W, const Mat& sigma, double beta, double gamma1, double gamma2 )
{
	Mat S = Mat::zeros(W.size().height, 1, CV_64F);
	for (int i = 0; i < 100; i++)
	{
		Mat p = -gamma2 * 2 * W * S;
		Mat St = L1QP_FeatureSign_Set_Zhang(X, B, p, sigma, beta, gamma1);
		Scalar ts = sum(St - S);
		double t = ts.val[0];
		if (t == 0)
			break;

		S = St;
		Mat residual = (X - B * S).t() * (X - B * S) + sum(S) - S.t() * W * S;
		if (norm(residual) < 0.02)
			break;
	}
	return S;
}


Mat SCC::L1QP_FeatureSign_Set_Zhang( const Mat& X, const Mat& B, const Mat& p, const Mat& sigma, double beta, double gamma )
{
	CvSize SizeX = X.size();
	int nSample = SizeX.width;
	int nBases = B.size().width;
	Mat A = B.t() * B + 2 * beta * sigma;
	Mat S(nBases, nSample, CV_64F);

	for (int i = 0; i < nSample; i++)
	{
		Mat b = -B.t() * X.col(i) + p / 2;
		Mat Yresult = L1QP_FeatureSign_Yang(gamma, A, b);
		Yresult.copyTo(S.col(i));
	}
	return S;
}

vector<Mat> SCC::semantic_neighbours( const Mat qfea, const Mat f, const Mat W, const Mat sigma, double beta, double gamma1, double gamma2 )
{
	vector<Mat> ret;
	Mat Scc = CCCP( qfea, f, W, sigma, beta, gamma1, gamma2 );
	Mat idx;

	sortIdx(Scc, idx, SORT_EVERY_COLUMN | SORT_DESCENDING);
	int row = sigma.size().height;

	Mat ft = f.t();
	Mat Scct = Scc.t();

	Mat aa, scc;

	for (int i = 0; i < row; i++)
	{
		int ii = idx.at<int>(i, 0);
		MatElem weight = Scc.at<MatElem>(ii, 0);
		if (weight != 0.0)
		{
			aa.push_back(ft.row(ii));
			scc.push_back(Scc.row(ii));
		}
	}
	Mat A = aa.clone();
	Mat qfeat = qfea.t();
	A.push_back(qfeat);
	A = A.t();
	Mat pA = A.inv(DECOMP_SVD);
	Mat sou = pA * qfea;

	ret.push_back(A);
	ret.push_back(scc);
	ret.push_back(sou);
	return ret;
}

double SCC::retrievalScore( const InputArray& queryFea, const InputArray& candidateFea, const InputArray& codebook )
{
	Mat qF = queryFea.getMat();
	Mat cF = candidateFea.getMat();
	Mat cb = codebook.getMat();
	//Debug
	Mat cbi = cb.inv(DECOMP_SVD);
	Mat b = cbi * cF;
	double score = norm(cbi * cF - qF);
	return score;
}

// Mat L1QP_FeatureSign_Set_Yang( double lambda, const Mat& A, const Mat& b )
// {
// 	Mat a;
// 	Mat x_min, o_min;
//
// 	double loss = 0.0;
//
// 	double EPS = 1e-9;
// 	CvSize ASize = A.size();
// 	ASize.width = 1;
// 	Mat x = Mat::zeros(ASize, CV_64F);	//coeff
// 	Mat gradient = A * x + b;
// 	double maxValue;
// 	int maxIndex[2];
// 	Mat xZero = MatMemberwiseIsZero(x);
//
// 	// Find max element in gradient
// 	minMaxIdx(abs(gradient).mul(xZero), NULL, &maxValue, NULL, maxIndex);
//
// 	int outerCount = 0;
// 	while (true)
// 	{
// 		int mi = maxIndex[0];
// 		MatElem gradMax = gradient.at<MatElem>(maxIndex[0], 0);
// 		if (gradMax > lambda + EPS)
// 			x.at<MatElem>(mi, 0) = (lambda - gradMax) / A.at<MatElem>(mi, mi);
// 		else if (gradMax < -lambda - EPS)
// 			x.at<MatElem>(mi, 0) = (-lambda - gradMax) / A.at<MatElem>(mi, mi);
// 		else if (isZeroMatrix(x))
// 			break;
//
// 		int innerCount = 0;
// 		while (true)
// 		{
// 			a = MatMemberwiseIsNonZero(x);
// 			Mat Aa = LogicSubDiagonal(A, a, a);
// 			Mat ba = LogicSubVector(b, a);
// 			Mat xa = LogicSubVector(x, a);
//
// 			// New b based on unchanged sign
// 			Mat vect = -lambda * MatrixSign(xa) - ba;
// 			Mat x_new = Aa.inv() *  vect;
// 			Mat idx = find(x_new);
//
// 			Mat x_new_i = SubVector(x_new, idx);
// 			Mat o_new = (SubVector(vect, idx) / 2
// 				+ SubVector(ba, idx)).t()
// 				* x_new_i
// 				+ lambda * sum(abs(x_new_i));
//
// // 			Mat o_new = (SubVector(vect, idx, noArray()) / 2
// // 				+ SubVector(ba, idx, noArray())).t()
// // 				* SubVector(x_new, idx, noArray())
// // 				+ lambda * sum(abs(SubVector(x_new, idx, noArray())));
//
// 			// Cost based on changing sign
// 			Mat s = find(MatMemberwiseNonPositive(xa.mul(x_new)));
// 			if (s.empty())
// 			{
// 				int count = 0;
// 				for (int i = 0; i < a.size().height; i++)
// 				{
// 					if (a.at<MatElem>(i, 0) != 0)
// 					{
// 						x.at<MatElem>(i, 0) = x_new.at<MatElem>(count++, 0);
// 					}
// 				}
// 				loss = o_new.at<MatElem>(0, 0);
// 				break;
// 			}
// 			x_min = x_new;
// 			o_min = o_new;
// 			Mat d = x_new - xa;
// 			Mat t = d.mul(1/xa);
// 			Mat st = s.t();
//
// 			MatConstIterator_<MatElem> it = st.begin<MatElem>(),
// 				itEnd = st.end<MatElem>();
// 			for (; it != itEnd; it++)
// 			{
// 				int zd = *it;
// 				Mat x_s = xa - d / t.at<MatElem>(zd, 0);
// 				x_s.at<MatElem>(zd, 0) = 0;
// 				Mat idx = find(x_s);
// 				Mat x_si = SubVector(x_s, idx);
//
// 				Mat o_s = (SubDiagonal(Aa, idx, idx) * x_si / 2
// 					+ SubVector(ba, idx)).t() * x_si
// 					+ lambda * sum(abs(x_si));
//
// // 				Mat o_s = (SubDiagonal(Aa, idx, idx) * SubVector(x_s, idx) / 2
// // 					+ SubVector(ba, idx)).t() * SubVector(x_s, idx)
// // 					+ lambda * sum(abs(SubVector(x_s, idx)));
//
// 				if (o_s.at<MatElem>(0, 0) < o_min.at<MatElem>(0, 0))
// 				{
// 					x_min = x_s;
// 					o_min = o_s;
// 				}
// 			}
// 			LogicMultiAssign(x, a, x_min);
// 			loss = o_min.at<MatElem>(0, 0);
// 		}
//
// 		gradient = A * x + b;
// 		xZero = MatMemberwiseIsZero(x);
// 		minMaxIdx(abs(gradient).mul(xZero), NULL, &maxValue, NULL, maxIndex);
// 		if (maxValue <= lambda + EPS)
// 			break;
// 	}
// 	return x;
// }
