include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(ncnn_SRCS
    datareader.cpp
    net.cpp
    layer.cpp
    blob.cpp
    paramdict.cpp
    modelbin.cpp
    mat_pixel.cpp
    option.cpp
    )


file(GLOB SRC_LAYER ${CMAKE_CURRENT_SOURCE_DIR}/layer/*.c*)
list(APPEND ncnn_SRCS ${SRC_LAYER})

set(LIBRARY_OUTPUT_PATH ${ncnn_lession1_BINARY_DIR/src_lib/})
add_library(ncnn_lession1 STATIC ${ncnn_SRCS})


