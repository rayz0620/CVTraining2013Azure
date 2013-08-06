#include "LLC.h"

cv::Mat LLC::LLC_pooling( FeatureItem feaSet,Mat B,Mat pyramid,int knn )
{
	double dSize = B.size().width;
	double nSmp= feaSet.feaArr.size().width;
	double img_width=feaSet.width;
	double img_height=feaSet.height;
	Mat idxBin=Mat::zeros(nSmp,1,CV_32F);
	//llc coding
	Mat llc_codes=LLC_coding_appr(B.t(),feaSet.feaArr.t(),knn);
	llc_codes=llc_codes.t();

	//spatial levels
	double pLevels=pyramid.size().width;
	Mat pBins=pyramid.mul(pyramid);
	double tBins =sum(pBins).val[0];
	Mat beta=Mat::zeros(dSize,tBins,CV_32F);
	Mat beta2=Mat::zeros(dSize,tBins,CV_32F);
	double bId=0;

	for(int iter1=0;iter1<pLevels;iter1++)
	{
		float nBins=pBins.at<float>(0,iter1);
		double wUnit=img_width/pyramid.at<float>(0,iter1);
		double hUnit=img_height/pyramid.at<float>(0,iter1);

		Mat xBin=MatCeil(feaSet.x/wUnit);
		Mat yBin=MatCeil(feaSet.y/hUnit);
		Mat idxBin=(yBin-1)*pyramid.at<float>(0,iter1)+xBin;
		for(float iter2=1;iter2<=nBins;iter2++)
		{
			for(int i=0;i<idxBin.size().height;i++)
			{

				if(idxBin.at<float>(i,0)==iter2)
				{
					//beta.col(bId)=Maxrow(beta2,llc_codes,bId,i).copyTo()+0;
					Maxrow(beta2,llc_codes,bId,i).copyTo(beta.col(bId));
				}
			}
			bId+=1;
		}
	}
	beta=Col(beta);

	beta=beta/sqrt(sum(beta.mul(beta)).val[0]);
	return beta;
}

cv::Mat LLC::LLC_coding_appr( Mat B,Mat X,int knn )
{
	double beta=1e-4;

	double nframe=X.rows;
	double nbase=B.rows;

	Mat t1=X.mul(X);
	Mat t2=B.mul(B);

	Mat XX=sumrow(t1);
	Mat BB=sumrow(t2);

	Mat t3=Mat::zeros(XX.rows,nbase,CV_32F);
	Mat t4=Mat::zeros(nframe,BB.rows,CV_32F);
	for(int i=0;i<nbase;i++)
	{
		//t3.col(i)=XX + 0;
		XX.copyTo(t3.col(i));
	}


	for(int i=0;i<nframe;i++)
	{
		//t4.row(i)=BB.t() + 0;
		((Mat)BB.t()).copyTo(t4.row(i));
	}
	//D check OK
	Mat D=t3-(2*X*(B.t()))+t4;
	//IDX check OK
	Mat IDX=Mat::zeros(nframe,knn,CV_32F);

	for(int i=0;i<nframe;i++)
	{
        Mat d;
        D.row(i).copyTo(d);
		//Mat d=D.row(i)+0;
		Mat idx=Sort(d);
		for(int j=0;j<knn;j++)
			IDX.at<float>(i,j)=idx.at<float>(0,j);
	}


	Mat II=Mat::eye(knn,knn,CV_32F);

	Mat Coeff=Mat::zeros(nframe,nbase,CV_32F);
	for(int i=0;i<nframe;i++)
	{
		Mat t5=Mat::zeros(knn,X.size().width,CV_32F);
		Mat z=Mat::zeros(knn,B.size().width,CV_32F);
		for(int j=0;j<knn;j++)
		{
			float n=IDX.at<float>(i,j);
			//z.row(j)=B.row(n)+0;
			B.row(n).copyTo(z.row(j));
			//t5.row(j)=X.row(i)+0;
			X.row(i).copyTo(t5.row(j));
		}
		z=z-t5;

		Mat C=z*z.t();
		double t6=sumtrace(C);
		C=C+II*beta*t6;

		Mat w=Mat::ones(knn,1,CV_32F);
		
		w=C.inv()*w;
		w=w/sum(w).val[0];
		w=w.t();

		for(int j=0;j<knn;j++)
		{
			float n=IDX.at<float>(i,j);

			Coeff.at<float>(i,n)=w.at<float>(0,j);
		}
	}
	return Coeff;
}