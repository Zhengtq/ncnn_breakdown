#include <stdio.h>
#include <algorithm>
#include <vector>
#include "datareader.h"
#include <iostream>
using namespace std;

int test_dr_scan() {
    const char* file_path = "../examples/tmp.proto";
    FILE* fp = fopen(file_path, "rb");
    ncnn::DataReaderFromStdio dr(fp);

    int ret = 0;
    while(1)
    {
        char layer_type[256];
        ret = dr.scan("%s", &layer_type);
        if (ret == -1) break;
        int layer_id;
        ret = dr.scan("%d", &layer_id);
        if (ret == -1) break;
        cout << layer_type << "  " << layer_id << endl;
    }
    return 0;
}
int test_dr_read() {
    const char* file_path = "../examples/tmp.model";
    FILE* fp = fopen(file_path, "rb");
    ncnn::DataReaderFromStdio dr(fp);

    int ret = 0;
    while (1) {
        char* a = new char(4);
        ret = dr.read(a, sizeof(char) * 4);
        cout << a << endl;
        if (ret == 0) break;
    }
    return 0;
}
int main(int argc, char** argv) {
    //     test_dr_scan();
    test_dr_read();

    printf("yes\n");
    return 0;
}
