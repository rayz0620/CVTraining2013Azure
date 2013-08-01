#include <boost/python.hpp>
#include <Python.h>
#include "RetrievalDatabase.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(RetrievalDatabase)
{
	class_<RetrievalDatabaseItem>("RetrievalDatabaseItem")
		.def_readwrite("id", & RetrievalDatabaseItem::id)
		.def_readwrite("label", & RetrievalDatabaseItem::label)
		.def_readwrite("feature", & RetrievalDatabaseItem::feature)
	;

	class_<RetrievalDatabase>("RetrievalDatabase")
		.def("loadRaw", & RetrievalDatabase::loadraw)
		.def("load", & RetrievalDatabase::load)
		.def("save", & RetrievalDatabase::save)
		//.def("query", & RetrievalDatabase::map<string, RetrievalDatabaseItem>::operator[])
	;
}