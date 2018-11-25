cmake_minimum_required(VERSION 3.12)
project(ImageClassCuda_LZMP)

set(CMAKE_CXX_STANDARD 14)

include_directories(cuda/alg_cuda/inc)

add_executable(ImageClassCuda_LZMP
        cuda/alg_cuda/inc/cat_list.h
        cuda/alg_cuda/inc/command_line.h
        cuda/alg_cuda/inc/definitions.h
        cuda/alg_cuda/inc/dist.h
        cuda/alg_cuda/inc/entropy.h
        cuda/alg_cuda/inc/ffiles.hpp
        cuda/alg_cuda/inc/gpu_dict.h
        cuda/alg_cuda/inc/img_types.h
        cuda/alg_cuda/inc/main.h
        cuda/alg_cuda/inc/make_path.h
        cuda/alg_cuda/inc/my_timer.h
        cuda/alg_cuda/inc/ocv_functions.h
        cuda/alg_cuda/inc/write_cases_to_file.h
        cuda/alg_cuda/inc/write_distance_mat_to_file.h
        cuda/alg_cuda/scr/cat_list.cpp
        cuda/alg_cuda/scr/command_line.cpp
        cuda/alg_cuda/scr/entropy.cpp
        cuda/alg_cuda/scr/ffiles.cpp
        cuda/alg_cuda/scr/main.cpp
        cuda/alg_cuda/scr/make_path.cpp
        cuda/alg_cuda/scr/ocv_functions.cpp
        cuda/alg_cuda/scr/write_cases_to_file.cpp
        cuda/alg_cuda/scr/write_distance_mat_to_file.cpp)
