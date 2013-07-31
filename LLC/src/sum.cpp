#include "sum.h"




cv::Mat sumcol( Mat X )
{
	Mat T=Mat::zeros(1,X.size().width,CV_32F);
	for(int i=0;i<X.size().width;i++)
	{
		T.at<float>(0,i) = (float) sum(X.col(i)).val[0];
	}
	return T;
}

cv::Mat sumrow( Mat X )
{
	Mat T=Mat::zeros(X.size().height,1,CV_32F);
	for(int i=0;i<X.size().height;i++)
	{
		T.at<float>(i,0) = (float) sum(X.row(i)).val[0];
	}
	return T;
}

cv::Mat MatCeil( Mat X )
{
	Mat T=Mat::zeros(X.size().height,X.size().width,CV_32F);
	for(int i=0;i<X.size().height;i++)
	{
		for(int j=0;j<X.size().width;j++)
		{
			T.at<float>(i,j)=ceil(X.at<float>(i,j));
		}
	}
	return T;
}

cv::Mat Maxrow( Mat X,Mat Y,int bId,int com )
{
	for(int i=0;i<Y.size().height;i++)
	{
		if(X.at<float>(i,bId) < Y.at<float>(i,com))
		{
			X.at<float>(i,bId) = Y.at<float>(i,com);
		}
	}
	return X.col(bId);
}

cv::Mat Sort( Mat X )
{
	Mat Y=Mat::zeros(X.size(),CV_32F);
	Mat Z=Mat::zeros(X.size(),CV_32F);
	for(int i=0;i<X.size().width;i++)
	{
		for(int j=0;j<X.size().width;j++)
		{
			if(i>j)
			{
				if(X.at<float>(0,i)>=X.at<float>(0,j))
					Y.at<float>(0,i)++;
			}
			if(i<j)
			{
				if(X.at<float>(0,i)>X.at<float>(0,j))
					Y.at<float>(0,i)++;
			}
		}
	}
	for(int i=0;i<Y.size().width;i++)
	{
		Z.at<float>(0,Y.at<float>(0,i))=i;
	}

	return Z;
}

double sumtrace( Mat X )
{
	double sum=0;
	for(int i=0;i<X.size().height;i++)
	{
		sum+=X.at<float>(i,i);
	}
	return sum;
}

cv::Mat Col( Mat X )
{
	Mat Y=Mat::zeros(X.size().width*X.size().height,1,CV_32F);
	for(int i=0;i<X.size().width;i++)
	{
		for(int j=0;j<X.size().height;j++)
		{
			Y.at<float>(i*X.size().height+j,0)=X.at<float>(j,i);
		}
	}
	return Y;
}
