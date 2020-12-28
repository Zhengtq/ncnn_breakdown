#ifndef NCNN_NET_H
#define NCNN_NET_H
#include <stdlib.h>
#include <string>
#include <vector>
#include "blob.h"
#include "datareader.h"
#include "layer.h"

namespace ncnn{

class Extractor;
class Net {
  public:
    Net();
    ~Net();

    Option opt;
    int load_param(const DataReader& dr);
    int load_param(const char* protopath);

    int load_model(const DataReader& dr);
    int load_model(const char* modelpath);

    Extractor create_extractor() const;

  public:
    std::vector<Layer*> layers;
    std::vector<Blob> blobs;  //存放blob的信息,如layer或者shape等等

  protected:
    int find_blob_index_by_name(const char* name) const;
    friend class Extractor;
    int forward_layer(int layer_index, std::vector<Mat>& blob_mats, const Option& opt) const;
};

class Extractor {
  public:
    ~Extractor();

    int input(const char* blob_name, const Mat& in);
    int input(int blob_index, const Mat& in);

    int extract(const char* blob_name, Mat& feat);
    int extract(int blob_index, Mat& feat);

  protected:
    friend Extractor Net::create_extractor() const;
    Extractor(const Net* net, size_t blob_count);

  private:
    const Net* net;
    std::vector<Mat> blob_mats;  //存放blob的数值
    Option opt;
};
}
#endif
