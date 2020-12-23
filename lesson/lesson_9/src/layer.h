#ifndef NCNN_LAYER_H
#define NCNN_LAYER_H
#include <string>
#include <vector>
#include "allocator.h"
#include "modelbin.h"
#include "paramdict.h"
#include "mat.h"

namespace ncnn {

class Layer {
  public:
    Layer();
    virtual ~Layer();
    virtual int load_param(const ParamDict& pd);
    virtual int load_model(const ModelBin& mb);

  public:
    int typeindex;
    std::string type;
    std::string name;
    std::vector<int> bottoms;
    std::vector<int> tops;

};

typedef Layer* (*layer_creator_func)();

struct layer_registry_entry {
    const char* name;
    layer_creator_func creator;
};

int layer_to_index(const char* type);
Layer* create_layer(const char* type);
Layer* create_layer(int index);

#define DEFINE_LAYER_CREATOR(name) \
    ncnn::Layer* name##_final_layer_creator() { return new name; }
}

#endif
