#include <Python.h>
#include <boost/python.hpp>
#include "python-Retrieval.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(retrieval)
{
	class_<py_Retrieval>("Retrieval")
		.def("processQuery", & py_Retrieval::py_ProcessQuery)
		.def("loadConfigFile", & py_Retrieval::loadConfigFile)
		.def("savdConfigFile", & py_Retrieval::savdConfigFile)
		.def("loadMainDB", & py_Retrieval::loadMainDB)
		.def("loadSemanticDB". & py_Retrieval::loadSemanticDB)
	;
}