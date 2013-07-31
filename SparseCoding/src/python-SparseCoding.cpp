#include <boost/python.hpp>
#include <Python.h>
#include "sparseCoding.h"

using namespace boost::python;
using namespace SparseCoding;

BOOST_PYTHON_MODULE(SparseCoding)
{
	def("reg_sparse_coding", reg_sparse_coding);
}
