#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

typedef float MatElem;

using namespace std;
using namespace cv;

namespace MatrixUtils
{

//************************************
// Method:    MatMemberwiseIsZero
// FullName:  MatrixUtils::MatMemberwiseIsZero
// Access:    public
// Returns:   Mat
// Qualifier:
// Parameter: Mat & xZero
//
// Check if each element in the matrix is zero
// Returns a matrix of same size and type of the input
// If an element in position p is nonzero, the element at p in output
//	 is 1, otherwise is 0
//************************************
Mat MatMemberwiseIsZero( const Mat xZero);

//************************************
// Method:    MatMemberwiseIsNonZero
// FullName:  MatrixUtils::MatMemberwiseIsNonZero
// Access:    public
// Returns:   Mat
// Qualifier:
// Parameter: Mat & xZero
//
// Check if each element in the input matrix is non-zero
// Returns a matrix of same size and type of the input
// If an element in position p is nonzero, the element at p in output
//	 is 1, otherwise is 0
//************************************
Mat MatMemberwiseIsNonZero( const Mat xZero);

//************************************
// Method:    MatMemberwiseNonPositive
// FullName:  MatrixUtils::MatMemberwiseNonPositive
// Access:    public
// Returns:   Mat
// Qualifier:
// Parameter: Mat m
//
// Check if each element in the matrix is non-positive
// Returns a matrix of same size and type of the input
// If an element in position p is nonzero, the element at p in output
//	is 1, otherwise is 0
//************************************
Mat MatMemberwiseNonPositive ( const Mat src);

//************************************
// Method:    isZeroMatrix
// FullName:  MatrixUtils::isZeroMatrix
// Access:    public
// Returns:   bool
// Qualifier:
// Parameter: const Mat m
//
// Check if all elements in the input matrix are zero
//************************************
bool isZeroMatrix(const Mat m);


//************************************
// Method:    SubVector
// FullName:  MatrixUtils::SubVector
// Access:    public
// Returns:   Mat
// Qualifier:
// Parameter: const InputArray src			The vector to be processed
// Parameter: const InputArray rowCoord		A column vector containing indices
// Parameter: const InputArray colCoord
//
// Return a subvector of input src, consisiting of elements of src
//   correspoding to the indices in rowCoord
//************************************
Mat SubVector(const InputArray src, const InputArray rowCoord);

Mat SubDiagonal(const InputArray src, const InputArray rowCoord,
                const InputArray colCoord = noArray());

Mat LogicSubVector(const InputArray src, const InputArray mask);

Mat LogicSubDiagonal( const InputArray src, const InputArray rowCoord, const InputArray colCoord = noArray());

Mat MatrixSign(const InputArray m);

Mat find(const InputArray m);

void MultiAssign(InputArray dest, const InputArray index, const InputArray val);

void LogicMultiAssign(InputArray dest, const InputArray mask, const InputArray val);

Mat reorderCol(InputArray src, InputArray order);

//************************************
// Method:    printMatrix
// FullName:  MatrixUtils::printMatrix
// Access:    public
// Returns:   void
// Qualifier:
// Parameter: const Mat & m
// Parameter: const String & title
// Parameter: bool optionOverride
//
// Print a matrix to the screen
// If tilte is not empty, it will be printed above the matrix
//************************************
void printMatrix(const Mat m, const String& title = "", bool optionOverride = false);

Mat sortColumn(Mat m, bool isDecent);

Mat colSum(Mat m);

double sumOfMemWiseMultiply(Mat left, Mat right);

double sumOfAbs(Mat m);

vector<int> randPerm(int length, int begin = 0);

Mat shuffleCol(InputArray dst);
}
