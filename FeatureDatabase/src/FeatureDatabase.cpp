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

bool FeatureDatabase::saveSingle( const FeatureItem& item, path targetPath, const string& extension /*= ".yml" */ )
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


bool FeatureDatabase::generateDatabase( const path imgPath, const path featPath )
{
	printf("Generating Feature Database from %s\n", imgPath.parent_path().c_str());
	FileStorage fs;
	int fileCount = 0;
	if (exists(imgPath))
	{
		auto it = recursive_directory_iterator(imgPath);
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
						&FeatureDatabase::generateSingleDatabaseItem, this, file, featPath));
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
					generateSingleDatabaseItem(file, featPath);
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

void FeatureDatabase::generateSingleDatabaseItem( path imgPath, path featPath )
{
	FeatureItem item = CalculateSiftDescriptor(imgPath.string(), gridSpacing, patchSize, maxImSize, nrml_threshold);
	item.id = imgPath.stem().string();
// 	dbIOMutex.lock_upgrade();
// 	operator[](imgPath.basename()) = item;
// 	dbIOMutex.unlock_upgrade();

	saveSingle(item, featPath);
}

void FeatureDatabase::saveConfig( const path filename )
{
	FileStorage fs(filename.string(), FileStorage::WRITE);
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

void FeatureDatabase::loadConfig( const path filename )
{
	FileStorage fs(filename.string(), FileStorage::READ);
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

bool FeatureDatabase::randomDictionary( const path featPath, const path dictPath, float percentage )
{
	printf("Generating dictionary from %s\n", featPath.parent_path().c_str());
	FileStorage fs;
	int fileCount = 0;
	int featLength = 0;
	int matType = CV_32F;

	Mat allFeature;
	if (exists(featPath))
	{
		auto it = recursive_directory_iterator(featPath);
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

		it = recursive_directory_iterator(featPath);
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
		fs.open(dictPath.string(), FileStorage::WRITE);
		fs << "mat" << allFeature;
		printf("Randomly chose %d features as initial dictionary\n", allFeature.cols);
		return true;
	}
	else return false;
}
