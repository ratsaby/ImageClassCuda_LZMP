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
