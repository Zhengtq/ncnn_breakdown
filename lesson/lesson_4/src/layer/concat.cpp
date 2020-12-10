#include "concat.h"
#include <iostream>
using namespace std;

namespace ncnn {

Concat::Concat() {
}

int Concat::load_param(const ParamDict& pd) {
    axis = pd.get(0, 0);
    return 0;
}




}
