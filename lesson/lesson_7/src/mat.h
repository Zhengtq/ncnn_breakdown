#ifndef NCNN_MAT_H
#define NCNN_MAT_H
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "allocator.h"
using namespace std;

namespace ncnn {

class Mat {
  public:
    Mat();
    ~Mat();
    Mat(int w, size_t elemsize = 4u, Allocator* allocator = 0);
    Mat(int w, int h, void* data, size_t elemsize, int elempack, Allocator* allocator = 0);
    bool empty() const;
    size_t total() const;

    void create(int w, size_t elemsize = 4u, Allocator* allocator = 0);
    void create(int w, size_t elemsize, int elempack, Allocator* allocator = 0);

    void create(int w, int h, size_t elemsize = 4u, Allocator* allocator = 0);
    void create(int w, int h, size_t elemsize, int elempack, Allocator* allocator = 0);

    void create(int w, int h, int c, size_t elemsize = 4u, Allocator* allocate = 0);
    void create(int w, int h, int c, size_t elemsize, int elempack, Allocator* allocator = 0);

    void release();

    Mat channel(int c);
    const Mat channel(int c) const;

    Mat clone(Allocator* allocator = 0) const;

    //定义重载类型转化符
    template <typename T>
    operator T*();
    template <typename T>
    operator const T*() const;


  public:
    void* data;
    int* refcount;
    size_t elemsize;
    int elempack;
    int dims;
    int w;
    int h;
    int c;
    size_t cstep;
    Allocator* allocator;
};

inline Mat::Mat()
    : data(0),
      refcount(0),
      elemsize(0),
      elempack(0),
      allocator(0),
      dims(0),
      w(0),
      h(0),
      c(0),
      cstep(0) {}

inline Mat::Mat(int _w, size_t _elemsize, Allocator* _allocator)
    : data(0), refcount(0), elemsize(0), elempack(0), dims(0), w(_w), h(0), c(0), cstep(0) {
    cout << "Mat has been created" << endl;
    create(_w, _elemsize, _allocator);
}

inline Mat::Mat(int _w, int _h, void* _data, size_t _elemsize, int _elempack,
                Allocator* _allocator)
    : data(_data),
      refcount(0),
      elemsize(_elemsize),
      elempack(_elempack),
      allocator(_allocator),
      dims(2),
      w(_w),
      h(_h),
      c(1) {
    cstep = (size_t)w * h;
}

inline Mat::~Mat() {
    cout << "Mat hea been destroyed" << endl;
    release(); }

inline void Mat::create(int _w, size_t _elemsize, Allocator* _allocator) {
    //如果是初始化Mat那么这个判断不会起到作用，肯定会到下面的函数体的
    if (dims == 1 && w == _w && elemsize == _elemsize && elempack == 1 && allocator == _allocator)
        return;

    release();
    elemsize = _elemsize;
    elempack = 1;
    allocator = _allocator;

    dims = 1;
    w = _w;
    h = 1;
    c = 1;
    cstep = w;

    if (total() > 0) {
        size_t totalsize = alignSize(total() * elemsize, 4);
        data = fastMalloc(totalsize + (int)sizeof(*refcount));
        //把refcount的地址放到了data的最后一位，同时赋值为1
        refcount = (int*)(((unsigned char*)data) + totalsize);
        *refcount = 1;
    }
}

inline void Mat::create(int _w, size_t _elemsize, int _elempack, Allocator* _allocator) {
    //如果是初始化Mat那么这个判断不会起到作用，肯定会到下面的函数体的
    if (dims == 1 && w == _w && elemsize == _elemsize && elempack == _elempack &&
        allocator == _allocator)
        return;

    release();
    elemsize = _elemsize;
    elempack = _elempack;
    allocator = _allocator;

    dims = 1;
    w = _w;
    h = 1;
    c = 1;
    cstep = w;

    if (total() > 0) {
        size_t totalsize = alignSize(total() * elemsize, 4);
        data = fastMalloc(totalsize + (int)sizeof(*refcount));
        //把refcount的地址放到了data的最后一位，同时赋值为1
        refcount = (int*)(((unsigned char*)data) + totalsize);
        *refcount = 1;
    }
}

inline void Mat::create(int _w, int _h, size_t _elemsize, Allocator* _allocator) {
    //如果是初始化Mat那么这个判断不会起到作用，肯定会到下面的函数体的
    if (dims == 3 && w == _w && h == _h && elemsize == _elemsize && elempack == 1 &&
        allocator == _allocator)
        return;

    release();
    elemsize = _elemsize;
    elempack = 1;
    allocator = _allocator;

    dims = 2;
    w = _w;
    h = _h;
    c = 1;
    cstep = (size_t)w * h;
    if (total() > 0) {
        size_t totalsize = alignSize(total() * elemsize, 4);
        data = fastMalloc(totalsize + (int)sizeof(*refcount));
        //把refcount的地址放到了data的最后一位，同时赋值为1
        refcount = (int*)(((unsigned char*)data) + totalsize);
        *refcount = 1;
    }
}

inline void Mat::create(int _w, int _h, size_t _elemsize, int _elempack, Allocator* _allocator) {
    //如果是初始化Mat那么这个判断不会起到作用，肯定会到下面的函数体的
    if (dims == 3 && w == _w && h == _h && elemsize == _elemsize && elempack == _elempack &&
        elempack == 1 && allocator == _allocator)
        return;

    release();
    elemsize = _elemsize;
    elempack = _elempack;
    allocator = _allocator;

    dims = 2;
    w = _w;
    h = _h;
    c = 1;
    cstep = (size_t)w * h;
    if (total() > 0) {
        // alignSize是尺寸上的对齐，fastMalloc是首地址方面的对齐
        size_t totalsize = alignSize(total() * elemsize, 4);
        data = fastMalloc(totalsize + (int)sizeof(*refcount));
        //把refcount的地址放到了data的最后一位，同时赋值为1
        refcount = (int*)(((unsigned char*)data) + totalsize);
        *refcount = 1;
    }
}

inline void Mat::create(int _w, int _h, int _c, size_t _elemsize, Allocator* _allocator) {
    //如果是初始化Mat那么这个判断不会起到作用，肯定会到下面的函数体的
    if (dims == 3 && w == _w && h == _h && c == _c && elemsize == _elemsize && elempack == 1 &&
        allocator == _allocator)
        return;

    release();
    elemsize = _elemsize;
    elempack = 1;
    allocator = _allocator;

    dims = 3;
    w = _w;
    h = _h;
    c = _c;
    cstep = alignSize((size_t)w * h * elemsize, 16) / elemsize;

    if (total() > 0) {
        size_t totalsize = alignSize(total() * elemsize, 4);
        data = fastMalloc(totalsize + (int)sizeof(*refcount));
        refcount = (int*)(((unsigned char*)data) + totalsize);
        *refcount = 1;
    }
}

inline void Mat::create(int _w, int _h, int _c, size_t _elemsize, int _elempack,
                        Allocator* _allocator) {
    //如果是初始化Mat那么这个判断不会起到作用，肯定会到下面的函数体的
    if (dims == 3 && w == _w && h == _h && c == _c && elemsize == _elemsize &&
        elempack == _elempack && allocator == _allocator)
        return;

    release();
    elemsize = _elemsize;
    elempack = _elempack;
    allocator = _allocator;

    dims = 3;
    w = _w;
    h = _h;
    c = _c;
    cstep = alignSize((size_t)w * h * elemsize, 16) / elemsize;

    if (total() > 0) {
        size_t totalsize = alignSize(total() * elemsize, 4);
        data = fastMalloc(totalsize + (int)sizeof(*refcount));
        refcount = (int*)(((unsigned char*)data) + totalsize);
        *refcount = 1;
    }
}

inline Mat Mat::clone(Allocator* allocator) const {
    if (empty()) return Mat();

    Mat m;
    if (dims == 1)
        m.create(w, elemsize, elempack, allocator);
    else if (dims == 2)
        m.create(w, h, elemsize, elempack, allocator);
    else if (dims == 3)
        m.create(w, h, c, elemsize, elempack, allocator);

    if (total() > 0) memcpy(m.data, data, total() * elemsize);

    return m;
}






inline bool Mat::empty() const { return data == 0 || total() == 0; }
inline size_t Mat::total() const { return cstep * c; }

inline void Mat::release() {
    if (refcount && NCNN_XADD(refcount, -1) == 1) {
        if (allocator)
            allocator->fastFree(data);
        else
            fastFree(data);
    }

    data = 0;
    elemsize = 0;
    elempack = 0;
    dims = 0;
    w = 0;
    h = 0;
    c = 0;
    cstep = 0;
    refcount = 0;
}

inline Mat Mat::channel(int _c) {
    return Mat(w, h, (unsigned char*)data + cstep * _c * elemsize, elemsize, elempack, allocator);
}

inline const Mat Mat::channel(int _c) const {
    return Mat(w, h, (unsigned char*)data + cstep * _c * elemsize, elemsize, elempack, allocator);
}
template <typename T>
inline Mat::operator T*() {
    return (T*)data;
}

template <typename T>
inline Mat::operator const T*() const {
    return (const T*)data;
}
}
#endif
