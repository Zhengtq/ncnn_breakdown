#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "allocator.h"
#include "blob.h"
#include "datareader.h"
#include "iostream"
#include "layer.h"
#include "net.h"
using namespace std;

int main(int argc, char** argv) {
    cout << "buffer created" << endl;
    char* new_buff = (char*)fastMalloc(1000);

    cout << "buffer freed" << endl;
    fastFree(new_buff);

    printf("yes\n");
    return 0;
}
