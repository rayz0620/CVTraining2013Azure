#pragma once
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

#define DB_ITEM_YAML_ELEM_NAME "db_item"

using namespace boost::filesystem;
using namespace std;
using namespace cv;



struct RetrievalDatabaseItem{
	string id;
	vector<string> label;
	Mat feature;

	void write(FileStorage& fs) const;
	void read(const FileNode& fs);
};

void write(FileStorage& fs, const std::string&, const RetrievalDatabaseItem& x);
void read(const FileNode& node, RetrievalDatabaseItem& x, const RetrievalDatabaseItem& default_value = RetrievalDatabaseItem());

typedef map<string, RetrievalDatabaseItem> DB_BASE;

class RetrievalDatabase: public DB_BASE{
public:
	RetrievalDatabase();
	RetrievalDatabase(const string& dbPath, const string& extension = ".yml", bool isRecursive = true );
	//bool convertFromRaw(const path& rawPath, const path& targetPath, const string& extension = ".gz", bool isRecursive = true);
	bool loadraw(const string& dbPath, const string& extension = ".yml", bool isRecursive = true  );
	bool load(const string& dbPath, const string& extension = ".yml", bool isRecursive = true  );
	bool save( string& targetPath, const string& extension = ".yml");
	~RetrievalDatabase();
private:
};

