#include "SIFT.h"

cv::Mat SIFT::mcos( Mat src )
{
	CvSize size=src.size();
	Mat M(size.height,size.width,CV_32F);
	for(int i=0;i<size.height;i++)
	{
		float *pt=src.ptr<float>(i);
		for(int j=0;j<size.width;j++)
		{
			M.at<float>(i,j)=cos(pt[j]);
		}
	}
	return M;
}

cv::Mat SIFT::matan2( Mat src1,Mat src2 )
{
	CvSize size=src1.size();
	Mat M(size.height,size.width,CV_32F);
	for(int i=0;i<size.height;i++)
	{
		for(int j=0;j<size.width;j++)
		{
			M.at<float>(i,j)=atan2(src1.at<float>(i,j),src2.at<float>(i,j));
		}
	}
	return M;
}

float SIFT::totalSumO( Mat src ) //计算所有元素的总和
{
	int k=src.rows;
	int m=src.cols;
	float num=0;
	for(int i=0;i<k;i++)
	{
		float *pt=src.ptr<float>(i);
		for(int j=0;j<m;j++)
		{
			if(pt[j]>=0)
				num+=pt[j];
			else
				num-=pt[j];
		}
	}
	return num;
}

cv::Mat SIFT::gradientX( Mat src )
{
	int k=src.rows;
	int m=src.cols;
	Mat M(k,m,CV_32F);
	for(int j=0;j<k;j++)
	{
		float *pt=src.ptr<float>(j);
		M.at<float>(j,0)=pt[1]-pt[0];
		M.at<float>(j,m-1)=pt[m-1]-pt[m-2];
	}
	for(int i=1;i<m-1;i++)
	{
		for(int j=0;j<k;j++)
		{
			float *pt=src.ptr<float>(j);
			M.at<float>(j,i)=(pt[i+1]-pt[i-1])/2;
		}
	}
	return M;
}

cv::Mat SIFT::gradientY( Mat src )
{
	int k=src.rows;
	int m=src.cols;
	Mat M(k,m,CV_32F);
	for(int j=0;j<m;j++)
	{
		float *pt1=src.ptr<float>(1);
		float *pt2=src.ptr<float>(0);
		float *pt3=src.ptr<float>(m-1);
		float *pt4=src.ptr<float>(m-2);
		M.at<float>(0,j)=pt1[j]-pt2[j];
		M.at<float>(m-1,j)=pt3[j]-pt4[j];
	}
	for(int i=1;i<k-1;i++)//hang
	{
		float *pt1=src.ptr<float>(i-1);
		float *pt2=src.ptr<float>(i+1);
		for(int j=0;j<m;j++)//lie
		{
			M.at<float>(i,j)=(pt2[j]-pt1[j])/2;
		}
	}
	return M;
}

cv::Mat SIFT::sum_every_col( Mat src )
{
	Mat M(1,src.cols,CV_32F);
	for(int i=0;i<src.cols;i++)
	{
		float num=0;
		for(int j=0;j<src.rows;j++)
		{
			num+=src.at<float>(j,i);
		}
		M.at<float>(0,i)=num;
	}
	return M;
}

cv::Mat SIFT::getNum( Mat src,int y_lo,int y_hi,int x_lo,int x_hi )
{
	//Mat M=src.rowRange(x_lo-1,x_hi);
	//Mat X=M.colRange(y_lo-1,y_hi);
// 	Mat X((x_hi-x_lo+1),(y_hi-y_lo+1),CV_32F);
//
// 	int i=x_lo;
// 	int j=y_lo;
//
// 	for(int k=0;k<X.rows;k++,i++)
// 	{
// 		float *pt=src.ptr<float>(i);
// 		for(int m=0;m<X.cols;m++,j++)
// 		{
// 			X.at<float>(k,m)=pt[j];
// 			// if(j<=y_hi);
// 		}
// 	}
// 	return X;
//
	return src(cv::Range(x_lo, y_lo), cv::Range(x_hi, y_hi));
}

cv::Mat SIFT::Less( Mat src,float num )
{
	CvSize size=src.size();
	Mat tep(size.height,size.width,CV_32F);
	for(int i=0;i<size.height;i++)
	{
		for(int j=0;j<size.width;j++)
		{
			if(src.at<float>(i,j)<=num)
			{
				tep.at<float>(i,j)=1;
			}
			else
			{
				tep.at<float>(i,j)=0;
			}

		}
	}
	return tep;
}

cv::Mat SIFT::compare( Mat src,float num )
{
	Mat M(src.rows,src.cols,CV_32F);
	int k=src.rows;
	int m=src.cols;
	for(int i=0;i<k;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(src.at<float>(i,j)>=num)
				M.at<float>(i,j)=1;
			else
				M.at<float>(i,j)=0;
		}
	}
	return M;
}

cv::Mat SIFT::compareB( Mat src,float num )
{
	Mat M(src.rows,src.cols,CV_32F);
	int k=src.rows;
	int m=src.cols;
	for(int i=0;i<k;i++)
	{
		float *pt=src.ptr<float>(i);
		for(int j=0;j<m;j++)
		{
			if(src.at<float>(i,j)>num)
				M.at<float>(i,j)=pt[j];
			else
				M.at<float>(i,j)=0;
		}
	}
	return M;
}

void SIFT::assign( Mat dst,Mat var,Mat src )
{
	int i=var.rows;
	int k=0;
	for(int j=0;j<i;j++)
	{
		if(var.at<float>(j,0)==1)
		{
			dst.row(j)=src.row(k);
			k++;
		}
	}
}

cv::Mat SIFT::suppresss( Mat src,float num )
{
	Mat M(src.rows,src.cols,CV_32F);
	for(int i=0;i<src.rows;i++)
	{
		for(int j=0;j<src.cols;j++)
		{
			if(src.at<float>(i,j)>0.2)
			{
				M.at<float>(i,j)=0.2;
			}
			else
				M.at<float>(i,j)=src.at<float>(i,j);
		}
	}
	return M;
}

cv::Mat SIFT::search( Mat src,Mat dst ) //把dst中为1的src中对应行找出来， ??
{
	int num=0;
	for(int i=0;i<dst.rows;i++)
	{
		if(dst.at<float>(i,0)==1)
			num++;

	}
	Mat M(num,src.cols,CV_32F);
	int j=0;
	for(int i=0;i<dst.rows;i++)
	{
		if(dst.at<float>(i,0)==1)
		{
			M.row(j)=src.row(i);
			j++;
		}

	}
	return M;
}

cv::Mat SIFT::sum_row( Mat src )
{
	Mat M(src.rows,1,CV_32F);
	for(int i=0;i<src.rows;i++)
	{
		float num=0;
		for(int j=0;j<src.cols;j++)
		{
			num+=src.at<float>(i,j);
		}
		M.at<float>(i,0)=num;
	}

	return M;
}

cv::Mat SIFT::change( Mat src )
{
	Mat M(src.rows,src.cols,CV_32F);
	int k=src.cols;
	int m=src.rows;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<k;j++)
		{
			if(src.at<float>(i,j)>0)
				M.at<float>(i,j)=0;
			else
				M.at<float>(i,j)=1;
		}
	}
	return M;
}

cv::Mat SIFT::repmat( Mat src,int height,int width )
{
	CvSize size=src.size();
	if(height==1)
	{
		Mat x(src.rows,src.cols*width,CV_32F);
		for(int i=0;i<width;i++)
		{
			for(int j=0;j<size.height;j++)
			{
				float *pt=src.ptr<float>(j);
				for(int m=0;m<size.width;m++)
				{
					x.at<float>(j,i*size.width+m)=pt[m];
				}
			}
		}
		return x;
	}
	else if(width==1)
	{
		Mat x(src.rows*height,src.cols,CV_32F);
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<size.height;j++)
			{
				float *pt=src.ptr<float>(j);
				for(int k=0;k<size.width;k++)
				{
					x.at<float>(i*size.height+j,k)=pt[k];
				}
			}
		}
		return x;
	}else
	{
		Mat x(src.rows * height, src.cols * height, CV_32F);
		for (int i = 0; i < src.rows; i++ )
		{
			Mat repRow = repmat(x.row(i), 1, width);
			for (int j = 0; j < height; j++)
			{
				repRow.copyTo(x.row(j * height + i));
			}
		}
		return x;
	}
}

cv::Mat SIFT::Add( Mat src, float x )
{
	Mat c(src.rows,src.cols,CV_32F);
	CvSize size=src.size();
	for(int j=0;j<size.height;j++)
	{
		float *pt=src.ptr<float>(j);
		for(int i=0;i<size.width;i++)
		{
			float mm=pt[i];
			c.at<float>(j,i)=mm+x;
		}
	}
	return c;
}

cv::Mat SIFT::create( float start,float end,float step )
{
	//int m=(int)(end-start)/step+2;
	int m=0;
	float n=start;
	while(n<=end)
	{
		m++;
		n=n+step;
	}
	int j=0;
	Mat x(1,m,CV_32F);
	while(start<=end)
	{
		x.at<float>(0,j)=start;
		j++;
		start+=step;
	}
	return x;
}

cv::Mat SIFT::reshapeX( Mat I ) //变为?维矩阵
{
	CvSize size=I.size();
	Mat a(1,size.height*size.width,CV_32F);
	int x=0;

	for(int i=0;i<size.width;i++)
	{
		for(int j=0;j<size.height;j++)
		{
			a.at<float>(0,x)=I.at<float>(j,i);
			x++;
		}
	}
	return a;
}

cv::Mat SIFT::reshapeY( Mat I ) //变为n维矩阵
{
	CvSize size=I.size();
	Mat a(size.height*size.width,1,CV_32F);
	int x=0;
	for(int i=0;i<size.width;i++)
	{
		for(int j=0;j<size.height;j++)
		{
			a.at<float>(x,0)=I.at<float>(j,i);
			x++;
		}
	}
	return a;
}

cv::Mat SIFT::meshgrid_X( Mat I1,Mat I2 )
{
	CvSize size=I2.size();
	Mat b=Mat::ones(size.width,size.height,CV_32F);
	Mat a=b*I1;
	return a;
}

cv::Mat SIFT::meshgrid_Y( Mat I1,Mat I2 )
{
	CvSize size=I1.size();
	Mat a=Mat::ones(size.height,size.width,CV_32F);
	Mat b=reshapeY(I2)*a;
	return b;
}

cv::Mat SIFT::deleteO( Mat src )
{
	Mat x(src.rows,src.cols-1,CV_32F);
	float *pt=src.ptr<float>(0);
	for(int i=0;i<src.cols-1;i++)
	{
		x.at<float>(0,i)=pt[i];
	}
	return x;
}

cv::Mat SIFT::gaussian( int wid,float sigma )
{
	Mat X(wid,wid,CV_32F);
	float sum=0;
	for(int i=-2;i<=2;i++)
	{
		for(int j=-2;j<=2;j++)
		{
			float tmp=exp(-(i*i+j*j)/(2*sigma*sigma));
			X.at<float>(i+2,j+2)=tmp;
			sum=sum+tmp;
		}
	}
	for(int i=0;i<5;i++)
	{
		float *pt=X.ptr<float>(i);
		for(int j=0;j<5;j++)
		{
			X.at<float>(i,j)=pt[j]/sum;
		}
	}
	return X;
}

cv::Mat SIFT::im2double( Mat src )
{
	int r=src.rows;
	int c=src.cols;
	Mat M(r,c,CV_32F);
	for(int i=0;i<r;i++)
	{
		float *pt=src.ptr<float>(i);
		for(int j=0;j<c;j++)
		{
			M.at<float>(i,j)=pt[j]/255;
		}
	}
	return M;
}

cv::Mat SIFT::square( Mat src ) //对每个元素求平 ?
{
	int r=src.rows;
	int c=src.cols;
	Mat X(r,c,CV_32F);
	for(int i=0;i<r;i++)
	{
		float *pt=src.ptr<float>(i);
		for(int j=0;j<c;j++)
		{
			X.at<float>(i,j)=pt[j]*pt[j];
		}
	}
	return X;
}

cv::Mat SIFT::filter2( Mat mask,Mat src )
{
	int sr=src.rows;
	int sc=src.cols;
	int mr=mask.rows;
	int mc=mask.cols;
	Mat X(sr,sc,CV_32F);
	for(int i=0;i<sr;i++)
	{
		for(int j=0;j<sc;j++)
		{
			float n=0;
			for(int k=0;k<mr;k++)
			{
				for(int m=0;m<mc;m++)
				{
					if((i+k<sr)&&(j+m<sc))
					{
						float *pt1=src.ptr<float>(i+k);
						float *pt2=mask.ptr<float>(k);
						n=n+pt1[j+m]*pt2[m];

					}

				}
			}
			X.at<float>(i,j)=n;
		}
	}
	return X;
}

cv::Mat SIFT::sp_find_sift_grid( Mat I,Mat gridX,Mat gridY,int patchSize, float sigma_edge )
{
	int num_angles=8;
	float num_bins=4;
	int num_samples=num_bins*num_bins;
	int alpha = 9;

	//此处需要判断总共传入多少个变量，如果变量数小于5，就把sigma_edge设置为1
	float angle_step=2*pi/num_angles;

	//初始化angles 为一个一维矩阵从0到2*pi；间隔为angle_step
	Mat angles=create(0,2*pi,angle_step);
	angles=deleteO(angles); //删除最后一个元素

	CvSize size=I.size();
	//int hgt=size.height;
	//int wid=size.width;

	int num_patches=gridX.total();//计算gridX总共有多少个元素

	Mat sift_arr=Mat::zeros(num_patches,num_samples*num_angles,CV_32F);

	//计算滤波算子
	int  f_wid = 4 * ceil(sigma_edge) + 1;
	Mat G=gaussian(f_wid,sigma_edge);

	Mat GX=gradientX(G);
	Mat GY=gradientY(G);


	GX=GX*2/totalSumO(GX);
	GY=GY*2/totalSumO(GY);



	Mat I_X(I.rows,I.cols,CV_32F);
	I_X=filter2(GX,I);              //因为I，图片读入不同，所以I_X不同，与I有关的均布相同，但是，都正确


	Mat I_Y(I.rows,I.cols,CV_32F);
	I_Y=filter2(GY,I);

	Mat T(I_X.rows,I_X.cols,CV_32F);
	add(I_X.mul(I_X),I_Y.mul(I_Y),T);
	Mat I_mag(I_X.rows,I_X.cols,CV_32F);
	sqrt(T,I_mag);
	Mat I_theta=matan2(I_Y,I_X);

	Mat interval=create(2/num_bins,2,2/num_bins);
	interval-=(1/num_bins+1);

	Mat sample_x=meshgrid_X(interval,interval);


	Mat sample_y=meshgrid_Y(interval,interval);

	sample_x=reshapeX(sample_x);//变为一个1维矩阵

	sample_y=reshapeX(sample_y);

	Mat I_orientation[8] = {Mat::zeros(size,CV_32F)};
	for(int i=0;i<8;i++)
	{
		I_orientation[i] = Mat::zeros(size,CV_32F);
	}
	float *pt=angles.ptr<float>(0);

	for(int a=0;a<num_angles;a++)
	{
		Mat tep1=mcos(I_theta-pt[a]);//cos
		//cout<<tep1.at<float>(0,1)<<endl;
		Mat tep(tep1.rows,tep1.cols,CV_32F);
		pow(tep1,alpha,tep);
		tep=compareB(tep,0);
		I_orientation[a]=tep.mul(I_mag);
	}

	for(int i=0;i<num_patches;i++)
	{

		double r=patchSize/2;
		float l=(float)(i/gridX.rows);
		float m=i%gridX.rows;
		float cx=gridX.at<float>(m,l)+r-0.5;
		float cy=gridY.at<float>(m,l)+r-0.5;

		Mat sample_x_t=Add(sample_x*r,cx);
		Mat sample_y_t=Add(sample_y*r,cy);
		float *pt1=sample_y_t.ptr<float>(0);
		float sample_res=pt1[1]-pt1[0];

// 		int c=(int)i/gridX.rows;
// 		float *ptc1=gridX.ptr<float>(c);
// 		int x_lo=ptc1[i%gridX.rows];

		int x_lo = gridX.at<float>(i % gridX.rows, i / gridX.rows);
		int x_hi=patchSize+x_lo-1;
/*		float *ptc2=gridY.ptr<float>(c);*/


		int y_lo=gridY.at<float>(i % gridY.rows, i / gridY.rows);
		int y_hi=y_lo+patchSize-1;

		Mat A=create(x_lo,x_hi,1);
		Mat B=create(y_lo,y_hi,1);


		Mat sample_px=meshgrid_X(A,B);
		Mat sample_py=meshgrid_Y(A,B);

		int num_pix = sample_px.total();//计算sample_px元素总数
		sample_px=reshapeY(sample_px);
		sample_py=reshapeY(sample_py);


		Mat dist_px=abs(repmat(sample_px,1,num_samples)-repmat(sample_x_t,num_pix,1));
		Mat dist_py=abs(repmat(sample_py,1,num_samples)-repmat(sample_y_t,num_pix,1));


		Mat weights_x=dist_px/sample_res;
		Mat weights_x_l=Less(weights_x,1);
		weights_x=(1-weights_x).mul(weights_x_l);

		Mat weights_y=dist_py/sample_res;
		Mat weights_y_l=Less(weights_y,1);
		weights_y=(1-weights_y).mul(weights_y_l);
		Mat weights=weights_x.mul(weights_y);

		Mat curr_sift=Mat::zeros(num_angles,num_samples,CV_32F);
		for(int a=0;a<num_angles;a++)
		{
			//Mat I=getNum(I_orientation[a],y_lo,y_hi,x_lo,x_hi);
			Mat I = I_orientation[a](Range(y_lo, y_hi), Range(x_lo, x_hi));
			Mat tep=reshapeY(I);

			// Fill tep with zeros to fit size of weight
			if (tep.cols < weights.cols)
			{
				for (int i = tep.rows; i < weights.rows; i++)
					tep.push_back(0.0f);
			}

			tep=repmat(tep,1,num_samples);
			Mat t=tep.mul(weights);
			Mat ta=sum_every_col(t);
			float *p=ta.ptr<float>(0);
			for(int i=0;i<curr_sift.cols;i++)
			{
				curr_sift.at<float>(a,i)=p[i];
			}

		}
		Mat tp=reshapeX(curr_sift);
		float *p=tp.ptr<float>(0);
		for(int j=0;j<sift_arr.cols;j++)
		{
			sift_arr.at<float>(i,j)=p[j];
		}

	}

	return sift_arr;
}

cv::Mat SIFT::sp_normalize_sift_len( Mat sift_arr )
{
	Mat siftlen(sift_arr.rows,1,CV_32F);
	Mat t=square(sift_arr);
	Mat x=sum_row(t);
	sqrt(x,siftlen);

	return siftlen;
}

cv::Mat SIFT::sp_normalize_sift_arr( Mat sift_arr,float threshold )
{
	Mat siftlen=sp_normalize_sift_len(sift_arr);
	Mat normalize_ind1=compare(siftlen,threshold);
	Mat normalize_ind2=change(normalize_ind1);

	Mat sift_arr_hcontrast=search(sift_arr,normalize_ind1);
	sift_arr_hcontrast=sift_arr_hcontrast/repmat(search(siftlen,normalize_ind1),1,sift_arr.cols);//此处应为点除

	Mat sift_arr_lcontrast=search(sift_arr,normalize_ind2);
	sift_arr_lcontrast=sift_arr_lcontrast/threshold;

	sift_arr_hcontrast= suppresss(sift_arr_hcontrast,0.2);
	sift_arr_lcontrast= suppresss(sift_arr_lcontrast,0.2);

	Mat tep(sift_arr_hcontrast.rows,1,CV_32F);
	sqrt(sum_row(square(sift_arr_hcontrast)),tep);
	sift_arr_hcontrast = sift_arr_hcontrast /repmat(tep, 1,sift_arr.cols);

	assign(sift_arr,normalize_ind1,sift_arr_hcontrast);
	assign(sift_arr,normalize_ind2,sift_arr_lcontrast);

	return sift_arr;
}

FeatureItem SIFT::CalculateSiftDescriptorFromFile( const string& filename, int gridSpacing, int patchSize, int maxImSize, float nrml_threshold )
{
	//Mat img = imread("009_0002.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	try
	{
		Mat iplImg = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
		//IplImage* GrayImage = cvCreateImage(cvGetSize(iplImg),IPL_DEPTH_8U,1);
		//cvCvtColor(iplImg,GrayImage,CV_RGB2GRAY);

		Mat result;
		iplImg.convertTo(result, CV_32FC1); /*cvCreateMat(iplImg->height,iplImg->width,CV_32FC1 );*/
		//cvConvert(GrayImage,mat);
		iplImg.release();

		Mat Img=im2double(result);
		result.release();

		return CalculateSiftDescriptor(Img, gridSpacing, patchSize, maxImSize, nrml_threshold);
	}catch (cv::Exception e)
	{
		printf("Exception happened in file %s\n",filename.c_str());
		printf("%s\n", e.msg.c_str());
		return FeatureItem();
	}
}

FeatureItem SIFT::CalculateSiftDescriptor(Mat Img, int gridSpacing, int patchSize, int maxImSize, float nrml_threshold)
{
		CvSize size=Img.size();
		//Resize if image is larger than maxImSize
		int imgLength = size.width > size.height ? size.width : size.height;
		if (imgLength > maxImSize)
		{
			float scale = (float)imgLength / maxImSize;
			size.width /= scale;
			size.height /= scale;
			resize(Img, Img, size, 0, 0, CV_INTER_AREA);
		}
		float remX=(size.width-patchSize)%gridSpacing;
		int offsetX = floor(remX/2)+1;
		float remY = (size.height-patchSize)%gridSpacing;
		int offsetY = floor(remY/2)+1;
		Mat X=create(offsetX,(size.width-patchSize+1),gridSpacing);
		Mat Y=create(offsetY,(size.height-patchSize+1),gridSpacing);
		Mat gridX=meshgrid_X(X,Y);
		Mat gridY=meshgrid_Y(X,Y);

		Mat siftArr=sp_find_sift_grid(Img,gridX,gridY,patchSize,0.8);


		Mat siftlen=sp_normalize_sift_len(siftArr);

		siftArr=sp_normalize_sift_arr(siftArr,nrml_threshold);
		FeatureItem fea;
		fea.feaArr = siftArr.t();
		fea.height = size.height;
		fea.width = size.width;
		fea.x = reshapeY(gridX) + patchSize / 2 - 0.5;
		fea.y = reshapeY(gridY) + patchSize / 2 - 0.5;

		return fea;
}