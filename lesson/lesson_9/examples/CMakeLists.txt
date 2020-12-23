macro(ncnn_add_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE ncnn_lession1 ${OpenCV_LIBS})
    set_property(TARGET ${name} PROPERTY FOLDER "examples")
endmacro()

find_package(OpenCV QUIET COMPONENTS opencv_world)
if("${OpenCV_LIBS}" STREQUAL "")
    set(OpenCV_FOUND FALSE)
endif()

if(NOT OpenCV_FOUND)
    find_package(OpenCV QUIET COMPONENTS core highgui imgproc imgcodecs videoio)
endif()


if(NOT OpenCV_FOUND)
    find_package(OpenCV QUIET COMPONENTS core highgui imgproc)
endif()





include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
ncnn_add_example(lession_9)



