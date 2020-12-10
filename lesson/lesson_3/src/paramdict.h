#ifndef NCNN_PARAMDICT_H
#define NCNN_PARAMDICT_H
#define NCNN_MAX_PARAM_COUNT 32

namespace ncnn {

class DataReader;

class ParamDict {
  public:
    ParamDict();

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
    } params[NCNN_MAX_PARAM_COUNT];
};
}

#endif
