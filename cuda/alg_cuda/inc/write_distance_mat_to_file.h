/**
  ******************************************************************************
  * @file    write_distance_mat_to_file.h
  * @author  alexb
  * @brief   Header file containing functions prototypes of write_distance_mat_to_file
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

#ifndef _WRITE_DISTANCE_MAT_TO_FILE_H
#define _WRITE_DISTANCE_MAT_TO_FILE_H

#include "definitions.h"
#include "img_types.h"

#define FILE_DIST_PATH            SAVE_DISTANCE_MAT_PATH
#define FILE_DIST_NAME            SAVE_DISTANCE_MAT_FILE
#define FILE_DIST_NAME_EXT        SAVE_DISTANCE_MAT_FILE_EXTENSION

/**
 *@brief  Write Distance Matrix to file
 *@param  dist: pointer to Distances array
 *@param  rows: number of members in array
 *@param  name: pointer to string names
 *        This parameter can be a value of @ref img_file_name_t
 *@retval true - success , false - not success
 */
bool write_dist_to_file(float* dist, int rows, img_file_name_t* name);

#endif //_WRITE_DISTANCE_MAT_TO_FILE_H
