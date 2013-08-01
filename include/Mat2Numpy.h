#include <Python.h>
#include "numpy/ndarrayobject.h"
#include "opencv2/core/core.hpp"

using cv::Mat;

static int pyopencv_to(const PyObject* o, Mat& m, const char* name = "<unknown>", bool allowND=true);
static PyObject* pyopencv_from(const Mat& m);
