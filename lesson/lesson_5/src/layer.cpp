#include "layer.h"
#include <string.h>
#include <iostream>
#include "layer_declaration.h"
using namespace std;

namespace ncnn {

Layer::Layer() { }
Layer::~Layer() {}

int Layer::load_param(const ParamDict&) { return 0; }

static const layer_registry_entry layer_registry[] = {
    {"ReLU", ReLU_final_layer_creator},
    {"Input", Input_final_layer_creator},
    {"Pooling", Pooling_final_layer_creator},
    {"Convolution", Convolution_final_layer_creator},
    {"Split", Split_final_layer_creator},
    {"Concat", Concat_final_layer_creator},
    {"Dropout", Dropout_final_layer_creator},
    {"Softmax", Softmax_final_layer_creator},

};

//确定一共有多少个layer
static const int layer_registry_entry_count =
   sizeof(layer_registry) / sizeof(layer_registry_entry);

int layer_to_index(const char* type) {
    for (int i = 0; i < layer_registry_entry_count; i++) {
        if (strcmp(type, layer_registry[i].name) == 0) return i;
    }
    return -1;
}

Layer* create_layer(const char* type) {
    int index = layer_to_index(type);
    if (index == -1) return 0;
    return create_layer(index);
}

//基于id在数组里面找constructor
Layer* create_layer(int index) {
    if (index < 0 || index >= layer_registry_entry_count) return 0;

    layer_creator_func layer_creator = 0;
    { layer_creator = layer_registry[index].creator; }

    if (!layer_creator) return 0;

    Layer* layer = layer_creator();
    layer->typeindex = index;
    return layer;
}
}
