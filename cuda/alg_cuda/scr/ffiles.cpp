/**
  ******************************************************************************
  * @file    ffiles.cpp
  * @author  alexb
  * @brief   Find files
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

#include <ffiles.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <make_path.h>
#include <cat_list.h>
#include <ocv_functions.h>
#include <definitions.h>


/**
 *@brief  Private variables
 */
static int num_of_sub_images = 0;       /*!< number of sub images */
static int num_of_prot_in_cat = 0;      /*!< number of prototypes */

/**
 *@brief  Scan directory of prototypes (sorted order) 
 *        and push image files to linked list
 *@param  None
 *@retval true - success , false - not success
 */
bool ffiles_prototypes_sorted(void) {
    struct dirent **namelist;
    int n;

    n = scandir(make_path_get_search_unlab_prot_path(), &namelist, 0, alphasort);
    if (n < 0) {
        perror("scandir");
        return false;
    } else {
        while (n--) {
            if (namelist[n]->d_name[0] != '.') {
                printf("loading image %s\n", namelist[n]->d_name);
                ocv_push_img_to_list(make_path_get_search_unlab_prot_path(), namelist[n]->d_name);
            }
            free(namelist[n]);
        }
        free(namelist);
    }
    return true;
}

/******************************************************************************
 ** find sub images
 ******************************************************************************/


/**
 *@brief  Scan directory of sub images (sorted order) 
 *        and push image files to linked list
 *@param  None
 *@retval true - success , false - not success
 */
bool ffiles_sub_imgs_sorted(void) {
    struct dirent **namelist;
    int n;
    int sub_imges;

    n = scandir(make_path_get_input_image_read_path(), &namelist, 0, alphasort);
    if (n < 0) {
        perror("scandir");
        return false;
    } else {
        while (n--) {
            if (namelist[n]->d_name[0] != '.') {
                printf("loading image %s\n", namelist[n]->d_name);
                sub_imges = ocv_push_sub_imgs_to_list(make_path_get_input_image_read_path(), namelist[n]->d_name);
                if (sub_imges != -1) {
                    cat_list_push_to_list_img(namelist[n]->d_name, sub_imges);
                }
            }
            free(namelist[n]);
        }
        free(namelist);
    }
    return true;
}

/**
 *@brief  Find prototypes in a given path
 *@param  path: pointer to path string 
 *@retval true - success , false - not success
 */
bool scan_for_prototypes_list(char *path) {
    struct dirent **namelist;
    int n;

    n = scandir(path, &namelist, 0, alphasort);
    num_of_prot_in_cat = 0;
    if (n < 0) {
        perror("scandir");
        return false;
    } else {
        while (n--) {
            if (namelist[n]->d_name[0] != '.') {
                num_of_prot_in_cat++;
                printf("loading image:%d, name:%s\n", num_of_prot_in_cat, namelist[n]->d_name);
                ocv_push_proto_to_list(path, namelist[n]->d_name);
            }
            free(namelist[n]);
        }
        free(namelist);
    }
    return true;
}

/**
 *@brief  Find category prototypes in a given path
 *@param  None 
 *@retval true - success , false - not success
 */
bool ffiles_cat_prototypes(void) {
    DIR *dp;
    struct dirent *ep;
    char full_path[256];
    char *ptr;

    dp = opendir(make_path_get_sorted_prot_path());
    if (dp != NULL) {
        while (ep = readdir(dp)) {
            if (ep->d_name[0] != '.') {
                make_path_add_strings(full_path, make_path_get_sorted_prot_path(), ep->d_name);
                ptr = strchr(full_path, '\0');
                strcpy(ptr, SEPERATOR);
                scan_for_prototypes_list(full_path);
                cat_list_push_to_list(ep->d_name, num_of_prot_in_cat);
            }
        }
        (void) closedir(dp);
    } else {
        perror("Couldn't open the directory");
        return false;
    }
    return true;
}




