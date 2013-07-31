#include "Util.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <stdlib.h>

#define MAT_AT(m, row, col) ((MatElem*)m.data)[row * m.step1() + col]

Mat MatrixUtils::MatMemberwiseIsZero( const Mat src )
{
	Mat result = Mat::zeros(src.size(), src.type());
// 	MatConstIterator_<MatElem> src_it = src.begin<MatElem>(),
// 		src_end = src.end<MatElem>();
// 	MatIterator_<MatElem> res_it = result.begin<MatElem>(),
// 		res_end = result.end<MatElem>();

	for (int r = 0; r < src.rows; r++)
		for (int c = 0; c < src.cols; c++)
	{
		if (MAT_AT(src, r, c) == 0)
			MAT_AT(result, r, c) = 1.0;
	}
	return result;
}

Mat MatrixUtils::MatMemberwiseIsNonZero( const Mat src )
{
	Mat result = Mat::zeros(src.size(), src.type());

	for (int r = 0; r < src.rows; r++)
		for (int c = 0; c < src.cols; c++)
		{
			if (MAT_AT(src, r, c) != 0)
				MAT_AT(result, r, c) = 1.0;
		}
	return result;
}

Mat MatrixUtils::MatMemberwiseNonPositive( const Mat src )
{
	Mat result = Mat::zeros(src.size(), src.type());

	for (int r = 0; r < src.rows; r++)
		for (int c = 0; c < src.cols; c++)
		{
			if (MAT_AT(src, r, c) <= 0)
				MAT_AT(result, r, c) = 1.0;
		}
	return result;
}

bool MatrixUtils::isZeroMatrix( const Mat m )
{
	for (int r = 0; r < m.rows; r++)
		for (int c = 0; c < m.cols; c++)
		{
			if (MAT_AT(m, r, c) != 0)
			{
				return false;
			}
		}
	return true;
}


Mat MatrixUtils::SubVector( const InputArray src, const InputArray rowCoord )
{
	Mat srcM = src.getMat(), rowM = rowCoord.getMat();
	Mat subV(rowM.rows, 1, src.type());

	for (int i = 0; i < rowM.size().height; i++)
	{
		int idx = MAT_AT(rowM, i, 0);
		MAT_AT(subV, i, 0) = MAT_AT(srcM, idx, 0);
	}
	return subV;
}


Mat MatrixUtils::LogicSubVector( const InputArray src, const InputArray mask )
{
	Mat srcM = src.getMat(), maskM = mask.getMat();
	Mat indices = find(mask);

	Mat subV(indices.rows, 1, src.type());

	for (int i = 0; i < indices.rows; i++)
	{
		int idx = MAT_AT(indices, i, 0);
		MAT_AT(subV, i, 0) = MAT_AT(srcM, idx, 0);
	}
	return subV;
}

Mat MatrixUtils::LogicSubDiagonal( const InputArray src, const InputArray rowCoord, const InputArray colCoord /*= noArray()*/ )
{
	Mat srcM = src.getMat(), rowM = rowCoord.getMat(), colM = colCoord.getMat();
	Mat rowIndices = find(rowM);
	Mat colIndices = find(colM);
	int rowIndNum = rowIndices.rows;
	int colIndNum = colIndices.rows;

	Mat result(rowIndNum, colIndNum, srcM.type());

	for (int i = 0; i < rowIndNum; i++)
	{
		for (int j = 0; j < colIndNum; j++)
		{
			int rowIdx = MAT_AT(rowIndices, i, 0);
			int colIdx = MAT_AT(colIndices, j, 0);
			MAT_AT(result, i, j) = MAT_AT(srcM, rowIdx, colIdx);
// 			result.at<MatElem>(i, j) = srcM.at<MatElem>(
// 				rowIndices.at<MatElem>(i, 0), colIndices.at<MatElem>(j, 0));
		}
	}
	return result;
}

Mat MatrixUtils::MatrixSign( const InputArray m )
{
	Mat src = m.getMat();
	Mat sign(src.size(), src.type());

	if (!src.empty())
	{
		for (int r = 0; r < src.rows; r++)
			for (int c = 0; c < src.cols; c++)
		{
			if (MAT_AT(src, r, c) > 0)
				MAT_AT(sign, r, c) = 1.0;
			else if (MAT_AT(src, r, c) < 0)
				MAT_AT(sign, r, c) = -1.0;
			else
				MAT_AT(sign, r, c) = 0.0;
		}
		return sign;
	}else return Mat();
}

Mat MatrixUtils::find( const InputArray m )
{
	Mat src = m.getMat();
	Mat index;
	int count = 0;
	for (int i = 0; i < src.size().height; i++)
	{
		if (MAT_AT(src, i, 0) != 0)
			count++;
	}

	if (count > 0)
	{
		index.create(count, 1, src.type());

		count = 0;
		for (int i = 0; i < src.size().height; i++)
		{
			if (MAT_AT(src, i, 0) != 0)
				MAT_AT(index, count++, 0) = i;
		}
	}
	return index;
}

void MatrixUtils::LogicMultiAssign( InputArray dest, const InputArray mask, const InputArray val )
{
	Mat destM = dest.getMat();
	Mat maskM = mask.getMat();
	Mat valM = val.getMat();

	int valNum = valM.rows;
	for (int i = 0; i < destM.rows; i++)
	{
		if (MAT_AT(maskM, i, 0))
		{
			MAT_AT(destM, i, 0) = MAT_AT(destM, i, 0);
		}
		if (i >= valNum)
			break;
	}
}


void MatrixUtils::printMatrix( const Mat m, const String& title /*= ""*/, bool optionOverride /*= false*/ )
{
	if (true || optionOverride)
	{
		int height = m.size().height;
		int width = m.size().width;
		if (title.size() > 0)
		{
			cout << title << endl;
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				cout << m.at<MatElem>(i, j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

Mat MatrixUtils::SubDiagonal( const InputArray src, const InputArray rowCoord, const InputArray colCoord /*= noArray()*/ )
{
	Mat srcM = src.getMat(), rowM = rowCoord.getMat(), colM = colCoord.getMat();
	int rowIndNum = rowM.rows;
	int colIndNum = colM.rows;

	Mat result(rowIndNum, colIndNum, srcM.type());

	for (int i = 0; i < rowIndNum; i++)
	{
		for (int j = 0; j < colIndNum; j++)
		{
			int rowIdx = MAT_AT(rowM, i ,0);
			int colIdx = MAT_AT(colM, j, 0);
			MAT_AT(result, i, j) = MAT_AT(srcM, rowIdx, colIdx);
		}
	}
	return result;
}

Mat MatrixUtils::reorderCol( InputArray src, InputArray order )
{
	Mat srcM = src.getMat();//.t();
	Mat orderM = order.getMat();
	Mat result(srcM.size(), srcM.type());
	for (int r = 0; r < orderM.rows; r++)
	{
		int colIdx = MAT_AT(orderM, r, 0);
		srcM.col(colIdx).copyTo(result.col(r));
	}
	return result;
}

Mat MatrixUtils::colSum( Mat m )
{
	int width = m.size().width;
	Mat colSum(width, 1, m.type());
	for (int i = 0; i < width; i++)
	{
		MAT_AT(colSum, i, 0) = (sum(m.col(i))).val[0];
	}
	return colSum;
}

double MatrixUtils::sumOfMemWiseMultiply( Mat left, Mat right )
{
	double sum = 0.0;
	if (left.size() == right.size())
	{
		for (int r = 0; r < left.rows; r++)
			for (int c = 0; c < left.cols; c++)
			{
				sum += MAT_AT(left, r, c) * MAT_AT(right, r ,c);
			}
	}
	return sum;
}

double MatrixUtils::sumOfAbs( Mat m )
{
	double sum = 0.0;
	for (int r = 0; r < m.rows; r++)
		for (int c = 0; c < m.cols; c++)
		{
			double current = MAT_AT(m, r, c);
			sum += current < 0 ? -current : current;
		}
	return sum;
}

vector<int> MatrixUtils::randPerm( int length, int begin )
{
	vector<int> seqPerm(length);

	for (int i = begin; i < begin + length; i++)
	{
		seqPerm[i] = i;
	}
	randShuffle(seqPerm);
	return seqPerm;
}

Mat MatrixUtils::shuffleCol( InputArray dst )
{
	srand(time(NULL));
	Mat dstM = dst.getMat();
	int shuffleTimes = dstM.cols / 2;
	int i = 0;
	Mat temp(dstM.rows, 1, dstM.type());
	int randPower = ceil(log((double)dstM.cols) / log(RAND_MAX));

	while (i < shuffleTimes)
	{
		int rand1 = 1, rand2 = 1;
		for (int j = 0; j < randPower; j++)
		{
			rand1 *= rand();
			rand2 *= rand();
		}
		rand1 %= dstM.cols;
		rand2 %= dstM.cols;

		if (rand1 != rand2)
		{
			dstM.col(rand1).copyTo(temp);
			dstM.col(rand2).copyTo(dstM.col(rand1));
			temp.copyTo(dstM.col(rand2));
			i++;
		}
	}
	return dstM;
}

#undef MAT_AT
