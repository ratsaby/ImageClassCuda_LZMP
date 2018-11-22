#ifndef CAT_LIST_H_
#define CAT_LIST_H_

#include <img_types.h>

/**
 *@brief  Get reference to category (Prototypes) linked list 
 *@param  None
 *@retval Reference to category (Prototypes) linked list 
 *        This parameter can be a value of @ref cat_struct_t
 */
cat_struct_t *cat_list_get_ref_to_list(void);

/**
 *@brief  Get reference to category (Images) linked list 
 *@param  None
 *@retval Reference to category (Images) linked list 
 *        This parameter can be a value of @ref cat_struct_t
 */
cat_struct_t *cat_list_get_ref_to_img_list(void);

/**
 *@brief  Get total number of nodes (Images) in linked list 
 *@param  None
 *@retval Total number of nodes (Images) in current linked list
 */
int cat_list_get_total_members(void);

/**
 *@brief  Printing all nodes data in linked list 
 *@param  list: pointer to linked list,
 *        This parameter can be a value of @ref cat_struct_t
 *@retval None
 */
void cat_list_print_list(cat_struct_t *list);

/**
 *@brief  Free linked list 
 *@param  list: pointer to linked list,
 *        This parameter can be a value of @ref cat_struct_t
 *@retval None
 */
void cat_list_free_list(cat_struct_t *list);

/**
 *@brief  Push string name to linked list (Prototypes)
 *@param  cat_name: pointer to a string name,
 *@param  num_of_prototypes: current name number   
 *@retval None
 */
void cat_list_push_to_list(char *cat_name, int num_of_prototype);

/**
 *@brief  Push string name to linked list (Image)
 *@param  cat_name: pointer to a string name,
 *@param  num_of_prototypes: current name number   
 *@retval None
 */
void cat_list_push_to_list_img(char *name, int num_of_img);


/**
 *@brief  Find Euclidean distance to category from a Distance Matrix
 *        and write cases to file by calling to @ref write_cases_to_f() function
 *@param  dist_mat1D: pointer to a Distance Matrix 1 Dimension array
 *@param  row: total row members of a Distance Matrix 
 *@param  col: total column members of a Distance Matrix 
 *@retval None
 */
void cat_list_euclidean_dist_to_cat(float *dist_mat1D, int row, int col);

/**
 *@brief  Find ExplicitProtoDistInCase from a Distance Matrix
 *        and write cases to file by calling to @ref write_cases_to_f() function
 *@param  dist_mat1D: pointer to a Distance Matrix 1 Dimension array
 *@param  row: total row members of a Distance Matrix
 *@param  col: total column members of a Distance Matrix
 *@retval None
 */
void cat_list_ExplicitProtoDistInCase(float *dist_mat1D, int row, int col);
/**
 *@brief  Test function for testing category linked list
 *@param  None 
 *@retval None
 */
void cat_list_test(void);

#endif //CAT_LIST_H_
