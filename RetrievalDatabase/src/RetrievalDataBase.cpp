#include "RetrievalDataBase.h"
#include "IO.h"

using namespace IOUtils;

void RetrivalDatabaseItem::write( FileStorage& fs ) const
{
	fs << "{";
	fs << "id" << id;
	fs << "label" << "[";
	for (auto label_it:label)
	{
		fs << label_it;
	}
	fs << "]";
	fs << "feature" << feature;
	fs << "}";
}

void RetrivalDatabaseItem::read( const FileNode& node )
{
	node["id"] >> id;

	FileNode n = node["label"];
	label.clear();
	for (auto label_it: n)
	{
		label.push_back((string)label_it);
	}

	node["feature"] >> feature;
}


RetrievalDatabase::RetrievalDatabase( const path& dbPath, const string& extension /*= ".yml"*/, bool isRecursive /*= false */ )
	:DB_BASE()
{
	load(dbPath, extension, isRecursive);
}

RetrievalDatabase::RetrievalDatabase()
{

}


bool RetrievalDatabase::load( const path& dbPath, const string& extension, bool isRecursive)
{
	printf("Loading Retrieval Database from %s\n", dbPath.parent_path().c_str());
	FileStorage fs;
	if (exists(dbPath))
	{
		auto it = recursive_directory_iterator(dbPath);
		auto end_it = recursive_directory_iterator();

		if (!isRecursive)
			it.no_push();

		for (; it != end_it; it++)
		{
			auto &file = it->path();
			if (file.extension() == extension)
			{
				RetrivalDatabaseItem newItem;
				fs.open(file.string(), FileStorage::READ);
				fs[DB_ITEM_YAML_ELEM_NAME] >> newItem;

				if (!newItem.feature.empty())
					operator[](newItem.id) = newItem;
			}
		}
		printf("Loaded %d items from database\n", (int)size());
		return true;
	}
	else return false;
}

RetrievalDatabase::~RetrievalDatabase()
{
	clear();
}

bool RetrievalDatabase::loadraw( const path& dbPath, const string& extension /*= ".yml"*/, bool isRecursive /*= false */ )
{
	printf("Loading Database from %s\n", dbPath.parent_path().c_str());
	if (exists(dbPath))
	{
		auto it = recursive_directory_iterator(dbPath);
		auto end_it = recursive_directory_iterator();

		if (!isRecursive)
			it.no_push();

		for (; it != end_it; it++)
		{
			auto &file = it->path();
			if (file.extension() == extension)
			{
				RetrivalDatabaseItem newItem;
				newItem.feature = readMatrixFromYML(file);
				newItem.id = file.stem().string();
				newItem.label.push_back(newItem.id.substr(0,3));

				if (!newItem.feature.empty())
					operator[](newItem.id) = newItem;
			}
		}
		printf("Loaded %d items from database\n", (int)size());
		return true;
	}
	else return false;
}

bool RetrievalDatabase::save( path targetPath, const string& extension /*= ".yml"*/ )
{
	FileStorage fs;

	if (exists(targetPath) && !is_directory(targetPath))
		return false;
	else if (!exists(targetPath))
		create_directory(targetPath);

	for (auto item: *this)
	{
		path currentFile = targetPath;
		currentFile /= (item.first + extension);
		fs.open(currentFile.string(), FileStorage::WRITE);
		if (fs.isOpened())
			fs << DB_ITEM_YAML_ELEM_NAME << item.second;
		fs.release();
	}
	return true;
}

void write( FileStorage& fs, const std::string&, const RetrivalDatabaseItem& x )
{
	x.write(fs);
}

void read( const FileNode& node, RetrivalDatabaseItem& x, const RetrivalDatabaseItem& default_value /*= RetrivalDatabaseItem()*/ )
{
	if(node.empty())
		x = default_value;
	else
		x.read(node);
}
