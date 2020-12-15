#include "net.h"
#include <string.h>
#include <iostream>
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

int Net::find_blob_index_by_name(const char* name) const {
    for (size_t i = 0; i < blobs.size(); i++) {
        const Blob& blob = blobs[i];
        if (blob.name == name) {
            return static_cast<int>(i);
        }
    }

    return -1;
}
}
