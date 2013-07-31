#include <boost/python.hpp>
#include <Python.h>
#include  "SparseCoder.h"

using namespace boost::python;
using namespace SparseCoding;

BOOST_PYTHON_MODULE(SparseCoder)
{
	class_<SparseCoder>("SparseCoder")
		.def("encode", & SparseCoder::encode)
		.def("loacConfig", & SparseCoder::loadConfig)
		.def("saveConfig", & SparseCoder::saveConfig)
		.def_readwrite("num_bases", & SparseCoder::num_bases)
		.def_readwrite("Sigma", & SparseCoder::Sigma)
		.def_readwrite("beta", & SparseCoder::beta)
		.def_readwrite("gamma", & SparseCoder::gamma)
		.def_readwrite("num_iters", & SparseCoder::num_iters)
		.def_readwrite("isParallel", & SparseCoder::isParallel)
		.def_readwrite("threads", & SparseCoder::threads)
	;
}