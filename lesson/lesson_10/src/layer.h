#ifndef NCNN_LAYER_H
#define NCNN_LAYER_H
#include <string>
#include <vector>
#include "allocator.h"
#include "modelbin.h"
#include "paramdict.h"
#include "mat.h"
#include "option.h" 

namespace ncnn {

class Layer {
  public:
    Layer();
    virtual ~Layer();
    virtual int load_param(const ParamDict& pd);
    virtual int load_model(const ModelBin& mb);

  public:
    bool one_blob_only;
    bool support_inplace;

    int typeindex;
    std::string type;
    std::string name;
    std::vector<int> bottoms;
    std::vector<int> tops;

    virtual int forward(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs,
                        const Option& opt) const;
    virtual int forward(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const;

    virtual int forward_inplace(std::vector<Mat>& bottom_top_blobs, const Option& opt) const;
    virtual int forward_inplace(Mat& bottom_top_blob, const Option& opt) const;
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
