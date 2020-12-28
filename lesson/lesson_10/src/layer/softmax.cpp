#include "softmax.h"

namespace ncnn {

Softmax::Softmax() {
    one_blob_only = true;
    support_inplace = true;
}

int Softmax::load_param(const ParamDict& pd) {
    axis = pd.get(0, 9);
    return 0;
}

int Softmax::forward_inplace(Mat& bottom_top_blob, const Option& opt) const {
    
    cout << "SOFTMAX_FORWARD" << endl;
    return 0;
}
}
