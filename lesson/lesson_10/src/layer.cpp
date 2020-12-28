#include "layer.h"
#include <string.h>
#include <iostream>
#include "layer_declaration.h"
using namespace std;

namespace ncnn {

Layer::Layer() {
    one_blob_only = false;
    support_inplace = false;
}
Layer::~Layer() {}

int Layer::load_param(const ParamDict&) { return 0; }
int Layer::load_model(const ModelBin&) { return 0; }

int Layer::forward(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs,
                   const Option& opt) const {
    if (!support_inplace) return -1;
    top_blobs = bottom_blobs;

    for (int i = 0; i < (int)top_blobs.size(); i++) {
        top_blobs[i] = bottom_blobs[i].clone(opt.blob_allocator);
        if (top_blobs[i].empty()) return -100;
    }

    return forward_inplace(top_blobs, opt);
}

int Layer::forward(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const {
    if (!support_inplace) return -1;

    top_blob = bottom_blob.clone(opt.blob_allocator);
    if (top_blob.empty()) return -100;

    return forward_inplace(top_blob, opt);
}

int Layer::forward_inplace(std::vector<Mat>&, const Option&) const { return -1; }

int Layer::forward_inplace(Mat&, const Option&) const { return -1; }

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
