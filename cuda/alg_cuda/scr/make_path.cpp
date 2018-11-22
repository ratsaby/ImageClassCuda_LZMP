#include <make_path.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <definitions.h>

/**
 *@brief  Private variables
 */
static char search_unlab_prot_path[FILE_NAME_MAX_LENGTH]; /*!< search for unlabeled prototypes path*/
static char save_unlab_prot_gray_path[FILE_NAME_MAX_LENGTH]; /*!< save unlabeled prototypes gray path */
static char sorted_prot_path[FILE_NAME_MAX_LENGTH]; /*!< labeled prototypes path             */
static char input_image_read_path[FILE_NAME_MAX_LENGTH]; /*!< read input images path             */
static char input_image_save_gray_path[FILE_NAME_MAX_LENGTH]; /*!< save input images gray path       */
static char sub_image_save_gray_path[FILE_NAME_MAX_LENGTH]; /*!< save sub images gray path          */
static char distance_mat_save_path[FILE_NAME_MAX_LENGTH]; /*!< save Distance Matrix file path     */
static char cases_save_path[FILE_NAME_MAX_LENGTH]; /*!< save cases file path               */

/**
 *@brief  Copy category name from a given file name 
 *@param  image_name: pointer to a file name string
 *@param  category: pointer to a category string that name of category will be copied to
 *@retval None
 */
void make_path_category_from_path(char *image_name, char *category) {
    int index = 0;

    while (true) {
        category[index] = image_name[index];
        index++;
        if (image_name[index] == '_')
            break;
    }
    category[index++] = '/';
    category[index] = '\0';
}

/**
 *@brief  Copy string from the beginning of a given string to a given separator
 *@param  copy_to_str: pointer to string that copy to 
 *@param  copy_from_str: string from start copy
 *@param  separator: character where to should stop copy
 *@retval None
 */
void make_path_copy_string_to_separator(char *copy_to_str, char *copy_from_str, char separator) {
    int index = 0;

    while (true) {
        copy_to_str[index] = copy_from_str[index];
        index++;
        if (copy_from_str[index] == separator)
            break;
    }
    copy_to_str[index++] = '/';
    copy_to_str[index] = '\0';
}

/**
 *@brief  Add a postfix to a given file name
 *@param  new_file_name: pointer to string that copy to 
 *@param  postfix: string that would be added to a given file name
 *@param  old_file_name: pointer to string that copy from 
 *@retval None
 */
void make_path_add_postfix_to_image(char *new_file_name, char *postfix, char *old_file_name) {
    char extension[10];
    char *ptr;

    strcpy(new_file_name, old_file_name);
    ptr = strchr(new_file_name, '.');
    strcpy(extension, ptr);
    strcpy(ptr, postfix);
    ptr = strchr(new_file_name, '\0');
    strcpy(ptr, extension);
}

/**
 *@brief  Add a integer postfix to a given file name
 *@param  new_file_name: pointer to string that copy to 
 *@param  val: integer value that would be added to a given file name
 *@param  old_file_name: pointer to string that copy from 
 *@retval None
 */
void make_path_add_int_postfix_to_image(char *new_file_name, int val, char *old_file_name) {
    char extension[10];
    char postfix[15];
    char *ptr;

    assert(val < 99999);
    sprintf(postfix, "%d", val);

    strcpy(new_file_name, old_file_name);
    ptr = strchr(new_file_name, '.');
    strcpy(extension, ptr);
    strcpy(ptr, postfix);
    ptr = strchr(new_file_name, '\0');
    strcpy(ptr, extension);
}

/**
 *@brief  Remove spaces in a given file name
 *@param  str: pointer to a string 
 *@retval None
 */
void make_path_remove_spaces(char *str) {
    char *ptr;

    ptr = strchr(str, ' ');
    while (ptr != NULL) {
        *ptr = '_';
        ptr = strchr(ptr + 1, ' ');
    }
}

/**
 *@brief  Replace a character in a given string
 *@param  str: pointer to a string 
 *@param  find: find character that should replace
 *@param  replace: replace by a given character  
 *@retval true - success , false - not success
 */
bool make_path_change_chr(char* str, char find, char replace) {
    char* ptr;

    ptr = strchr(str, find);
    if (ptr != NULL) {
        *ptr = replace;
        return true;
    }
    return false;
}


/**
 *@brief  Add two strings and copy to new one
 *@param  new_str: pointer to new string 
 *@param  old_str: pointer to old string 
 *@param  add_str: pointer to string that should to add
 *@retval None
 */
void make_path_add_strings(char *new_str, char *old_str, char *add_str) {
    char *ptr;

    strcpy(new_str, old_str);
    ptr = strchr(new_str, '\0');
    strcpy(ptr, add_str);
}

/**
 *@brief  Add three strings and copy to new one
 *@param  new_str: pointer to new string 
 *@param  str1: pointer to first string 
 *@param  str2: pointer to second string
 *@param  str3: pointer to third string
 *@retval None
 */
void make_path_add_3_strings(char* new_str, char* str1, char* str2, char* str3) {
    strcat(new_str, str1);
    strcat(new_str, str2);
    strcat(new_str, str3);
}

/**
 *@brief  Add a user name strings to all system paths
 *@param  user_name: pointer to user name string 
 *@retval None
 */
void make_path_all_system_path(char *user_name) {
    make_path_add_3_strings(search_unlab_prot_path, HOME_PATH, user_name, SEARCH_PATH_FOLDER);
    make_path_add_3_strings(save_unlab_prot_gray_path, HOME_PATH, user_name, GRAY_IMAGE_PATH_TO_SAVE);
    make_path_add_3_strings(sorted_prot_path, HOME_PATH, user_name, IMAGE_PATH_SORTED_PROT);
    make_path_add_3_strings(input_image_read_path, HOME_PATH, user_name, INPUT_IMAGE_PATH);
    make_path_add_3_strings(input_image_save_gray_path, HOME_PATH, user_name, GRAY_INPUT_IMAGE_PATH_TO_SAVE);
    make_path_add_3_strings(sub_image_save_gray_path, HOME_PATH, user_name, SAVE_SUB_IMAGE_PATH);
    make_path_add_3_strings(distance_mat_save_path, HOME_PATH, user_name, SAVE_DISTANCE_MAT_PATH);
    make_path_add_3_strings(cases_save_path, HOME_PATH, user_name, CASES_PATH);
}


/**
 *@brief  Get reference to search unlabeled prototypes path 
 *@param  None
 *@retval reference to search unlabeled prototypes path 
 */
char *make_path_get_search_unlab_prot_path(void) {
    return search_unlab_prot_path;
}

/**
 *@brief  Get reference to save unlabeled gray prototypes path 
 *@param  None
 *@retval reference to save unlabeled gray prototypes path 
 */
char *make_path_get_save_unlab_prot_gray_path(void) {
    return save_unlab_prot_gray_path;
}

/**
 *@brief  Get reference to labeled prototypes path 
 *@param  None
 *@retval reference to labeled prototypes path 
 */
char *make_path_get_sorted_prot_path(void) {
    return sorted_prot_path;
}

/**
 *@brief  Get reference to search for input images path 
 *@param  None
 *@retval reference to search for input images path 
 */
char *make_path_get_input_image_read_path(void) {
    return input_image_read_path;
}

/**
 *@brief  Get reference to save input images gray path 
 *@param  None
 *@retval reference to save input images gray path 
 */
char *make_path_get_input_image_save_gray_path(void) {
    return input_image_save_gray_path;
}

/**
 *@brief  Get reference to save sub images gray path 
 *@param  None
 *@retval reference to save sub images gray path 
 */
char* make_path_get_sub_image_save_gray_path(void) {
    return sub_image_save_gray_path;
}

/**
 *@brief  Get reference to save Distance Matrix file path 
 *@param  None
 *@retval reference to save Distance Matrix file path 
 */
char *make_path_get_distance_mat_save_path(void) {
    return distance_mat_save_path;
}

/**
 *@brief  Get reference to save cases file path 
 *@param  None
 *@retval reference to save cases file path 
 */
char *make_path_get_cases_save_path(void) {
    return cases_save_path;
}

/**
 *@brief  Print all system file paths 
 *@param  None
 *@retval None
 */
void make_path_print_system_path(void) {
    printf("%s\n", make_path_get_search_unlab_prot_path());
    printf("%s\n", make_path_get_save_unlab_prot_gray_path());
    printf("%s\n", make_path_get_sorted_prot_path());
    printf("%s\n", make_path_get_input_image_read_path());
    printf("%s\n", make_path_get_input_image_save_gray_path());
    printf("%s\n", make_path_get_sub_image_save_gray_path());
    printf("%s\n", make_path_get_distance_mat_save_path());
    printf("%s\n", make_path_get_cases_save_path());
}
