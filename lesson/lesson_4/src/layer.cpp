#include "layer.h"
#include <string.h>
#include <iostream>
using namespace std;

namespace ncnn {

Layer::Layer() { }
Layer::~Layer() {}

int Layer::load_param(const ParamDict&) { return 0; }
}
