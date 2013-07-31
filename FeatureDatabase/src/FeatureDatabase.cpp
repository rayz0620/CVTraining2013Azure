#include "FeatureDatabase.h"
#include "SIFT.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include "Util.h"

using namespace std;
using namespace SIFT;
using namespace MatrixUtils;

// bool FeatureDatabase::saveAll( path targetPath, const string& extension /*= ".yml" */ )
// {
// 	printf("Saving database to %s\n", targetPath.directory_string().c_str());
// 	FileStorage fs;
// 	if (exists(targetPath) && !is_directory(targetPath))
// 		return false;
// 	else if (!exists(targetPath))
// 		create_directory(targetPath);
//
// 	for (auto item: *this)
// 	{
// 		path currentFile = targetPath;
// 		currentFile /= (item.first + extension);
// 		fs.open(currentFile, FileStorage::WRITE);
// 		if (fs.isOpened())
// 			fs << FEA_ITEM_YAML_ELEM_NAME << item.second;
// 		fs.release();
// 	}
// 	return true;
// }
FeatureDatabase::FeatureDatabase(const FeatureDatabase& other)
{
	gridSpacing = other.gridSpacing;
	patchSize = other.patchSize;
	maxImSize = other.maxImSize;
	nrml_threshold = other.nrml_threshold;
	isParallel = other.isParallel;
	threads = other.threads;
}

bool FeatureDatabase::saveSingle( const FeatureItem& item, string targetPath, const string extension /*= ".yml" */ )
{
	if (exists(targetPath) && !is_directory(targetPath))
		return false;
	else if (!exists(targetPath))
		create_directory(targetPath);

	path currentFile = targetPath;
	currentFile /= (item.id + extension);
	FileStorage fs(currentFile.string(), FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << FEA_ITEM_YAML_ELEM_NAME << item;
		return true;
	}
	else return false;
}


bool FeatureDatabase::generateDatabase( const string imgPath, const string featPath )
{
	path imgP(imgPath);
	printf("Generating Feature Database from %s\n", imgP.parent_path().c_str());
	FileStorage fs;
	int fileCount = 0;
	if (exists(imgP))
	{
		auto it = recursive_directory_iterator(imgP);
		auto end_it = recursive_directory_iterator();
		if (isParallel)
		{
			boost::threadpool::pool pool(threads);
			for (; it != end_it; it++)
			{
				path file = it->path();
				if (file.extension() == ".jpg" ||
					file.extension() == ".bmp" ||
					file.extension() == ".png" )
				{
					pool.schedule(boost::bind(
						&FeatureDatabase::generateSingleDatabaseItem, this, file.string(), featPath));
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
				if (file.extension() == ".jpg" ||
					file.extension() == ".bmp" ||
					file.extension() == ".png" )
				{
					generateSingleDatabaseItem(file.string(), featPath);
					fileCount++;
				}
			}
		}

		printf("Loaded %d items from database\n", fileCount);
		return true;
	}
	else return false;
}

FeatureDatabase::FeatureDatabase()
{

}

void FeatureDatabase::generateSingleDatabaseItem( string imgPath, string featPath )
{
	path imgP(imgPath);
	path featP(featPath);
	FeatureItem item = CalculateSiftDescriptor(imgPath, gridSpacing, patchSize, maxImSize, nrml_threshold);
	item.id = imgP.stem().string();
// 	dbIOMutex.lock_upgrade();
// 	operator[](imgPath.basename()) = item;
// 	dbIOMutex.unlock_upgrade();

	saveSingle(item, featPath);
}

void FeatureDatabase::saveConfig( const string filename )
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "gridSpacing" << gridSpacing;
		fs << "patchSize" << patchSize;
		fs << "maxImSize" << maxImSize;
		fs << "nrml_threshold" << nrml_threshold;
		fs << "isParallel" << isParallel;
		fs << "threads" << threads;
	}
}

void FeatureDatabase::loadConfig( const string filename )
{
	FileStorage fs(filename, FileStorage::READ);
	if (fs.isOpened())
	{
		fs["gridSpacing"] >> gridSpacing;
		fs["patchSize"] >> patchSize;
		fs["maxImSize"] >> maxImSize;
		fs["nrml_threshold"] >> nrml_threshold;
		fs["isParallel"] >> isParallel;
		fs["threads"] >> threads;
	}
}

bool FeatureDatabase::randomDictionary( const string featPath, const string dictPath, float percentage )
{
	path featP(featPath);
	path dictP(dictPath);
	printf("Generating dictionary from %s\n", featP.parent_path().c_str());
	FileStorage fs;
	int fileCount = 0;
	int featLength = 0;
	int matType = CV_32F;

	Mat allFeature;
	if (exists(featP))
	{
		auto it = recursive_directory_iterator(featP);
		auto end_it = recursive_directory_iterator();

		// Count number of features
		for (; it != end_it; it++)
		{

			path file = it->path();
			if (file.extension() == ".yml" ||
				file.extension() == ".xml" ||
				file.extension() == ".gz")
			{
				fs.open(file.string(), FileStorage::READ);
				FeatureItem item;
				fs[FEA_ITEM_YAML_ELEM_NAME] >> item;
				fs.release();
				featLength = item.feaArr.rows;
				matType = item.feaArr.type();
				break;
			}
		}

		// Load and combine features
		allFeature.create(0, featLength, matType);

		it = recursive_directory_iterator(featP);
		for (; it != end_it; it++)
		{
			path file = it->path();
			if (file.extension() == ".yml" ||
				file.extension() == ".xml" ||
				file.extension() == ".gz")
			{
				fs.open(file.string(), FileStorage::READ);
				FeatureItem item;
				fs[FEA_ITEM_YAML_ELEM_NAME] >> item;
				shuffleCol(item.feaArr);
				int numSelectedCol = item.feaArr.cols * percentage;
				Mat feaT = item.feaArr.t();
				allFeature.push_back(feaT.rowRange(0, numSelectedCol));
				fs.release();
				fileCount++;
				printf("Loaded feature from %s\n", file.filename().c_str());
			}
		}
		allFeature = allFeature.t();
		shuffleCol(allFeature);
		fs.open(dictP.string(), FileStorage::WRITE);
		fs << "mat" << allFeature;
		printf("Randomly chose %d features as initial dictionary\n", allFeature.cols);
		return true;
	}
	else return false;
}
