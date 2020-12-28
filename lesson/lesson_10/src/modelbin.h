#ifndef NCNN_MODELBIN_H
#define NCNN_MODELBIN_H

#include "mat.h"

namespace ncnn {

class DataReader;
class ModelBin {
  public:
    virtual ~ModelBin();
    virtual Mat load(int w, int type) const = 0;
};

class ModelBinFromDataReader : public ModelBin {
  public:
    ModelBinFromDataReader(const DataReader& dr);
    virtual Mat load(int w, int type) const;

  protected:
    const DataReader& dr;
};

}

#endif
