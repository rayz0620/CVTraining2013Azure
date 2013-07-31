#include <boost/python.hpp>
#include <Python.h>
#include "FeatureDatabase.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(FeatureDatabase)
{
    class_<FeatureDatabase>("FeatureDatabase")
		.def("generateDatabase", & FeatureDatabase::generateDatabase)
		.def("generateSingleDatabaseItem", & FeatureDatabase::generateSingleDatabaseItem)
		.def("randomDictionary", & FeatureDatabase::randomDictionary)
		.def("saveConfig", & FeatureDatabase::saveConfig)
		.def("loadConfig", & FeatureDatabase::loadConfig)
		.def_readwrite("gridSpacing", & FeatureDatabase::gridSpacing)
		.def_readwrite("patchSize", & FeatureDatabase::patchSize)
		.def_readwrite("maxImSize", & FeatureDatabase::maxImSize)
		.def_readwrite("isParallel", & FeatureDatabase::isParallel)
		.def_readwrite("threads", & FeatureDatabase::threads)
    ;
}