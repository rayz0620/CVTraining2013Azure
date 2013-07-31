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
	bool generateDatabase(const path imgPath, const path featPath);
	void generateSingleDatabaseItem(path imgPath, path featPath);
/*	bool saveAll( path targetPath, const string& extension = ".yml" );*/
	bool randomDictionary(const path featPath, const path dictPath, float percentage);

	void saveConfig(const path filename);
	void loadConfig(const path filename);

	int gridSpacing;
	int patchSize;
	int maxImSize;
	float nrml_threshold;
	bool isParallel;
	int threads;
private:
	boost::shared_mutex dbIOMutex;
	boost::shared_mutex dictIOMutex;

	bool saveSingle(const FeatureItem& item, path targetPath, const string& extension = ".gz" );
};
