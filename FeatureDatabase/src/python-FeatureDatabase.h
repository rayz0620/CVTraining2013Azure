#include <Python.h>
#include <string>
#include "FeatureDatabase.h"
using namespace std;

class Python_FeatureDatabase{
public:
	Python_FeatureDatabase();
	Python_FeatureDatabase(const string& config);
	void loadConfig(const string& config);
	FeatureItem calculateItem(PyObject* image);

private:
	FeatureDatabase db;
};