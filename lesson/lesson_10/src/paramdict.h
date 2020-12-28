#ifndef NCNN_PARAMDICT_H
#define NCNN_PARAMDICT_H
#define NCNN_MAX_PARAM_COUNT 32
#include "mat.h"

namespace ncnn {

class DataReader;
class Net;

class ParamDict {
  public:
    ParamDict();
    int get(int id, int def) const;
    float get(int id, float def) const;
    Mat get(int id, const Mat& def) const;

  protected:
    friend class Net;
    int load_param(const DataReader& dr);
    void clear();

  protected:
    struct {
        int type;
        union {
            int i;
            float f;
        };
        Mat v;
    } params[NCNN_MAX_PARAM_COUNT];
};
}

#endif
