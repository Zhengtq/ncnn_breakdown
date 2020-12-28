#ifndef NCNN_OPTION_H
#define NCNN_OPTION_H
#include "allocator.h"

namespace ncnn {

class Option {
  public:
    Option();

  public:
    bool lightmode;
    Allocator* blob_allocator;
};
}

#endif
