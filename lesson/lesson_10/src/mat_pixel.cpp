#include "mat.h"

namespace ncnn {
static int from_rgb(const unsigned char* rgb, int w, int h, int stride, Mat& m,
                    Allocator* allocator) {
    m.create(w, h, 3, 4u, allocator);
    if (m.empty()) return -100;

    const int wgap = stride - w * 3;
    if (wgap == 0) {
        w = w * h;
        h = 1;
    }

    float* ptr0 = m.channel(0);
    float* ptr1 = m.channel(1);
    float* ptr2 = m.channel(2);

    for (int y = 0; y < h; y++) {
        int remain = w;
        for (; remain > 0; remain--) {
            *ptr0 = rgb[0];
            *ptr1 = rgb[1];
            *ptr2 = rgb[2];
            rgb += 3;
            ptr0++;
            ptr1++;
            ptr2++;
        }
        rgb += wgap;
    }

    cout << "success" << endl;
    return 0;
}

Mat Mat::from_pixels(const unsigned char* pixels, int type, int w, int h, Allocator* allocator) {
    if (type == PIXEL_RGB || type == PIXEL_BGR) {
        return Mat::from_pixels(pixels, type, w, h, w * 3, allocator);
    }
    return Mat();
}

Mat Mat::from_pixels(const unsigned char* pixels, int type, int w, int h, int stride,
                     Allocator* allocator) {
    Mat m;
    if (type == PIXEL_RGB || PIXEL_RGB) from_rgb(pixels, w, h, stride, m, allocator);
    return m;
}
}
