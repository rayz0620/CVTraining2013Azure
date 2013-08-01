#include <boost/python.hpp>
#include <Python.h>
#include "SemanticDatabase.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(SemanticDatabase)
{
	class_<SemanticDatabase>("SemanticDatabase")
		.def("generateFeatureMatrix", &SemanticDatabase::generateFeatureMatrix)
		.def("saveSemanticInfo", & SemanticDatabase::saveSemanticInfo)
		.def("loadSemanticInfo", & SemanticDatabase::loadSemanticInfo)
		.add_property("relationMatrix", & SemanticDatabase::getRelationMatrix)
		.add_property("featureMatrix", & SemanticDatabase::getFeatureMatrix)		
	;
}