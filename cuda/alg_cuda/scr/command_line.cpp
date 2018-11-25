/**
  ******************************************************************************
  * @file    command_line.cpp
  * @author  alexb
  * @brief   command_line
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

#include <stdio.h>
#include <string.h>
#include <command_line.h>
#include <definitions.h>

/**
 *@brief  Private variables
 */
static char user_name[FILE_NAME_MAX_LENGTH];      /*!< user name array      */
static char distance_type[FILE_NAME_MAX_LENGTH];  /*!< distance name array  */
static char algorithm_type[FILE_NAME_MAX_LENGTH]; /*!< algorithm name array */
static int comm_line_sub_image_width = SUB_IMAGE_WIDTH;
static int comm_line_sub_image_height = SUB_IMAGE_HEIGHT;
/**
 *@brief  Set user name string 
 *@param  name: user name string
 *@retval None
 */
void comm_line_set_user_name(char *name) {
    strcpy(user_name, name);
}

/**
 *@brief  Set distance name string 
 *@param  name: distance name string
 *@retval None
 */
void comm_line_set_distance_type(char *name) {
    strcpy(distance_type, name);
}

/**
 *@brief  Set algorithm name string 
 *@param  name: algorithm name string
 *@retval None
 */
void comm_line_set_algorithm_type(char *name) {
    strcpy(algorithm_type, name);
}

/**
 *@brief  Set sub-image width
 *@param  val: sub-image width
 *@retval None
 */
void comm_line_set_sub_image_width(int val) {
	if(val < comm_line_sub_image_width){
		comm_line_sub_image_width = val;
	}
}

/**
 *@brief  Set sub-image height
 *@param  val: sub-image height
 *@retval None
 */
void comm_line_set_sub_image_height(int val) {
	if(val < comm_line_sub_image_height){
		comm_line_sub_image_height = val;
	}
}
/**
 *@brief  Get reference to user name string 
 *@param  None
 *@retval reference to user name string 
 */
char *comm_line_get_user_name(void) {
    return user_name;
}

/**
 *@brief  Get reference to distance name string 
 *@param  None
 *@retval reference to distance name string 
 */
char *comm_line_get_distance_type(void) {
    return distance_type;
}

/**
 *@brief  Get reference to algorithm name string 
 *@param  None
 *@retval reference to algorithm name string 
 */
char *comm_line_get_algorithm_type(void) {
    return algorithm_type;
}

/**
 *@brief  get sub-image width
 *@param  None
 *@retval sub-image width
 */
int comm_line_get_sub_image_width(void) {
	return comm_line_sub_image_width;
}

/**
 *@brief  get sub-image height
 *@param  None
 *@retval sub-image height
 */
int comm_line_get_sub_image_height(void) {
	return comm_line_sub_image_height;
}
