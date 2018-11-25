/**
  ******************************************************************************
  * @file    write_cases_to_file.cpp
  * @author  alexb
  * @brief   write_cases_to_file
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

#include <write_cases_to_file.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <sys/stat.h>
#include "make_path.h"
#include <entropy.h>

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
bool write_cases_to_f(cat_struct_array_t* category, cat_struct_array_t* images, int row_cat, int col_img, float* normal_count_mat, char* dtype) {
    FILE* f;
    char write_file[256];
    // current date/time based on current system
    time_t now = time(0);
    // convert now to string form
    char* dt = ctime(&now);

    char* ptr;
    strcpy(write_file, make_path_get_cases_save_path());
    if (mkdir(write_file, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
        printf("path to cases created\n");
    }

    ptr = strchr(write_file, '\0');
    strcpy(ptr, SAVE_CASES_FILE);
    ptr = strchr(write_file, '\0');
    strcpy(ptr, "_");
    ptr = strchr(write_file, '\0');
    strcpy(ptr, dt);
    ptr = strchr(write_file, '\0');
    strcpy(ptr, dtype);
    ptr = strchr(write_file, '\0');
    strcpy(ptr, SAVE_CASES_FILE_EXTENSION);
    make_path_remove_spaces(write_file);

    char find = '\n';
    char replace = '_';
    make_path_change_chr(write_file, find, replace);

    f = fopen(write_file, "w");
    printf("Write data to file: %s\n", write_file);
    if (f == NULL) {
        printf("can't create file\n");
        return false;
    }
    printf("Copy time to file:%s", dt);
    fprintf(f, "//");
    fprintf(f, "%s\n", dt);

    printf("Copy category names to file\n");
    for (int i = 0; i < row_cat; i++) {
        printf("%s ", category[i].name);
        fprintf(f, SEPERATOR3);
        fprintf(f, "%s", category[i].name);
        fprintf(f, SEPERATOR3);
        fprintf(f, SEPERATOR2);
    }
    fprintf(f, SEPERATOR3);
    fprintf(f, "%s", "entropy");
    fprintf(f, SEPERATOR3);
    fprintf(f, SEPERATOR2);
    fprintf(f, SEPERATOR3);
    fprintf(f, "%s", TARGET_CLASS);
    fprintf(f, SEPERATOR3);
    fprintf(f, SEPERATOR2);
    fprintf(f, SEPERATOR3);
    fprintf(f, "%s", TARGET_CLASS_FILE_NAME);
    fprintf(f, SEPERATOR3);
    fprintf(f, "\n");

    int ind1D;
    char target_name[256];
    char last_name[256];
    char current_name[256];
    int count = 0;
    last_name[0] = '\0';

    float entrp_everg = 0;
    float entrp;
    float* n_count_single_col = (float*)malloc(row_cat * sizeof(float));

    for (int i = 0; i < col_img; i++) {
        for (int j = 0; j < row_cat; j++) {
            ind1D = i + j*col_img;
            n_count_single_col[j] = normal_count_mat[ind1D];
            fprintf(f, "%f", normal_count_mat[ind1D]);
            fprintf(f, SEPERATOR2);
        }
        make_path_copy_string_to_separator(current_name, images[i].name, '_');
        if(strcmp(last_name, current_name) != 0){
                	count++;
        }
        fprintf(f, "%d", count);
        fprintf(f, SEPERATOR2);
        // entropy of single case
        entrp = entropy_single_case(n_count_single_col, row_cat);
        entrp_everg += entrp;
        fprintf(f, "%f", entrp);
        fprintf(f, SEPERATOR2);
        //
        strcpy(last_name, current_name);
        make_path_copy_string_to_separator(target_name, images[i].name, '.');
        fprintf(f, "%s", target_name);
        fprintf(f, SEPERATOR2);
        fprintf(f, "%s\n", images[i].name);
    }
    fprintf(f, "average entropy of all cases:%f\n", (float)((double)entrp_everg / (double)col_img));
    fclose(f);
    free(n_count_single_col);
    printf("\nwrite data to file - Complete\n");
}
