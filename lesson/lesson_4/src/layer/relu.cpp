#include "relu.h"
#include <iostream>
using namespace std;

namespace ncnn {

ReLU::ReLU() {
}

int ReLU::load_param(const ParamDict& pd) {
    slope = pd.get(0, 0.f);
    return 0;
}


}
