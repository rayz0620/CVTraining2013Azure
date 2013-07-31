#include <Python.h>
#include <boost/python.hpp>

#include "SIFT.h"

using namespace boost::python;
using namespace SIFT;

BOOST_PYTHON_MODULE(sift)
{
    using namespace boost::python;
    def("CalculateSiftDescriptor", CalculateSiftDescriptor);
}
