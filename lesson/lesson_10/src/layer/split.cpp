#include "split.h"

namespace ncnn {

Split::Split() {
    one_blob_only = false;
    support_inplace = false;
}

int Split::forward(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs,
                   const Option&) const {
    cout << "SPLIT_FORWARD" << endl;
    const Mat& bottom_blob = bottom_blobs[0];
    for (size_t i = 0; i < top_blobs.size(); i++) {
        top_blobs[i] = bottom_blob;
    }
    return 0;
}







}

