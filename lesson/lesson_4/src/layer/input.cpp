#include "input.h"
#include <iostream>
using namespace std;

namespace ncnn {

Input::Input() {
}

int Input::load_param(const ParamDict& pd) {
    w = pd.get(0, 0);
    h = pd.get(1, 0);
    c = pd.get(2, 0);
    return 0;
}


}
