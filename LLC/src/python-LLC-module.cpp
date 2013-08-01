#include <boost/python.hpp>
#include <Python.h>
#include "python-LLC.h"

using namespace boost::python;
using namespace LLC;

BOOST_PYTHON_MODULE(LLC)
{
	class_<python_LLC>("LLC")
		.def("calculateLLC", & python_LLC::py_calculateLLC)
	;
}