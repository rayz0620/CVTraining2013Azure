#include "SparseCoder.h"

vector<Mat> SparseCoding::SparseCoder::encode( const Mat X, const string& outFilename /*= ""*/ )
{
	return reg_sparse_coding(X, num_bases, Sigma, beta, gamma, num_iters, isParallel);
}

void SparseCoding::SparseCoder::saveConfig( const string& filename )
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "num_bases" << num_bases;
		fs << "Sigma" << Sigma;
		fs << "beta" << beta;
		fs << "gamma" << gamma;
		fs << "num_iters" << num_iters;
		fs << "isParallel" << isParallel;
		fs << "threads" << threads;
	}
}

void SparseCoding::SparseCoder::loadConfig( const string& filename )
{
	FileStorage fs(filename, FileStorage::READ);
	if (fs.isOpened())
	{
		fs["num_bases"] >> num_bases;
		if (fs["Sigma"].isNone())
			Sigma = Mat::eye(num_bases, num_bases, CV_32F);
		else
			fs["Sigma"] >> Sigma;
		fs["beta"] >> beta;
		fs["gamma"] >> gamma;
		fs["num_iters"] >> num_iters;
		fs["isParallel"] >> isParallel;
		fs["threads"] >> threads;
	}
}

SparseCoding::SparseCoder::SparseCoder()
{

}
