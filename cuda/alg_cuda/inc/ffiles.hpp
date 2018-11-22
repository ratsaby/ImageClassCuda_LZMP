#ifndef _FFILES_HPP
#define _FFILES_HPP


/**
 *@brief  Scan directory of prototypes (sorted order) 
 *        and push image files to linked list
 *@param  None
 *@retval true - success , false - not success
 */
bool ffiles_prototypes_sorted(void);

/**
 *@brief  Scan directory of sub images (sorted order) 
 *        and push image files to linked list
 *@param  None
 *@retval true - success , false - not success
 */
bool ffiles_sub_imgs_sorted(void);

/**
 *@brief  Find category prototypes in a given path
 *@param  None 
 *@retval true - success , false - not success
 */
bool ffiles_cat_prototypes(void);

#endif // _FFILES_HPP
