/**
  ******************************************************************************
  * @file    write_cases_to_file.h
  * @author  alexb
  * @brief   Header file containing functions prototypes of write_cases_to_file
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

#ifndef WRITE_CASES_TO_FILE_H_
#define WRITE_CASES_TO_FILE_H_
#include "definitions.h"
#include "img_types.h"

/**
 *@brief  Write cases to file
 *@param  category: pointer to string category names 
 *        This parameter can be a value of @ref cat_struct_array_t
 *@param  images: pointer to string images names 
 *        This parameter can be a value of @ref cat_struct_array_t
 *@param  row_cat: number of categories
 *@param  col_img: number of images
 *@param  normal_count_mat: pointer to a normalized counters
 *@param  dtype: pointer to a name of distance type
 *@retval true - success , false - not success
 */
bool write_cases_to_f(cat_struct_array_t* category, cat_struct_array_t* images, int row_cat, int col_img, float* normal_count_mat, char* dtype);

#endif // WRITE_CASES_TO_FILE_H_
