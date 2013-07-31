#include <boost/python.hpp>
#include <Python.h>
#include "LLC.h"

using namespace boost::python;
using namespace LLC;

BOOST_PYTHON_MODULE(LLCoder)
{
	class_<LLCoder>("LLCoder")
		.def("generateLLCDatabase", & LLCoder::generateLLCDatabase)
		.def("LLC_pooling", & LLCoder::LLC_pooling)
		.def("saveConfig", & LLCoder::saveConfig)
		.def("loadConfig", & LLCoder::loadConfig)
		.def_readwrite("B", & LLCoder::B)
		.def_readwrite("pyramid", & LLCoder::pyramid)
		.def_readwrite("knn", & LLCoder::knn)
		.def_readwrite("isParallel", & LLCoder::isParallel)
		.def_readwrite("threads", & LLCoder::threads)
	;
}