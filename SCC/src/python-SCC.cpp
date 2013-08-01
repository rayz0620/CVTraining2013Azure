#include <boost/python.hpp>
#include <Python.h>
#include "SCC.h"

using namespace boost::python;
using namespace SCC;

BOOST_PYTHON_MODULE(SCC)
{
	def("semantic_neighbours", semantic_neighbours);
	def("retrievalScore", retrievalScore);
}
