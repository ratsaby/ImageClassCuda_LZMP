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
