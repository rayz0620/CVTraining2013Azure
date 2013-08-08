#include <opencv2/opencv.hpp>
#include <cstdio>
#include <string>
#include "Retrieval.h"
#include "RetrievalDatabase.h"
#include "SemanticDatabase.h"
#include <ctime>

using namespace std;
using namespace cv;
using namespace MatrixUtils;
using namespace IOUtils;

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
        printf("Insufficient arguments\n");
        printf("Usage: runtest [configFile] [semanticDB] [mainDB] [testDB]\n");
        return 0;
    }else
 	{
 		unsigned int beginTime = time(NULL);
 		string cfg(argv[1]);
 		string semDB(argv[2]);
 		string mainDB(argv[3]);
 		string testDB(argv[4]);

 		RetrievalDatabase query;
 	 	SemanticDatabase aux;
 	 	RetrievalDatabase db;
 	 	Retrieval r;
 	// 
 	 	aux.load(semDB);
 	 	db.load(mainDB);
 	 	query.load(testDB);
 	// 
 	 	r.Sdb(&aux);
 	 	r.RDb(&db);
 	 	r.loadConfigFile(cfg);
 	 	double precision = r.TestAll(query);
 	 	printf("Completed in %d seconds\n", (unsigned int)time(NULL) - beginTime);
		printf("Precision is %lf\n", precision);
		system("pause");
		return 0;
 	}
// 
// 	int n = 50;
// 	double precision = r.ParrallelTestAll(query);
// 	printf("Precision of first %d queries is %lf\n", n, precision);
// 	system("pause");

	//auto X = readMatrixFromYML("X.yml");
	//auto X_trim = readMatrixFromYML("X_trim.yml");
	//shuffleCol(X);
	//saveMatrixToYML("X_trim_150.yml", X.colRange(0, 150));
	//auto X_trim = readMatrixFromYML("X_trim.yml");
	//auto S = readMatrixFromYML("opt_S.yml");
	//auto initB = readMatrixFromYML("initB.yml");
	//double beta = 1.0e-5;
	//double gamma = 0.15;
	//int num_bases = 128;
	//int num_iters = 50;
	//Mat Sigma = Mat::eye(num_bases, num_bases, CV_64F);
	

	//auto M = l2ls_learn_basis_dual(X, S, 1);
	//auto result = reg_sparse_coding(X, num_bases, Sigma, beta, gamma, num_iters);
	//auto result = reg_sparse_coding(X_trim, num_bases, Sigma, beta, gamma, num_iters, true);
	//auto obj = getObj(X_trim, initB, S, Sigma, beta, gamma);
	//saveMatrixToYML("B.yml", result[0]);
	//saveMatrixToYML("S.yml", result[1]);
	//saveMatrixToYML("B.yml", M);
	
}

