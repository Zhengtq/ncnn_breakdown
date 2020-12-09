macro(ncnn_add_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE ncnn_lession1 ${OpenCV_LIBS})
    set_property(TARGET ${name} PROPERTY FOLDER "examples")
endmacro()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
ncnn_add_example(lession_2)



