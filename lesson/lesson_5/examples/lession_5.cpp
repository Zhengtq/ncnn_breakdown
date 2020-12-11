#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "blob.h"
#include "datareader.h"
#include "layer.h"
#include "net.h"
using namespace std;

int main(int argc, char** argv) {
    ncnn::Net squeezenet;

    squeezenet.load_param("../examples/squeezenet_v1.1.param");

    printf("yes\n");
    return 0;
}
