#include "Retrieval.h"
#include <Python.h>
#include <boost/python.hpp>
#include <string>

using namespace boost::python;

class py_Retrieval: public Retrieval{
public:
	py_Retrieval();
	boost::python::list py_ProcessQuery(object feature, object topNum);
	void loadMainDB(string path);
	void loadSemanticDB(string path);
};