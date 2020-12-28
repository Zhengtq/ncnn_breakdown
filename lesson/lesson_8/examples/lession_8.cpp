#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "allocator.h"
#include "blob.h"
#include "datareader.h"
#include "iostream"
#include "layer.h"
#include "mat.h"
#include "net.h"
using namespace std;

int main(int argc, char** argv) {
    ncnn::Net squeezenet;
    squeezenet.load_param("../examples/squeezenet_v1.1.param");
    squeezenet.load_model("../examples/squeezenet_v1.1.bin");

    printf("yes\n");
    return 0;
}
