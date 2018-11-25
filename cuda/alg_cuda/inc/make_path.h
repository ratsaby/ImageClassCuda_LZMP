/**
  ******************************************************************************
  * @file    make_path.h
  * @author  alexb
  * @brief   Header file containing functions prototypes of make_path
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

#ifndef _MAKE_PATH_H
#define _MAKE_PATH_H

#include <stdio.h>
#include <string.h>

/**
 *@brief  Copy category name from a given file name 
 *@param  image_name: pointer to a file name string
 *@param  category: pointer to a category string that name of category will be copied to
 *@retval None
 */
void make_path_category_from_path(char *image_name, char *category);


/**
 *@brief  Copy string from the beginning of a given string to a given separator
 *@param  copy_to_str: pointer to string that copy to 
 *@param  copy_from_str: string from start copy
 *@param  separator: character where to should stop copy
 *@retval None
 */
void make_path_copy_string_to_separator(char *copy_to_str, char *copy_from_str, char separator);


/**
 *@brief  Add a postfix to a given file name
 *@param  new_file_name: pointer to string that copy to 
 *@param  postfix: string that would be added to a given file name
 *@param  old_file_name: pointer to string that copy from 
 *@retval None
 */
void make_path_add_postfix_to_image(char *new_file_name, char *postfix, char *old_file_name);
    

/**
 *@brief  Add a integer postfix to a given file name
 *@param  new_file_name: pointer to string that copy to 
 *@param  val: integer value that would be added to a given file name
 *@param  old_file_name: pointer to string that copy from 
 *@retval None
 */
void make_path_add_int_postfix_to_image(char *new_file_name, int val, char *old_file_name);
    

/**
 *@brief  Remove spaces in a given file name
 *@param  str: pointer to a string 
 *@retval None
 */
void make_path_remove_spaces(char *str);
    

/**
 *@brief  Replace a character in a given string
 *@param  str: pointer to a string 
 *@param  find: find character that should replace
 *@param  replace: replace by a given character  
 *@retval true - success , false - not success
 */
bool make_path_change_chr(char* str, char find, char replace);


/**
 *@brief  Add two strings and copy to new one
 *@param  new_str: pointer to new string 
 *@param  old_str: pointer to old string 
 *@param  add_str: pointer to string that should to add
 *@retval None
 */
void make_path_add_strings(char *new_str, char *old_str, char *add_str);
    

/**
 *@brief  Add three strings and copy to new one
 *@param  new_str: pointer to new string 
 *@param  str1: pointer to first string 
 *@param  str2: pointer to second string
 *@param  str3: pointer to third string
 *@retval None
 */
void make_path_add_3_strings(char* new_str, char* str1, char* str2, char* str3);


/**
 *@brief  Add a user name strings to all system paths
 *@param  user_name: pointer to user name string 
 *@retval None
 */
void make_path_all_system_path(char *user_name);
    

/**
 *@brief  Get reference to search unlabeled prototypes path 
 *@param  None
 *@retval reference to search unlabeled prototypes path 
 */
char *make_path_get_search_unlab_prot_path(void);


/**
 *@brief  Get reference to save unlabeled gray prototypes path 
 *@param  None
 *@retval reference to save unlabeled gray prototypes path 
 */
char *make_path_get_save_unlab_prot_gray_path(void);


/**
 *@brief  Get reference to labeled prototypes path 
 *@param  None
 *@retval reference to labeled prototypes path 
 */
char *make_path_get_sorted_prot_path(void);


/**
 *@brief  Get reference to search for input images path 
 *@param  None
 *@retval reference to search for input images path 
 */
char *make_path_get_input_image_read_path(void);


/**
 *@brief  Get reference to save input images gray path 
 *@param  None
 *@retval reference to save input images gray path 
 */
char *make_path_get_input_image_save_gray_path(void);


/**
 *@brief  Get reference to save sub images gray path 
 *@param  None
 *@retval reference to save sub images gray path 
 */
char* make_path_get_sub_image_save_gray_path(void);


/**
 *@brief  Get reference to save Distance Matrix file path 
 *@param  None
 *@retval reference to save Distance Matrix file path 
 */
char *make_path_get_distance_mat_save_path(void);


/**
 *@brief  Get reference to save cases file path 
 *@param  None
 *@retval reference to save cases file path 
 */
char *make_path_get_cases_save_path(void);


/**
 *@brief  Print all system file paths 
 *@param  None
 *@retval None
 */
void make_path_print_system_path(void);

#endif // _MAKE_PATH_H
