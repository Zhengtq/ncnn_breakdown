include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(ncnn_SRCS
    datareader.cpp
    net.cpp
    layer.cpp
    blob.cpp
    paramdict.cpp
    )

set(LIBRARY_OUTPUT_PATH ${ncnn_lession1_BINARY_DIR/src_lib/})
add_library(ncnn_lession1 STATIC ${ncnn_SRCS})


