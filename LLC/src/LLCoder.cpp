#include "LLCoder.h"
#include "LLC.h"
#include "sum.h"
#include "IO.h"
#include <boost/threadpool.hpp>
#include <cstdio>

using namespace IOUtils;
using namespace cv;

bool LLC::LLCoder::generateLLCDatabase( path srcPath, path destPath )
{
	printf("Generating LLC Coding from %s\n", srcPath.parent_path().c_str());
	FileStorage fs;
	int fileCount = 0;
	if (exists(srcPath))
	{
		auto it = recursive_directory_iterator(srcPath);
		auto end_it = recursive_directory_iterator();
		if (isParallel)
		{
			boost::threadpool::pool pool(threads);
			for (; it != end_it; it++)
			{
				path file = it->path();
				if (file.extension() == ".xml" ||
					file.extension() == ".yml" ||
					file.extension() == ".gz" )
				{
					pool.schedule(boost::bind(
						&LLCoder::generateLLCSingle, this, file, destPath));
					fileCount++;
				}
				pool.wait(threads);
			}
			pool.wait(0);

		}else
		{
			for (; it != end_it; it++)
			{
				path file = it->path();
				if (file.extension() == ".xml" ||
					file.extension() == ".yml" ||
					file.extension() == ".gz" )
				{
					generateLLCSingle(file, destPath);
					fileCount++;
				}
			}
		}

		printf("Loaded %d items from database\n", fileCount);
		return true;
	}
	else return false;
}

void LLC::LLCoder::generateLLCSingle( path srcPath, path destPath )
{
	FileStorage fs(srcPath.string(), FileStorage::READ);
	if (fs.isOpened())
	{
		FeatureItem feat;
		fs[FEA_ITEM_YAML_ELEM_NAME] >> feat;
		Mat llc = LLC_pooling(feat, B, pyramid, knn);
		saveSingle(llc, destPath, srcPath.filename().string(), "");
		remove(srcPath);
		printf("Generated LLC for %s\n", srcPath.stem().string().c_str());
	}
}

bool LLC::LLCoder::saveSingle( Mat item, path destPath, const string& filename, const string& extension /*= ".yml.gz"*/ )
{
	if (exists(destPath) && !is_directory(destPath))
		return false;
	else if (!exists(destPath))
		create_directory(destPath);

	path currentFile = destPath;
	currentFile /= (filename + extension);
	saveMatrixToYML(currentFile, item);
	return true;
}

void LLC::LLCoder::saveConfig( const string& filename )
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "B" << B;
		fs << "pyramid" << pyramid;
		fs << "knn" << knn;
		fs << "isParallel" << isParallel;
		fs << "threads" << threads;
	}
}

void LLC::LLCoder::loadConfig( const string& filename )
{
	FileStorage fs(filename, FileStorage::READ);
	if (fs.isOpened())
	{
		if (fs["B"].isString())
		{
			string filename;
			fs["B"] >> filename;
			B = readMatrixFromYML(filename);
		}else
			fs["B"] >> B;

		if (fs["pyramid"].isString())
		{
			string filename;
			fs["pyramid"] >> filename;
			pyramid = readMatrixFromYML(filename);
		}else
			fs["pyramid"] >> pyramid;

		fs["knn"] >> knn;
		fs["isParallel"] >> isParallel;
		fs["threads"] >> threads;
	}
}

LLC::LLCoder::LLCoder()
{

}
