#include "concat.h"
#include <iostream>
using namespace std;

namespace ncnn {

Concat::Concat() { cout << "concat constructed" << endl; }

int Concat::load_param(const ParamDict& pd) {
    axis = pd.get(0, 0);
    return 0;
}




}
