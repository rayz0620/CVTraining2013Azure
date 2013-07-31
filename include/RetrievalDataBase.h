#pragma once
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

#define DB_ITEM_YAML_ELEM_NAME "db_item"

using namespace boost::filesystem;
using namespace std;
using namespace cv;



struct RetrivalDatabaseItem{
	string id;
	vector<string> label;
	Mat feature;

	void write(FileStorage& fs) const;
	void read(const FileNode& fs);
};

void write(FileStorage& fs, const std::string&, const RetrivalDatabaseItem& x);
void read(const FileNode& node, RetrivalDatabaseItem& x, const RetrivalDatabaseItem& default_value = RetrivalDatabaseItem());

typedef map<string, RetrivalDatabaseItem> DB_BASE;

class RetrievalDatabase: public DB_BASE{
public:
	RetrievalDatabase();
	RetrievalDatabase(const path& dbPath, const string& extension = ".yml", bool isRecursive = false );
	bool convertFromRaw(const path& rawPath, const path& targetPath, const string& extension = ".yml", bool isRecursive = false);
	bool loadraw(const path& dbPath, const string& extension = ".yml", bool isRecursive = false  );
	bool load(const path& dbPath, const string& extension = ".yml", bool isRecursive = false  );
	bool save(path targetPath, const string& extension = ".yml");
	~RetrievalDatabase();
private:
};

