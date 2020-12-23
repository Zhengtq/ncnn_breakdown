#include "softmax.h"
#include "iostream"
using namespace std;

namespace ncnn {

Softmax::Softmax() { cout << "softmax constructed" << endl; }

int Softmax::load_param(const ParamDict& pd) {
    axis = pd.get(0, 9);
    return 0;
}
}
