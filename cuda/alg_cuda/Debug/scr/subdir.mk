################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../scr/cat_list.cpp \
../scr/command_line.cpp \
../scr/entropy.cpp \
../scr/ffiles.cpp \
../scr/main.cpp \
../scr/make_path.cpp \
../scr/ocv_functions.cpp \
../scr/write_cases_to_file.cpp \
../scr/write_distance_mat_to_file.cpp 

CU_SRCS += \
../scr/dist.cu \
../scr/gpu_dict.cu \
../scr/my_timer.cu 

CU_DEPS += \
./scr/dist.d \
./scr/gpu_dict.d \
./scr/my_timer.d 

OBJS += \
./scr/cat_list.o \
./scr/command_line.o \
./scr/dist.o \
./scr/entropy.o \
./scr/ffiles.o \
./scr/gpu_dict.o \
./scr/main.o \
./scr/make_path.o \
./scr/my_timer.o \
./scr/ocv_functions.o \
./scr/write_cases_to_file.o \
./scr/write_distance_mat_to_file.o 

CPP_DEPS += \
./scr/cat_list.d \
./scr/command_line.d \
./scr/entropy.d \
./scr/ffiles.d \
./scr/main.d \
./scr/make_path.d \
./scr/ocv_functions.d \
./scr/write_cases_to_file.d \
./scr/write_distance_mat_to_file.d 


# Each subdirectory must supply rules for building sources it contributes
scr/%.o: ../scr/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I/usr/include/opencv -I/usr/local/cuda/samples/common/inc -I"/home/alex/cuda-workspace/ImageClassCuda_LZMP/cuda/alg_cuda/inc" -G -g -O0 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_35,code=sm_35  -odir "scr" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I/usr/include/opencv -I/usr/local/cuda/samples/common/inc -I"/home/alex/cuda-workspace/ImageClassCuda_LZMP/cuda/alg_cuda/inc" -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

scr/%.o: ../scr/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I/usr/include/opencv -I/usr/local/cuda/samples/common/inc -I"/home/alex/cuda-workspace/ImageClassCuda_LZMP/cuda/alg_cuda/inc" -G -g -O0 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_35,code=sm_35  -odir "scr" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I/usr/include/opencv -I/usr/local/cuda/samples/common/inc -I"/home/alex/cuda-workspace/ImageClassCuda_LZMP/cuda/alg_cuda/inc" -G -g -O0 --compile --relocatable-device-code=true -gencode arch=compute_20,code=compute_20 -gencode arch=compute_35,code=compute_35 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_35,code=sm_35  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


