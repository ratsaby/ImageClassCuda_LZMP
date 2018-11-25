/**
  ******************************************************************************
  * @file    write_distance_mat_to_file.cpp
  * @author  alexb
  * @brief   write_distance_mat_to_file
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
#include <write_distance_mat_to_file.h>
#include <make_path.h>

#include <string.h>
#include <ctime>

/**
 *@brief  Write Distance Matrix to file
 *@param  dist: pointer to Distances array
 *@param  rows: number of members in array
 *@param  name: pointer to string names
 *        This parameter can be a value of @ref img_file_name_t
 *@retval true - success , false - not success
 */
bool write_dist_to_file(float* dist, int rows, img_file_name_t* name){
	FILE* f;
	img_file_name_t categ_name[rows];
	int index1D;
	char write_file[256];

	// current date/time based on current system
    time_t now = time(0);
	// convert now to string form
	char* dt = ctime(&now);

	char* ptr;
	strcpy(write_file, make_path_get_distance_mat_save_path());
	ptr = strchr(write_file, '\0');
	strcpy(ptr, FILE_DIST_NAME);
	ptr = strchr(write_file, '\0');
	strcpy(ptr, "_");
	ptr = strchr(write_file, '\0');
	strcpy(ptr, dt);
	ptr = strchr(write_file, '\0');
	strcpy(ptr, FILE_DIST_NAME_EXT);
	make_path_remove_spaces(write_file);
	char find = '\n';
	char replace = '_';

	make_path_change_chr(write_file, find, replace);

	f = fopen(write_file, "w");
	printf("Write data to file: %s\n", write_file);
	if(f == NULL){
		printf("can't create a file\n");
		return false;
	}
	printf("Copy time to file:%s", dt);
	fprintf(f, "%s", dt);

	printf("Copy names to file\n");
	for(int i = 0; i < rows; i++){
		//strcpy(categ_name[i].fileName, name[i].fileName);
		printf("%s ", name[i].file_name);
		fprintf(f, "%s ", name[i].file_name);
	}
	printf("\n");
	fprintf(f, "\n");

	printf("Copy category names to file\n");
	for(int i = 0; i < rows; i++){
		make_path_category_from_path(name[i].file_name, categ_name[i].file_name);
		printf("%s ", categ_name[i].file_name);
		fprintf(f, "%s ", categ_name[i].file_name);
	}
	printf("\n");
	fprintf(f, "\n");

	printf("Copy distance matrix to file\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			index1D = i + j*rows;
			fprintf(f, "%f ", dist[index1D]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
	printf("write data to file - Complete\n");

	return true;
}
