/**
  ******************************************************************************
  * @file    ffiles.h
  * @author  alexb
  * @brief   Header file containing functions prototypes of ffiles
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
