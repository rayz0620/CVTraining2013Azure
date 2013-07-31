#include <boost/python.hpp>
#include <Python.h>
#include "FeatureDatabase.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(FeatureItem)
{
	class_<FeatureItem>("FeatureItem")
		.def_readwrite("id", & FeatureItem::id)
		.def_readwrite("feaArr", & FeatureItem::feaArr)
		.def_readwrite("width", & FeatureItem::width)
		.def_readwrite("height", & FeatureItem::height)
		.def_readwrite("x", & FeatureItem::x)
		.def_readwrite("y", & FeatureItem::y)
	;
}