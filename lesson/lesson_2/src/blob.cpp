#include "blob.h"
#include <iostream>
using namespace std;
namespace ncnn {

Blob::Blob() {
    cout << "Blob has been constructed" << endl;
    producer = -1; }
}
