#include "relu.h"
#include <iostream>
using namespace std;

namespace ncnn {

ReLU::ReLU() {
    one_blob_only = true;
    support_inplace = true;
}

int ReLU::load_param(const ParamDict& pd) {
    slope = pd.get(0, 0.f);
    return 0;
}

int ReLU::forward_inplace(Mat& bottom_top_blob, const Option& opt) const {
    cout << "RELU_FORWARD" << endl;

    return 0;
}
}
