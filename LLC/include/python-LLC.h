#include "LLC.h"
#include <Python.h>
#include <boost/python.hpp>

using namespace LLC;
using namespace boost::python;

class python_LLC
{
public:
	python_LLC();
	object py_calculateLLC(object feaSet, object B, object pyramid, object knn);
};