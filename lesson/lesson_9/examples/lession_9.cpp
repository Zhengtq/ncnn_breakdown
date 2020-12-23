#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
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

    const char* imagepath = "../examples/320x320.bmp";
    cv::Mat bgr = cv::imread(imagepath, 1);
    ncnn::Mat in = ncnn::Mat::from_pixels(bgr.data, ncnn::Mat::PIXEL_BGR, bgr.cols, bgr.rows);

    printf("yes\n");
    return 0;
}
