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
