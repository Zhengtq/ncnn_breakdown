#include "dropout.h"
#include "iostream"
using namespace std;
namespace ncnn {

Dropout::Dropout() { cout << "dropout constructed" << endl; }

int Dropout::load_param(const ParamDict& pd) {
    scale = pd.get(0, 1.f);
    return 0;
}


}
