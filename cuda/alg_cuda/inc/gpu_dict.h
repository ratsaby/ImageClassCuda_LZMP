/**
  ******************************************************************************
  * @file    gpu_dict.h
  * @author  alexb
  * @brief   Header file containing functions prototypes of gpu_dict
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015, Alexander Belousov and Joel Ratsaby All rights reserved.</center></h2>
  *
  * LICENSE CONDITIONS
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Ariel University nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#ifndef GPU_DICT_H
#define GPU_DICT_H


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
bool gpu_dist_mat_from_img_list(img_struct_t *img_list, float *dist_mat, int dist_mat_len);

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
bool gpu_dist_mat_from_two_img_list(img_struct_t *img_row, img_struct_t *img_col, float *dist_mat, int dist_mat_len);
#endif // GPU_DICT_H
