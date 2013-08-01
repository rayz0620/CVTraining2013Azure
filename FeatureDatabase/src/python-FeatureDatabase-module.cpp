#include <Python.h>
#include <boost/python.hpp>
#include "python-FeatureDatabase.h"
using namespace boost::python;

BOOST_PYTHON_MODULE(FeatureDatabase)
{
    class_<Python_FeatureDatabase>("FeatureDatabase")
    	.def(init<const std::string &>())
    	.def("calculateItem", &Python_FeatureDatabase::calculateItem) // doSomething is the method in class ABC you wish to expose. One line for each method (or function depending on how you structure your code). Note: You don't have to expose everything in the library, just the ones you wish to make available to python.
    ;
}