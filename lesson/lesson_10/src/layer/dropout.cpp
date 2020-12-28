#include "dropout.h"

namespace ncnn {

Dropout::Dropout() {
    one_blob_only = true;
    support_inplace = true;
}

int Dropout::load_param(const ParamDict& pd) {
    scale = pd.get(0, 1.f);
    return 0;
}

int Dropout::forward_inplace(Mat& bottom_top_blob, const Option& opt) const {
    cout << "DROPOUT_FORWARD" << endl;
    return 0;
}
}
