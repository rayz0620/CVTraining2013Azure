#include "LLC.h"
#include <Python.h>

using namespace LLC;

class python_LLC: public LLCoder
{
public:
	python_LLC();
	PyObject* py_calculateLLC(FeatureItem feaSet);
};