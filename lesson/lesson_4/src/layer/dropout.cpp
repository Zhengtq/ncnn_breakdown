#include "dropout.h"

namespace ncnn {

Dropout::Dropout() {
}

int Dropout::load_param(const ParamDict& pd) {
    scale = pd.get(0, 1.f);
    return 0;
}


}
