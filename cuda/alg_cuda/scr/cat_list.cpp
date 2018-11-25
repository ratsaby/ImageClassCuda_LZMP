/**
  ******************************************************************************
  * @file    cat_list.cpp
  * @author  alexb
  * @brief   cat_list
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

#include <cat_list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <make_path.h>
#include <write_cases_to_file.h>

/**
 *@brief  Private variables
 */
static cat_struct_t *cat_list = NULL; /*!< pointer to Prototypes category list*/
static cat_struct_t *cat_img_list = NULL; /*!< pointer to Images category list    */

static int members_in_list = 0; /*!< total members in Prototypes category list*/
static int img_members_in_list = 0; /*!< total members in Images category list*/

/**
 *@brief  Get reference to category (Prototypes) linked list 
 *@param  None
 *@retval Reference to category (Prototypes) linked list 
 *        This parameter can be a value of @ref cat_struct_t
 */
cat_struct_t *cat_list_get_ref_to_list(void) {
    return cat_list;
}

/**
 *@brief  Clear number of nodes (Prototypes) in linked list 
 *@param  None
 *@retval None
 */
void clear_total_members(void) {
    members_in_list = 0;
}

/**
 *@brief  Get total number of nodes (Prototypes) in linked list 
 *@param  None
 *@retval Total number of nodes (Prototypes) in current linked list
 */
int cat_list_get_total_members(void) {
    return members_in_list;
}

/**
 *@brief  Get reference to category (Images) linked list 
 *@param  None
 *@retval Reference to category (Images) linked list 
 *        This parameter can be a value of @ref cat_struct_t
 */
cat_struct_t *cat_list_get_ref_to_img_list(void) {
    return cat_img_list;
}

/**
 *@brief  Clear number of nodes (Images) in linked list 
 *@param  None
 *@retval None
 */
void clear_total_members_img(void) {
    img_members_in_list = 0;
}

/**
 *@brief  Get total number of nodes (Images) in linked list 
 *@param  None
 *@retval Total number of nodes (Images) in current linked list
 */
int cat_list_get_total_members_img(void) {
    return img_members_in_list;
}

/**
 *@brief  Printing all nodes data in linked list 
 *@param  list: pointer to linked list,
 *        This parameter can be a value of @ref cat_struct_t
 *@retval None
 */
void cat_list_print_list(cat_struct_t *list) {
    cat_struct_t *current = list;

    while (current != NULL) {
        printf("[%d] name:%s, num_of_img:%d\n", current->num, current->name, current->num_of_img);
        current = current->next;
    }
}

/**
 *@brief  Free linked list 
 *@param  list: pointer to linked list,
 *        This parameter can be a value of @ref cat_struct_t
 *@retval None
 */
void cat_list_free_list(cat_struct_t *list) {
    cat_struct_t *current = list;
    while (current != NULL) {
        free(current);
        current = current->next;
    }
}

/**
 *@brief  Push string name to linked list (Prototypes)
 *@param  cat_name: pointer to a string name,
 *@param  num_of_prototypes: current name number   
 *@retval None
 */
void cat_list_push_to_list(char *cat_name, int num_of_prototype) {
    cat_struct_t *new_node = (cat_struct_t*) malloc(sizeof (cat_struct_t));

    if (new_node == NULL) {
        assert(false);
    }
    strcpy(new_node->name, cat_name);
    new_node->num_of_img = num_of_prototype;
    new_node->num = members_in_list;
    new_node->next = cat_list;
    cat_list = new_node;
    members_in_list++;
}

/**
 *@brief  Push string name to linked list (Image)
 *@param  cat_name: pointer to a string name,
 *@param  num_of_prototypes: current name number   
 *@retval None
 */
void cat_list_push_to_list_img(char *name, int num_of_img) {
    cat_struct_t *new_node = (cat_struct_t*) malloc(sizeof (cat_struct_t));

    if (new_node == NULL) {
        assert(false);
    }
    strcpy(new_node->name, name);
    new_node->num_of_img = num_of_img;
    new_node->num = img_members_in_list;
    new_node->next = cat_img_list;
    cat_img_list = new_node;
    img_members_in_list++;
}

/**
 *@brief  Extract data from a given linked list and copy to array 
 *@param  cat: pointer to an array, data will be copied to this array
 *        This parameter can be a value of @ref cat_struct_array_t
 *@param  cat_members: total members in a given array 
 *@param  list: pointer to a linked list, data will be copied from this list 
 *        This parameter can be a value of @ref cat_struct_t  
 *@retval None
 */
void cat_list_array_from_list(cat_struct_array_t* cat, int cat_members, cat_struct_t* list) {
    int list_members = list->num;
    int indx;

    assert(list_members < cat_members);
    while (list != NULL) {
        indx = list_members - list->num;
        strcpy(cat[indx].name, list->name);
        cat[indx].num_of_img = list->num_of_img;
        list = list->next;
    }
    for (int i = 0; i < cat_members; i++) {
        printf("array[%d] name:%s, num of img:%d\n", i, cat[i].name, cat[i].num_of_img);
    }
}

/**
 *@brief  Find index of a minimal value in a given array
 *@param  ptr: pointer to an array
 *@param  size: total members in a given array  
 *@retval Index of a minimal value of array
 */
int cat_index_min_val_in_array(float* ptr, int size) {
    int min_indx = 0;

    assert(ptr != NULL);
    float min = ptr[0];
    for (int i = 1; i < size; i++) {
        if (ptr[i] < min) {
            min = ptr[i];
            min_indx = i;
        }
    }
    return min_indx;
}

/**
 *@brief  Find Euclidean distance to category from a Distance Matrix
 *        and write cases to file by calling to @ref write_cases_to_f() function
 *@param  dist_mat1D: pointer to a Distance Matrix 1 Dimension array
 *@param  row: total row members of a Distance Matrix 
 *@param  col: total column members of a Distance Matrix 
 *@retval None
 */
void cat_list_euclidean_dist_to_cat(float *dist_mat1D, int row, int col) {
    int row_cat = cat_list_get_total_members();
    int col_img = cat_list_get_total_members_img();
    float sub_img_cat_vec[row_cat][col];
    float dist_mat2D[row][col];
    int count[row_cat][col_img];
    cat_struct_array_t category[row_cat];
    cat_struct_array_t images[col_img];

    cat_struct_dist_t cat_dist[col];

    cat_list_array_from_list(category, row_cat, cat_list);
    cat_list_array_from_list(images, col_img, cat_img_list);
    memset((char*) &count, 0, sizeof (count));

    int index;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            index = j + i*col;
            //printf("%f ", dist_mat1D[index]);
            dist_mat2D[i][j] = dist_mat1D[index];
        }
        //printf("\n");
    }
    printf("\nprint mat 2D, row = category, col = sub images\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%f ", dist_mat2D[i][j]);
        }
        printf("\n");
    }

    for (int j = 0; j < col; j++) {
        double temp = 0;
        int delta_row = 0;
        int k = 0;
        for (int i = 0; i < row; i++) {
            temp += dist_mat2D[i][j] * dist_mat2D[i][j];
            if (delta_row + category[k].num_of_img - 1 == i) {
            	temp *= 1 / (double)category[k].num_of_img;
                sub_img_cat_vec[k][j] = (float) sqrt(temp);
                temp = 0;
                delta_row = i + 1;
                k++;
            }
        }
    }
    printf("\neuclidian distance to each category, row = category, col = sub images\n");
    for (int i = 0; i < row_cat; i++) {
        for (int j = 0; j < col; j++) {
            printf("%f ", sub_img_cat_vec[i][j]);
        }
        printf("\n");
    }

    float temp_vec[row_cat];
    int z = 0;
    int delta_col = 0;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row_cat; j++) {
            temp_vec[j] = sub_img_cat_vec[j][i];
        }
        count[cat_index_min_val_in_array(temp_vec, row_cat)][z]++;
        if (delta_col + images[z].num_of_img - 1 == i) {
            z++;
            delta_col = i + 1;
        }
    }
    printf("\nCounts of each category\n");
    printf("rows is a category: ");
    for (int i = 0; i < row_cat; i++) {
        printf("%s, ", category[i].name);
    }
    printf("\ncols is an images: ");
    for (int j = 0; j < col_img; j++) {
        printf("%s, ", images[j].name);
    }
    printf("\n");
    for (int i = 0; i < row_cat; i++) {
        for (int j = 0; j < col_img; j++) {
            printf("%d ", count[i][j]);
        }
        printf("\n");
    }
    printf("\nNormalized Counts of each category\n");
    double sum[col_img];
    memset((char*) &sum, 0, sizeof (sum));
    for (int j = 0; j < col_img; j++) {
        for (int i = 0; i < row_cat; i++) {
            sum[j] += count[i][j];
        }
    }
    float count_normal2D[row_cat][col_img];
    float count_normal1D[row_cat * col_img];
    for (int i = 0; i < row_cat; i++) {
        for (int j = 0; j < col_img; j++) {
            count_normal2D[i][j] = (float) (count[i][j] / sum[j]);
            printf("%f ", count_normal2D[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int ind1D;
    for (int i = 0; i < row_cat; i++) {
        for (int j = 0; j < col_img; j++) {
            ind1D = j + i*col_img;
            count_normal1D[ind1D] = count_normal2D[i][j];
            printf("%f ", count_normal1D[ind1D]);
        }
        printf("\n");
    }
    write_cases_to_f(category, images, row_cat, col_img, count_normal1D, DIST1);
}

/**
 *@brief  Find ExplicitProtoDistInCase from a Distance Matrix
 *        and write cases to file by calling to @ref write_cases_to_f() function
 *@param  dist_mat1D: pointer to a Distance Matrix 1 Dimension array
 *@param  row: total row members of a Distance Matrix
 *@param  col: total column members of a Distance Matrix
 *@retval None
 */
void cat_list_ExplicitProtoDistInCase(float *dist_mat1D, int row, int col) {
    int row_cat = cat_list_get_total_members();
    int col_img = cat_list_get_total_members_img();
    int** count = (int**) malloc(row * sizeof (int*));

    if (count == NULL) {
        printf("can't allocate 2d int array\n");
        return;
    }
    for (int i = 0; i < row; i++) {
        count[i] = (int*) malloc(col_img * sizeof (int));
        if (count[i] == NULL) {
            printf("can't allocate 2d int array\n");
            return;
        }
    }
    float* count_normal1D = (float*) malloc(row * col_img * sizeof (float));
    if (count_normal1D == NULL) {
        printf("out of mem, return\n");
        return;
    }
    size_t* count_max = (size_t*) malloc(col_img * sizeof (size_t));
    if (count_max == NULL) {
        printf("count_max, out of mem, return\n");
        return;
    }
    cat_struct_array_t* category = (cat_struct_array_t*) malloc(row_cat * sizeof (cat_struct_array_t));
    cat_struct_array_t* proto = (cat_struct_array_t*) malloc(row * sizeof (cat_struct_array_t));
    cat_struct_array_t* images = (cat_struct_array_t*) malloc(col_img * sizeof (cat_struct_array_t));

    if (category == NULL || proto == NULL || images == NULL) {
        printf("out of mem, return\n");
        return;
    }
    cat_list_array_from_list(category, row_cat, cat_list);
    cat_list_array_from_list(images, col_img, cat_img_list);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col_img; j++) {
            count[i][j] = 0;
        }
    }

    int col_current_indx = 0;
    int closes_proto_index;
    float min_uid;
    int index1D;
    for (int i = 0; i < col_img; i++) { // for all images
        closes_proto_index = 0;
        for (int j = 0; j < images[i].num_of_img; j++) { // for all sub-images
        	min_uid = 1;
            for (int k = 0; k < row; k++) { // for all prototypes
                index1D = col_current_indx + k * col;
                if (dist_mat1D[index1D] < min_uid) {
                    min_uid = dist_mat1D[index1D];
                    closes_proto_index = k;
                }
            }
            count[closes_proto_index][i]++;
            col_current_indx++;
        }
    }
    memset(count_max, 0, col_img * sizeof (size_t));
    for (int i = 0; i < col_img; i++) {
        for (int k = 0; k < row; k++) {
            count_max[i] += count[k][i];
        }
    }
    memset(count_normal1D, 0, row * col_img * sizeof (float));
    for (int i = 0; i < col_img; i++) {
        for (int k = 0; k < row; k++) {
            //index1D = k + i*col_img;
            index1D = i + k*col_img;
            count_normal1D[index1D] = (float) ((double) count[k][i] / (double) count_max[i]);
        }
    }
//    printf("normalized counts, row - proto, col - images\n");
//    for (int k = 0; k < row; k++) {
//        for (int i = 0; i < col_img; i++) {
//            index1D = i + k*col_img;
//            printf("%f ", count_normal1D[index1D]);
//        }
//        printf("\n");
//    }
    printf("prototypes names\n");
    int row_index = 0;
    char name[0xff];
    char* ptr;
    for (int i = 0; i < row_cat; i++) { // copy all prototypes name to new array
        for (int j = 0; j < category[i].num_of_img; j++) {
        	strcpy(name, category[i].name);
        	ptr = strchr(name, '\0');
        	sprintf(ptr, "%d", j);
            strcpy(proto[row_index].name, name);
            printf("proto[%d]:%s\n", row_index, proto[row_index].name);
            row_index++;
        }
    }
    write_cases_to_f(proto, images, row, col_img, count_normal1D, DIST2);

    for (int i = 0; i < row; i++) {
        free(count[i]);
    }
    free(count);
    free(count_normal1D);
    free(count_max);
    free(category);
    free(proto);
    free(images);
}



#define CAT_FOREST_NAME 		"forest"   /*!< category name for test*/
#define CAT_SEA_NAME 	     	        "sea"      /*!< category name for test*/
#define CAT_DESERT_NAME 		"desert"   /*!< category name for test*/
#define CAT_CITY_NAME 		        "city"     /*!< category name for test*/

#define CAT_FOREST_num_of_img            10  /*!< images in categoory for test*/
#define CAT_SEA_num_of_img               155 /*!< images in categoory for test*/
#define CAT_DESERT_num_of_img            134 /*!< images in categoory for test*/
#define CAT_CITY_num_of_img              77  /*!< images in categoory for test*/

/**
 *@brief  Test function for testing category linked list
 *@param  None 
 *@retval None
 */
void cat_list_test(void) {
    printf("starting test category list\n");
    cat_list_push_to_list(CAT_FOREST_NAME, CAT_FOREST_num_of_img);
    cat_list_push_to_list(CAT_SEA_NAME, CAT_SEA_num_of_img);
    cat_list_push_to_list(CAT_DESERT_NAME, CAT_DESERT_num_of_img);
    cat_list_push_to_list(CAT_CITY_NAME, CAT_CITY_num_of_img);
    cat_list_print_list(cat_list_get_ref_to_list());
    cat_list_free_list(cat_list_get_ref_to_list());
}
