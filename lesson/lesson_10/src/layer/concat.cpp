#include "concat.h"
#include <iostream>
using namespace std;

namespace ncnn {

Concat::Concat() {
    one_blob_only = false;
    support_inplace = false;
}

int Concat::load_param(const ParamDict& pd) {
    axis = pd.get(0, 0);
    return 0;
}

int Concat::forward(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs,
                    const Option&) const {
    cout << "CONCAT_FOREARD" << endl;
    const Mat& bottom_blob = bottom_blobs[0];

    for (size_t i = 0; i < top_blobs.size(); i++) {
        top_blobs[i] = bottom_blob;
    }
    return 0;
}





}
