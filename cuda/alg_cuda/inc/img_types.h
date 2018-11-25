/**
  ******************************************************************************
  * @file    img_types.h
  * @author  alexb
  * @brief   Header file containing functions prototypes of img_types
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

#ifndef IMG_TYPES_H
#define IMG_TYPES_H
#include "definitions.h"

/**
 * @brief Image Structure data type
 */
typedef struct img_struct {
    char img_data[MAX_STRING_SIZE_IN_BYTES]; /*!< Image data                  */
    char file_name[FILE_NAME_MAX_LENGTH];    /*!< Image file name             */
    int img_num;                             /*!< Image current number in list*/
    int image_size;                          /*!< Image data size pixels      */
    int width;                               /*!< Image width pixels          */
    int height;                              /*!< Image height pixels         */
    struct img_struct *next;                 /*!< pointer to next node in list*/
} img_struct_t;

/**
 * @brief Image structure pure data type 
 */
typedef struct img_data {
    char data[MAX_ARRAY_SIZE];              /*!< Image pure data              */
    int len;                                /*!< Image pure data lenght       */
} img_data_t;

/**
 * @brief Image file name type
 */
typedef struct img_file_name {
    char file_name[FILE_NAME_MAX_LENGTH];   /*!< Image file name              */
} img_file_name_t;

/**
 * @brief Category name type
 */
typedef struct cat_struct {
    char name[FILE_NAME_MAX_LENGTH];        /*!< Category full name           */
    int num;                                /*!< Category number in list      */
    int num_of_img;                         /*!< Category total number images */
    struct cat_struct *next;
} cat_struct_t;

/**
 * @brief Category lite name type 
 */
typedef struct cat_struct_array {
    char name[FILE_NAME_MAX_LENGTH];        /*!< Category full name           */
    int num_of_img;                         /*!< Category total number images */
} cat_struct_array_t;

/**
 * @brief Category distance type 
 */
typedef struct cat_struct_dist {
    char name[FILE_NAME_MAX_LENGTH];        /*!< Category full name           */
    float dist;                             /*!< Distance value of sequence   */
} cat_struct_dist_t;

#endif // IMG_TYPES_H
