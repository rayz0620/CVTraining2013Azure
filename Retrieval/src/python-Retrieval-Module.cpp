#include <Python.h>
#include <boost/python.hpp>
#include "python-Retrieval.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(retrieval)
{
	class_<py_Retrieval>("Retrieval")
		.def("processQuery", & py_Retrieval::py_ProcessQuery)
		.def("loadConfig", & py_Retrieval::loadConfigFile)
		.def("savdConfig", & py_Retrieval::saveConfigFile)
		.def("loadMainDB", & py_Retrieval::loadMainDB)
		.def("loadSemanticDB", & py_Retrieval::loadSemanticDB)
	;
}