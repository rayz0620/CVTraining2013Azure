#include <boost/filesystem.hpp>
#include <string>
#include <boost/thread.hpp>
#include <boost/threadpool.hpp>
#include "FeatureItem.h"

using namespace std;
using namespace boost::filesystem;


class FeatureDatabase{
public:
	FeatureDatabase();
	FeatureDatabase(const FeatureDatabase& other);
	bool generateDatabase(const string imgPath, const string featPath);
	void generateSingleDatabaseItem(string imgPath, string featPath);
/*	bool saveAll( path targetPath, const string& extension = ".yml" );*/
	bool randomDictionary(const string featPath, const string dictPath, float percentage);

	void saveConfig(const string filename);
	void loadConfig(const string filename);

	int gridSpacing;
	int patchSize;
	int maxImSize;
	float nrml_threshold;
	bool isParallel;
	int threads;
private:
	boost::shared_mutex dbIOMutex;
	boost::shared_mutex dictIOMutex;

	bool saveSingle(const FeatureItem& item, string targetPath, const string extension = ".gz" );
};
