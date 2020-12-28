#ifndef NCNN_ALLOCATOR_H
#define NCNN_ALLOCATOR_H

#include <stdlib.h>

namespace ncnn {

#define MALLOC_ALIGN 16

//相当于ptr首先向后移动n-1的位置，然后用-n进行最高位直接截断对其
template <typename _Tp>
static inline _Tp* alignPtr(_Tp* ptr, int n = (int)sizeof(_Tp)) {
    return (_Tp*)(((size_t)ptr + n - 1) & -n);
}

static inline size_t alignSize(size_t sz, int n) { return (sz + n - 1) & -n; }


static inline void* fastMalloc(size_t size) {
//符合POSIX标准的c源码
#if (defined(__unix__)) && _POSIX_C_SOURCE >= 200112L
    void* ptr = 0;
    if (posix_memalign(&ptr, MALLOC_ALIGN, size)) ptr = 0;
    return ptr;
#else
    //预留需要的空间，sizeof(void*)的目的是给udata的地址留下空间，MALLOC_ALIGN的目的是使得对齐后有size的空间
    unsigned char* udata = (unsigned char*)malloc(size + sizeof(void*) + MALLOC_ALIGN);
    if (!udata) return 0;
    //从udata+8开始，其中8是udata地址的位置，
    unsigned char** adata = alignPtr((unsigned char**)udata + 1, MALLOC_ALIGN);
    adata[-1] = udata;
    return adata;
#endif
}

static inline int NCNN_XADD(int* addr, int delta) {
    int tmp = *addr;
    *addr += delta;
    return tmp;
}

static inline void fastFree(void* ptr) {
    if (ptr) {
#if _MSC_VER
        _aligned_free(ptr);
#elif (defined(__unix__) || defined(__APPLE__)) && _POSIX_C_SOURCE >= 200112L || \
    (__ANDROID__ && __ANDROID_API__ >= 17)
        free(ptr);
#elif __ANDROID__ && __ANDROID_API__ < 17
        free(ptr);
#else
        unsigned char* udata = ((unsigned char**)ptr)[-1];
        free(udata);
#endif
    }
}

class Allocator {
  public:
    virtual void* fastMalloc(size_t size) = 0;
    virtual void* fastFree(void* ptr) = 0;
};
}
#endif
