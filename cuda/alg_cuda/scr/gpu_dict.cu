/**
 ******************************************************************************
 * @file    gpu_dict.cu
 * @author  Alexander Belousov
 * @version V1.0.0
 * @date    09/24/2014
 * @brief   This file provides all the GPU kernels.
 ****************************************************************************** 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <helper_cuda.h>
#include <helper_functions.h> 
#include <img_types.h>
#include <gpu_dict.h>
#include <dist.h>


/**
 *@brief  GPU - kernel 
 *        Calculating LZ-complexity of a single member in a given array, 
 *        Each block works on a calculation of a single member in a given array.
 *        Carefully launch blocks, blocks = number of members in an array. 
 *@param  ptr: device pointer to images pure data array,
 *        This parameter can be a value of @ref img_data_t
 *@param  lzmp_value: device pointer where kernel will copy after calculation  
 *        LZ-complexity of each member in array 
 *@retval None
 */
__device__ void gpu_calc_single_LZMP(char *data, int size, int *lz_val) {
    // initialize Thread index within a block
    int threadId = threadIdx.x;
    __shared__ int m; // history length
    __shared__ int SM; // maximum steps
    int D = 0; // lz variable  (Dictionary)
    int p = MAX_THREADS_PER_BLOCK;
    int n = size;

    int i;
    int k;
    int h;
    int z;
    int j;
    int index;

    m = 0;
    while (m < n) {
        SM = 0;
        if (threadId >= 0 && threadId < p) {
            index = m / p;
            for (int l = 0; l < index + 1; l++) {
                // create new index that depend from threads
                j = threadId + (l * p);
                if (j < m) {
                    i = 0;
                    k = j;
                    h = m - j;
                    // Let each Thread scan and compare characters
                    // in history buffer with characters in S string
                    while (data[m + i] == data[k]) {
                        i++;
                        k++;
                        h--;
                        if (h == 0 || (m + i) == n) {
                            break;
                        }
                    }
                    // If history is over and S is not
                    if (h == 0 && ((m + i) < n)) {
                        z = m;
                        // Let each Thread continue to scan &
                        // compare characters in S string
                        while (data[z] == data[m + i]) {
                            i++;
                            z++;
                            if ((m + i) == n) {
                                break;
                            }
                        }
                    }
                    if (i > 0)
                        atomicMax(&SM, i);
                }
            }
        }
        __syncthreads();
        // Only first thread check and copy to history buffer
        if (threadId == 0) {
            m += SM + 1;
            D++;
        }
        __syncthreads();
    }
    if (threadId == 0)
        *lz_val = D;
}

/**
 *@brief  GPU - kernel 
 *        Calculating LZ-complexity of a single member in a given array, 
 *        Each block works on a calculation of a single member in a given array.
 *        Carefully launch blocks, blocks = number of members in an array. 
 *@param  ptr: device pointer to images pure data array,
 *        This parameter can be a value of @ref img_data_t
 *@param  lzmp_value: device pointer where kernel will copy after calculation  
 *        LZ-complexity of each member in array 
 *@retval None
 */
__global__ void gpu_lzmp_single(img_data_t *ptr, int *lzmp_value) {
    // initialize Thread index within a block
    int threadId = threadIdx.x;
    // each block work on specific string
    int member = blockIdx.x;
    int n = ptr[member].len;
    // initialize shared memory array, it much faster than global
    __shared__ char S[MAX_SEQUENCE_ARRAY_SIZE];

    if (threadId == 0) {
        assert(n < MAX_SEQUENCE_ARRAY_SIZE);
        // copy current string from global to shared memory
        memcpy(S, ptr[member].data, n);
    }
    __syncthreads();
    gpu_calc_single_LZMP(S, n, (int*) &lzmp_value[member]);
}

/**
 *@brief  GPU - kernel 
 *        Calculating Distance Matrix of sequence pair arrays,
 *        This kernel will calculate Distance Matrix of sequence pair arrays, 
 *        Each sequence pair calculated in one block.
 *@param  ptr: device pointer to images pure data array,
 *        This parameter can be a value of @ref img_data_t
 *@param  lzmp_value: device pointer to LZ-complexity of each member in array
 *@param  dist_mat: device pointer to Distance Matrix value
 *@param  d_members: device pointer to total members in array
 *@retval None
 */
__global__ void gpu_dist_mat(img_data_t *ptr, int *lzmp_value, float *dist_mat,
        int *d_members) {
    // initialize Thread index within a block
    int threadId = threadIdx.x;
    // each block work on specific string
    int i = blockIdx.x;
    int j = blockIdx.y;
    int n = ptr[i].len + ptr[j].len;
    int lzmp_seq;
    int width = *d_members;
    // initialize shared memory array, it much faster than global
    __shared__ char S[MAX_SEQUENCE_ARRAY_SIZE];

    if (threadId == 0) {
        assert(n < MAX_SEQUENCE_ARRAY_SIZE);
        // copy current string from global to shared memory
        memcpy(S, ptr[i].data, ptr[i].len);
        memcpy(&S[ptr[i].len], ptr[j].data, ptr[j].len);
    }
    __syncthreads();
    gpu_calc_single_LZMP(S, n, &lzmp_seq);
    if (threadId == 0) {
        int index = i + j * width;
        dist_mat[index] = dist_calc_val(lzmp_value[i], lzmp_value[j], lzmp_seq);
    }
}

/**
 *@brief  GPU - kernel 
 *        Calculating Distance Matrix of sequence pair arrays,
 *        This kernel will calculate Distance Matrix of sequence pair arrays, 
 *        Each sequence pair calculated in one block.
 *@param  ptr_row: device pointer to images pure data array per row,
 *        This parameter can be a value of @ref img_data_t
 *@param  lzmp_value_row: device pointer to LZ-complexity of each member in row array
 *@param  row: device pointer to total members in row array
 *@param  ptr_col: device pointer to images pure data array per columns,
 *        This parameter can be a value of @ref img_data_t
 *@param  lzmp_value_col: device pointer to LZ-complexity of each member in column array
 *@param  col: device pointer to total members in column array
 *@param  dist_mat: device pointer to Distance Matrix value
 *@retval None
 */
__global__ void gpu_dist_mat_two_arr(img_data_t *ptr_row, int *lzmp_value_row,
        int *row, img_data_t *ptr_col, int *lzmp_value_col, int *col,
        float* dist_mat) {
    // initialize Thread index within a block
    int threadId = threadIdx.x;
    // each block work on specific string
    int i = blockIdx.x;
    int j = blockIdx.y;
    int n = ptr_row[i].len + ptr_col[j].len;
    int lzmp_seq;
    int width = *col;
    // initialize shared memory array, it much faster than global
    __shared__ char S[MAX_SEQUENCE_ARRAY_SIZE];

    if (threadId == 0) {
        assert(n < MAX_SEQUENCE_ARRAY_SIZE);
        // copy current string from global to shared memory
        memcpy(S, ptr_row[i].data, ptr_row[i].len);
        memcpy(&S[ptr_row[i].len], ptr_col[j].data, ptr_col[j].len);
    }
    __syncthreads();
    gpu_calc_single_LZMP(S, n, &lzmp_seq);
    if (threadId == 0) {
        int index = j + i * width;
        dist_mat[index] = dist_calc_val(lzmp_value_row[i], lzmp_value_col[j], lzmp_seq);
    }
}


/**
 *@brief  Printing Distance Matrix from 1D array as 2D array (Mat).
 *@param  dist_mat: pointer to Distance Matrix 1D array
 *@param  row: split to total rows
 *@param  col: split to total columns
 *@retval None
 */
void gpu_print_dist_mat_1D_array_as_2D_array(float *dist_mat, int row, int col) {
    int index1D;
    printf("Distance Matrix\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            index1D = j + i * col;
            printf("%f ", dist_mat[index1D]);
        }
        printf("\n");
    }
}



/**
 *@brief  Extract images sorted linked list and copy pure data to array.
 *@param  img_list: pointer to linked list of images,
 *        This parameter can be a value of @ref img_struct_t
 *@param  img: pointer to array that data would be copied to,
 *        array should be already allocated,
 *        This parameter can be a value of @ref img_data_t
 *@param  total_img: total images in array
 *@retval None
 */
void gpu_extract_from_list(img_struct_t *img_list, img_data_t *img, int total_img) {
    img_struct_t *ptr_to_free = NULL;
    int currentImg;

    printf("Extracting images data from list - Start ");
    while (img_list != NULL) {
        currentImg = total_img - img_list->img_num - 1; // add to oposite
        assert(img_list->image_size < MAX_ARRAY_SIZE);
        memcpy(img[currentImg].data, img_list->img_data, img_list->image_size);
        img[currentImg].len = img_list->image_size;
        ptr_to_free = img_list;
        img_list = img_list->next;
        free(ptr_to_free);
        printf(".");
    }
    printf("\nExtracting images data from list - Complete\n");
}


/**
 *@brief  Calculating Distance Matrix from single array,
 *		  This function allocate memory on device (GPU)
 *		  Copy data from CPU to GPU and launch the kernels.
 *		  After calculation copy data back and deallocate device memory
 *@param  h_current: host pointer to images pure data array,
 *        This parameter can be a value of @ref img_data_t
 *@param  members: total members in array
 *@param  h_distMat: host pointer to Distance Matrix
 *@retval None
 */
void gpu_calc_dist_mat(img_data_t *h_current, int members, float *h_distMat) {
    img_data_t *d_current;
    int *d_plz_value;
    int *d_members;
    float *d_distMat;

    // Allocate memory on  Device
    checkCudaErrors(cudaMalloc((void**) &d_current, members * sizeof (img_data_t) * sizeof (char)));
    checkCudaErrors(cudaMalloc((void**) &d_plz_value, members * sizeof (int)));
    checkCudaErrors(cudaMalloc((void**) &d_members, sizeof (int)));
    checkCudaErrors(cudaMalloc((void**) &d_distMat, members * members * sizeof (float)));
    // Copy data strings from Host memory to Device memory
    checkCudaErrors(cudaMemcpy(d_current, h_current, members * sizeof (img_data_t) * sizeof (char),
            cudaMemcpyHostToDevice));
    checkCudaErrors(cudaMemcpy(d_members, &members, sizeof (int),
            cudaMemcpyHostToDevice));
    int dimGrid = members;
    int dimBlock = MAX_THREADS_PER_BLOCK;
    // launch kernel
    gpu_lzmp_single << <dimGrid, dimBlock>>>(d_current, d_plz_value);

    dim3 dimGridSeq(members, members);
    gpu_dist_mat << <dimGridSeq, dimBlock>>>(d_current, d_plz_value, d_distMat, d_members);
    //app_test_kernel<<<dimGrid, dimBlock>>>(d_current, d_plz_value, members);
    cudaDeviceSynchronize();
    // Copy result from Device memory to Host memory
    checkCudaErrors(cudaMemcpy(h_distMat, d_distMat, members * members * sizeof (float),
            cudaMemcpyDeviceToHost));
    // Free Device memory
    checkCudaErrors(cudaFree(d_current));
    checkCudaErrors(cudaFree(d_plz_value));
    checkCudaErrors(cudaFree(d_members));
    checkCudaErrors(cudaFree(d_distMat));
}

/**
 *@brief  Calculating Distance Matrix from sequence arrays,
 *		  This function allocate memory on device (GPU)
 *		  Copy data from CPU to GPU and launch the kernels.
 *		  After calculation copy data back and deallocate device memory
 *@param  h_vec_row: host pointer to images pure data array per row,
 *        This parameter can be a value of @ref img_data_t
 *@param  h_row: total members in row array
 *@param  h_vec_col: host pointer to images pure data array per columns,
 *        This parameter can be a value of @ref img_data_t
 *@param  h_col: total members in column array
 *@param  h_distMat: host pointer to Distance Matrix
 *@retval None
 */
void gpu_calc_dist_mat_from_two_arr(img_data_t *h_vec_row, int h_row, img_data_t *h_vec_col, int h_col, float *h_distMat) {
    img_data_t *d_vec_row;
    int *d_row;
    int *d_lzmp_val_row;
    img_data_t *d_vec_col;
    int *d_col;
    int *d_lzmp_val_col;
    float *d_distMat;

    StopWatchInterface *timer = NULL;
    float time_val = 0;
    int total_bytes;

    sdkCreateTimer(&timer);
    sdkResetTimer(&timer);
    sdkStartTimer(&timer);

    total_bytes = h_row * sizeof (img_data_t) * sizeof (char);
    total_bytes += sizeof (int);
    total_bytes += h_col * sizeof (img_data_t) * sizeof (char);
    total_bytes += sizeof (int);
    printf("Will copy %d bytes to device\n", total_bytes);

    // Allocate memory on  Device
    checkCudaErrors(cudaMalloc((void**) &d_vec_row, h_row * sizeof (img_data_t) * sizeof (char)));
    checkCudaErrors(cudaMalloc((void**) &d_lzmp_val_row, h_row * sizeof (int)));
    checkCudaErrors(cudaMalloc((void**) &d_row, sizeof (int)));

    checkCudaErrors(cudaMalloc((void**) &d_vec_col, h_col * sizeof (img_data_t) * sizeof (char)));
    checkCudaErrors(cudaMalloc((void**) &d_lzmp_val_col, h_col * sizeof (int)));
    checkCudaErrors(cudaMalloc((void**) &d_col, sizeof (int)));

    checkCudaErrors(cudaMalloc((void**) &d_distMat, h_row * h_col * sizeof (float)));

    // Copy data strings from Host memory to Device memory
    checkCudaErrors(cudaMemcpy(d_vec_row, h_vec_row, h_row * sizeof (img_data_t) * sizeof (char),
            cudaMemcpyHostToDevice));
    checkCudaErrors(cudaMemcpy(d_row, &h_row, sizeof (int),
            cudaMemcpyHostToDevice));
    checkCudaErrors(cudaMemcpy(d_vec_col, h_vec_col, h_col * sizeof (img_data_t) * sizeof (char),
            cudaMemcpyHostToDevice));
    checkCudaErrors(cudaMemcpy(d_col, &h_col, sizeof (int),
            cudaMemcpyHostToDevice));
    sdkStopTimer(&timer);
    time_val = sdkGetTimerValue(&timer);
    printf("Allocate and copy memory to device took:%fms\n", time_val);

    int dimGrid = h_row;
    int dimBlock = MAX_THREADS_PER_BLOCK;
    printf("kernel calc row - start\n");
    sdkResetTimer(&timer);
    sdkStartTimer(&timer);
    // launch kernel
    gpu_lzmp_single << <dimGrid, dimBlock>>>(d_vec_row, d_lzmp_val_row);
    printf("kernel calc row - complete\n");
    printf("kernel calc col - start\n");
    dimGrid = h_col;
    // launch kernel
    gpu_lzmp_single << <dimGrid, dimBlock>>>(d_vec_col, d_lzmp_val_col);
    printf("kernel calc col - complete\n");

    printf("kernel calc dist - start\n");
    dim3 dimGridSeq(h_row, h_col);
    gpu_dist_mat_two_arr << <dimGridSeq, dimBlock>>>(d_vec_row, d_lzmp_val_row, d_row,
            d_vec_col, d_lzmp_val_col, d_col, d_distMat);
    cudaDeviceSynchronize();
    sdkStopTimer(&timer);
    time_val = sdkGetTimerValue(&timer);
    sdkDeleteTimer(&timer);
    printf("kernel calc dist - complete\n");
    printf("All kernels took time:%fms\n", time_val);

    // Copy result from Device memory to Host memory
    checkCudaErrors(cudaMemcpy(h_distMat, d_distMat, h_row * h_col * sizeof (float),
            cudaMemcpyDeviceToHost));
    // Free Device memory
    checkCudaErrors(cudaFree(d_vec_row));
    checkCudaErrors(cudaFree(d_lzmp_val_row));
    checkCudaErrors(cudaFree(d_row));

    checkCudaErrors(cudaFree(d_vec_col));
    checkCudaErrors(cudaFree(d_lzmp_val_col));
    checkCudaErrors(cudaFree(d_col));

    checkCudaErrors(cudaFree(d_distMat));
}

/**
 *@brief  Calculating Distance Matrix from single Image sorted linked list,
 *		  This function will extract linked list to an array
 *		  since copy data to GPU available by passing pointer to an array
 *@param  img_list: pointer to images linked list,
 *        This parameter can be a value of @ref img_struct_t
 *@param  dist_mat: pointer to Distance Matrix
 *@param  dist_mat_len: Distance Matrix length
 *@retval true - success , false - not success
 */
bool gpu_dist_mat_from_img_list(img_struct_t *img_list, float *dist_mat, int dist_mat_len) {
    int totalImg;
    int totalImgSeq;
    StopWatchInterface *timer = NULL;
    sdkCreateTimer(&timer);

    printf("Calculation distance matrix from image list - Start\n");
    if (img_list == NULL) {
        printf("Empty image list - Return\n");
        return false;
    }
    totalImg = img_list->img_num + 1;
    totalImgSeq = totalImg * totalImg;
    if (totalImgSeq > dist_mat_len) {
        printf("Distance matrix length is to short - Return\n");
        return false;
    }

    // Should use dynamic memory allocation since our stack is limited.
    img_data_t *img_d = (img_data_t*) malloc(totalImg * sizeof (img_data_t));
    assert(img_d != NULL);

    printf("Total Images:%d, Total Sequences Pair:%d\n", totalImg, totalImgSeq);
    gpu_extract_from_list(img_list, img_d, totalImg);

    printf("Launch GPU kernel - Start\n");
    sdkResetTimer(&timer);
    sdkStartTimer(&timer);

    gpu_calc_dist_mat(img_d, totalImg, dist_mat);
    sdkStopTimer(&timer);
    printf("Launch GPU kernel - Complete, time:%fms\n",
            sdkGetTimerValue(&timer));
    sdkDeleteTimer(&timer);
    gpu_print_dist_mat_1D_array_as_2D_array(dist_mat, totalImg, totalImg);

    free(img_d);
    printf("Calculation distance matrix from image list - Complete\n");
    return true;
}

/**
 *@brief  Calculating Distance Matrix from sequence Images sorted linked lists,
 *		  This function will extract linked lists to a sequence arrays
 *		  since copy data to GPU available by passing pointer to an array
 *@param  img_row: pointer to images linked list per rows,
 *        This parameter can be a value of @ref img_struct_t
 *@param  img_col: pointer to images linked list per columns,
 *        This parameter can be a value of @ref img_struct_t
 *@param  dist_mat: pointer to Distance Matrix
 *@param  dist_mat_len: Distance Matrix length
 *@retval true - success , false - not success
 */
bool gpu_dist_mat_from_two_img_list(img_struct_t *img_row, img_struct_t *img_col, float *dist_mat, int dist_mat_len) {
    int row;
    int col;
    int total_img;
    StopWatchInterface *timer = NULL;

    sdkCreateTimer(&timer);
    printf("Calculation distance matrix from two images list - Start\n");
    if (img_row == NULL || img_col == NULL) {
        printf("Empty image list - Return\n");
        return false;
    }

    row = img_row->img_num + 1;
    col = img_col->img_num + 1;
    total_img = row * col;
    if (total_img > dist_mat_len) {
        printf("Distance matrix length is to short - Return\n");
        return false;
    }

    printf("Image rows:%d Image columns:%d Total Sequences Pair:%d\n", row, col,
            total_img);

    // Should use dynamic memory allocation since our stack is limited.
    img_data_t *img_d_row = (img_data_t*) malloc(row * sizeof (img_data_t));
    assert(img_d_row != NULL);
    img_data_t *img_d_col = (img_data_t*) malloc(col * sizeof (img_data_t));
    assert(img_d_col != NULL);

    gpu_extract_from_list(img_row, img_d_row, row);
    gpu_extract_from_list(img_col, img_d_col, col);

    printf("Launch GPU kernel - Start\n");
    sdkResetTimer(&timer);
    sdkStartTimer(&timer);

    gpu_calc_dist_mat_from_two_arr(img_d_row, row, img_d_col, col, dist_mat);
    sdkStopTimer(&timer);
    printf("Launch GPU kernel - Complete, time:%fms\n",
            sdkGetTimerValue(&timer));
    sdkDeleteTimer(&timer);

    gpu_print_dist_mat_1D_array_as_2D_array(dist_mat, row, col);

    free(img_d_row);
    free(img_d_col);
    printf("Calculation distance matrix from image list - Complete\n");
    return true;
}
