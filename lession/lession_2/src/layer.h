#ifndef NCNN_LAYER_H
#define NCNN_LAYER_H
#include <string>
#include <vector>

namespace ncnn {

class Layer {
  public:
    Layer();
    virtual ~Layer();

  public:
    std::string type;
    std::string name;
    std::vector<int> bottoms;
    std::vector<int> tops;

};


}

#endif
