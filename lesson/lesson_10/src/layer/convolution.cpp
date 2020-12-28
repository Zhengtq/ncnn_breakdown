#include "convolution.h"
#include <iostream>
using namespace std;

namespace ncnn {

Convolution::Convolution() {
    one_blob_only = true;
    support_inplace = false;
}

int Convolution::load_param(const ParamDict& pd) {
    num_output = pd.get(0, 0);
    kernel_w = pd.get(1, 0);
    kernel_h = pd.get(11, kernel_w);
    dilation_w = pd.get(2, 1);
    dilation_h = pd.get(12, dilation_w);
    stride_w = pd.get(3, 1);
    stride_h = pd.get(13, stride_w);
    pad_left = pd.get(4, 0);
    pad_right = pd.get(15, pad_left);
    pad_top = pd.get(14, pad_left);
    pad_bottom = pd.get(16, pad_top);
    pad_value = pd.get(18, 0.f);
    bias_term = pd.get(5, 0);
    weight_data_size = pd.get(6, 0);
    int8_scale_term = pd.get(8, 0);
    activation_params = pd.get(10, Mat());
    impl_type = pd.get(17, 0);


    return 0;
}

int Convolution::load_model(const ModelBin& mb) {
    weight_data = mb.load(weight_data_size, 0);
    if (weight_data.empty()) return -100;

    if (bias_term) {
        bias_data = mb.load(num_output, 1);
        if (bias_data.empty()) return -100;
    }
    return 0;
}

int Convolution::forward(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const {
    cout << "CONV FORWARD" << endl;
    top_blob = bottom_blob.clone(opt.blob_allocator);
    return 0;
}




}
