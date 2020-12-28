#include "net.h"
#include <string.h>
#include <iostream>
#include "modelbin.h"
#include "paramdict.h"

using namespace std;

namespace ncnn {

Net::Net() {  }

Net::~Net() {}

int Net::load_param(const DataReader& dr) {
#define SCAN_VALUE(fmt, v) dr.scan(fmt, &v);

    int magic = 0;
    SCAN_VALUE("%d", magic)

    int layer_count = 0;
    int blob_count = 0;

    SCAN_VALUE("%d", layer_count)
    SCAN_VALUE("%d", blob_count)

    layers.resize((size_t)layer_count);
    blobs.resize((size_t)blob_count);

    ParamDict pd;
    int blob_index = 0;
    for (int i = 0; i < layer_count; i++) {
        char layer_type[256];
        char layer_name[256];
        int bottom_count = 0;
        int top_count = 0;

        SCAN_VALUE("%255s", layer_type)
        SCAN_VALUE("%255s", layer_name)
        SCAN_VALUE("%d", bottom_count)
        SCAN_VALUE("%d", top_count)

        Layer* layer = create_layer(layer_type);
        //  Layer* layer = new Layer();

        layer->type = string(layer_type);
        layer->name = string(layer_name);
        layer->bottoms.resize(bottom_count);
        layer->tops.resize(top_count);

        for (int j = 0; j < bottom_count; j++) {
            char bottom_name[256];
            SCAN_VALUE("%255s", bottom_name)
            int bottom_blob_index =
                find_blob_index_by_name(bottom_name);  //找到blob的唯一id(在top中被指定的)
            Blob& blob = blobs[bottom_blob_index];
            blob.consumers.push_back(i);            //使用(消费)blob的时候的层的id
            layer->bottoms[j] = bottom_blob_index;  // layer获取bottom_blob的blob_id
        }

        for (int j = 0; j < top_count; j++) {
            Blob& blob =
                blobs[blob_index];  // blob在top时候时候才是被产生的时候，获取这时候的blob_id
            char blob_name[256];
            SCAN_VALUE("%255s", blob_name)
            blob.name = string(blob_name);
            blob.producer = i;            //产生blob时候的层的id
            layer->tops[j] = blob_index;  // Layer 获取top_blob的blob_id
            blob_index++;
        }


        //利用pd，load每一层的配置参数(非weight)
        int pdlr = pd.load_param(dr);
        int lr = layer->load_param(pd);
        layers[i] = layer;
    }

#undef SCAN_VALUE

    return 0;
}

int Net::load_param(const char* protopath) {
    FILE* fp = fopen(protopath, "rb");
    DataReaderFromStdio dr(fp);
    int ret = load_param(dr);
    fclose(fp);
    return ret;
}

int Net::load_model(const DataReader& dr) {
    int ret = 0;
    ModelBinFromDataReader mb(dr);

    for (size_t i = 0; i < layers.size(); i++) {
        Layer* layer = layers[i];
        int lret = layer->load_model(mb);
    }

    return ret;
}

int Net::load_model(const char* modelpath) {
    FILE* fp = fopen(modelpath, "rb");
    DataReaderFromStdio dr(fp);
    int ret = load_model(dr);
    fclose(fp);
    return ret;
}

int Net::find_blob_index_by_name(const char* name) const {
    for (size_t i = 0; i < blobs.size(); i++) {
        const Blob& blob = blobs[i];
        if (blob.name == name) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int Net::forward_layer(int layer_index, std::vector<Mat>& blob_mats, const Option& opt) const {
    const Layer* layer = layers[layer_index];

    if (layer->one_blob_only) {
        //由于是one_blob_only,所有只会取第一个值
        int bottom_blob_index = layer->bottoms[0];
        int top_blob_index = layer->tops[0];

        if (blob_mats[bottom_blob_index].dims == 0) {
            int ret = forward_layer(blobs[bottom_blob_index].producer, blob_mats, opt);
            if (ret != 0) return ret;
        }
        //这个时候经过了递归之后bottom_blob肯定是有值的
        //第一个bottom_blob.dims不为0的层其实是input层的下一层
        Mat bottom_blob = blob_mats[bottom_blob_index];
        Mat top_blob;
        int ret = layer->forward(bottom_blob, top_blob, opt);
        if (ret != 0) return ret;
        blob_mats[top_blob_index] = top_blob;
    } else {
        std::vector<Mat> bottom_blobs(layer->bottoms.size());

        for (size_t i = 0; i < layer->bottoms.size(); i++) {
            int bottom_blob_index = layer->bottoms[i];
            if (blob_mats[bottom_blob_index].dims == 0) {
                int ret = forward_layer(blobs[bottom_blob_index].producer, blob_mats, opt);
                if (ret != 0) return ret;
            }
            bottom_blobs[i] = blob_mats[bottom_blob_index];
        }

        std::vector<Mat> top_blobs(layer->tops.size());
        //调用对应Layer子类的forward函数
        int ret = layer->forward(bottom_blobs, top_blobs, opt);
        if (ret != 0) return ret;
        for (size_t i = 0; i < layer->tops.size(); i++) {
            int top_blob_index = layer->tops[i];
            blob_mats[top_blob_index] = top_blobs[i];
        }
    }
    return 0;
}

Extractor Net::create_extractor() const { return Extractor(this, blobs.size()); }

Extractor::Extractor(const Net* _net, size_t blob_count) : net(_net) {
    blob_mats.resize(blob_count);
    opt = net->opt;
}

Extractor::~Extractor() { blob_mats.clear(); }

int Extractor::input(const char* blob_name, const Mat& in) {
    int blob_index = net->find_blob_index_by_name(blob_name);
    if (blob_index == -1) return -1;

    return input(blob_index, in);
}

int Extractor::input(int blob_index, const Mat& in) {
    if (blob_index < 0 || blob_index >= (int)blob_mats.size()) return -1;
    blob_mats[blob_index] = in;
    return 0;
}

int Extractor::extract(const char* blob_name, Mat& feat) {
    int blob_index = net->find_blob_index_by_name(blob_name);
    if (blob_index == -1) return -1;

    return extract(blob_index, feat);
}

int Extractor::extract(int blob_index, Mat& feat) {
    if (blob_index < 0 || blob_index >= (int)blob_mats.size()) return -1;

    int ret = 0;
    if (blob_mats[blob_index].dims == 0) {
        int layer_index = net->blobs[blob_index].producer;
        ret = net->forward_layer(layer_index, blob_mats, opt);
    }

    feat = blob_mats[blob_index];

    return 10;
}
}
