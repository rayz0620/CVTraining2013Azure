#include <boost/python.hpp>
#include <Python.h>
#include "IO.h"

using namespace boost::python;
using namespace IOUtils;

BOOST_PYTHON_MODULE(IOUtils)
{
	def("readMatrixFromYML", readMatrixFromYML);
	def("saveMatrixToYML", saveMatrixToYML);
}