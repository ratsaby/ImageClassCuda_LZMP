/**
  ******************************************************************************
  * @file    command_line.cpp
  * @author  alexb
  * @brief   Header file containing functions prototypes of command_line
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

#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

/**
 *@brief  Set user name string 
 *@param  name: user name string
 *@retval None
 */
void comm_line_set_user_name(char *name);

/**
 *@brief  Set distance name string 
 *@param  name: distance name string
 *@retval None
 */
void comm_line_set_distance_type(char *name);

/**
 *@brief  Set algorithm name string 
 *@param  name: algorithm name string
 *@retval None
 */
void comm_line_set_algorithm_type(char *name);


void comm_line_set_sub_image_width(int val);
void comm_line_set_sub_image_height(int val);

/**
 *@brief  Get reference to user name string 
 *@param  None
 *@retval reference to user name string 
 */
char *comm_line_get_user_name(void);

/**
 *@brief  Get reference to distance name string 
 *@param  None
 *@retval reference to distance name string 
 */
char *comm_line_get_distance_type(void);

/**
 *@brief  Get reference to algorithm name string 
 *@param  None
 *@retval reference to algorithm name string 
 */
char *comm_line_get_algorithm_type(void);

/**
 *@brief  get sub-image width
 *@param  None
 *@retval sub-image width
 */
int comm_line_get_sub_image_width(void);

/**
 *@brief  get sub-image height
 *@param  None
 *@retval sub-image height
 */
int comm_line_get_sub_image_height(void);

#endif //COMMAND_LINE_H
