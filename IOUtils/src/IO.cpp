#include "IO.h"

Mat IOUtils::readMatrixFromYML( const path filename )
{
	FileStorage fs(filename.string(), FileStorage::READ);
	Mat read;
	if (exists(filename))
		fs["mat"] >> read;

	return read;
}

void IOUtils::saveMatrixToYML( const path filename, const Mat& m )
{
	FileStorage fs(filename.string(), FileStorage::WRITE);
	fs << "mat" << m;
}
