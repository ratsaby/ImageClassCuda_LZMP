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
