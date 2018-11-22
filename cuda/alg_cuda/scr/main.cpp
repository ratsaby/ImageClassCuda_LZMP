/*
 * main.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: alex
 */
#include <main.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <write_distance_mat_to_file.h>
#include <cat_list.h>
#include <definitions.h>
#include <command_line.h>
#include <ocv_functions.h>
#include <make_path.h>

/**
 *@brief  Private variables
 */
static img_file_name_t *names = NULL;           /*!< pointer to Images file names     */
static img_struct_t *main_img_list = NULL;      /*!< pointer to Images list           */
static img_struct_t *main_sub_img_list = NULL;  /*!< pointer to sub Images list       */
static img_struct_t *main_proto_list = NULL;    /*!< pointer to Images prototypes list*/

/**
 *@brief  Printing all nodes data in linked list 
 *@param  list: pointer to linked list,
 *        This parameter can be a value of @ref img_struct_t
 *@retval None
 */
void main_print_list(img_struct_t *list) {
    img_struct_t *current = list;

    while (current != NULL) {
        printf("nodeNum[%u] dataSize:%u width:%u height:%u fileName:%s\n",
                current->img_num, current->image_size, current->width,
                current->height, current->file_name);
        current = current->next;
    }
}

/**
 *@brief  Extract numbers from a string
 *@param  str: pointer to string
 *@param  number_p: pointer to numbers array
 *@param  number_buf_len: numbers buffer length
 *@retval true - found numbers, false - no numbers
 */
bool main_get_numbers_from_string(char* str, int* number_p, int number_buf_len) {
	int cnt = 0;

	printf("get numbers from string\n");
	while (*str) {
		if (isdigit(*str)) {
			long val = strtol(str, &str, 10);
			printf("%ld\n", val);
			number_p[cnt++] = (int)val;
			if(cnt == number_buf_len){
				return true;
			}
		} else {
			str++;
		}
	}
	return false;
}

/**
 *@brief  Extract data file names from a list and copy to array
 *@param  None
 *@retval true - success , false - not success
 */
bool main_names_from_images_list(void) {
    img_struct_t *current = main_img_list;
    int totalImages = current->img_num + 1;

    if (current == NULL) {
        printf("Empty image list\n");
        return false;
    }

    names = (img_file_name_t*) malloc(totalImages * sizeof (img_file_name_t));
    if (names == NULL) {
        printf("Can't allocate memory for image name\n");
        return false;
    }
    int img;
    while (current != NULL) {
        img = totalImages - current->img_num - 1; // first image in list is a last in array
        strcpy(names[img].file_name, current->file_name);
        current = current->next;
    }
    printf("names in buffer\n");
    for (int i = 0; i < totalImages; i++) {
        printf("[%d] name:%s\n", i, names[i].file_name);
    }
    return true;
}

/**
 *@brief  Free names pointer 
 *@param  None
 *@retval None
 */
void main_names_free_list(void) {
    free(names);
}

/**
 *@brief  Printing Command Line current parameters (help) 
 *@param  None
 *@retval None
 */
void main_print_help_commands(void) {
    printf("\n/***************************************************************/\n");
    printf("Use command line arguments: user_name distance_type algorithm_type sub_images_size\n");
    printf("user_name: is any user that work on the system\n");
    printf("distance_type: %s, %s, %s\n", DIST1, DIST2, DIST3);
    printf("algorithm_type: %s, %s\n", ALGORITHM2, ALGORITHM3);
    printf("sub_images_size: WidthxHeight\n");
    printf("/***************************************************************/\n");
}


/**
 *@brief  Execute all function of Algorithm2
 *@param  None
 *@retval None
 */
void main_app_alg2(void) {
    int totalImages;
    int totalSeqPair;

    printf("Starting Algorithm 2\n");
    ffiles_prototypes_sorted();
    main_img_list = ocv_get_ref_to_list();
    printf("\n extracting data from list\n");
    main_print_list(main_img_list);

    totalImages = main_img_list->img_num + 1;
    totalSeqPair = totalImages * totalImages;

    float* dMat = (float*) malloc(totalSeqPair * sizeof (float));
    assert(dMat != NULL);
    main_names_from_images_list();
    if (gpu_dist_mat_from_img_list(main_img_list, dMat, totalSeqPair)) {
        write_dist_to_file(dMat, totalImages, names);
    }
    main_names_free_list();
    free(dMat);
}

/**
 *@brief  Execute all function of Algorithm3
 *@param  None
 *@retval None
 */
void main_app_alg3(void) {
    printf("Starting Algorithm 3\n");

    ffiles_sub_imgs_sorted();
    main_sub_img_list = ocv_get_ref_to_subimgs_list();
    printf("\n extracting sub images from list\n");
    assert(main_sub_img_list != NULL);
    main_print_list(main_sub_img_list);

    ffiles_cat_prototypes();
    cat_list_print_list(cat_list_get_ref_to_list());
    cat_list_print_list(cat_list_get_ref_to_img_list());
    main_proto_list = ocv_get_ref_to_proto_list();
    printf("\n extracting prototypes from list\n");
    assert(main_proto_list != NULL);
    main_print_list(main_proto_list);

    int col = main_sub_img_list->img_num + 1;
    int row = main_proto_list->img_num + 1;
    int total_img = row * col;
    float* distMatGpu1D = (float*) malloc(total_img * sizeof (float));
    assert(distMatGpu1D != NULL);

    gpu_dist_mat_from_two_img_list(main_proto_list, main_sub_img_list,
            distMatGpu1D, total_img);
    if (strcmp(comm_line_get_distance_type(), DIST1) == 0) {
    	cat_list_euclidean_dist_to_cat(distMatGpu1D, row, col);
    } else if (strcmp(comm_line_get_distance_type(), DIST2) == 0) {
    	cat_list_ExplicitProtoDistInCase(distMatGpu1D, row, col);
    }else{
    	cat_list_ExplicitProtoDistInCase(distMatGpu1D, row, col);
    	cat_list_euclidean_dist_to_cat(distMatGpu1D, row, col);
    }
    free(distMatGpu1D);
}

/**
 *@brief  Main function
 *@param  argc: total members from command line
 *@param  argv: pointer to an array of strings
 *@retval int
 */
int main(int argc, char* argv[]) {
    if (argc > 5) {
        printf("Too many command line arguments, return\n");
        main_print_help_commands();
        return 0;
    } else if (argc == 1) {
        comm_line_set_user_name(DEFAULT_NAME);
        comm_line_set_distance_type(DEFAULT_DISTANCE_TYPE);
        comm_line_set_algorithm_type(DEFAULT_ALGORITHM_TYPE);
    } else if (argc == 2) {
        if (strcmp(argv[1], COMMAND_LINE_HELP) == 0) {
            main_print_help_commands();
            return 0;
        }
        comm_line_set_user_name(argv[1]);
        comm_line_set_distance_type(DEFAULT_DISTANCE_TYPE);
        comm_line_set_algorithm_type(DEFAULT_ALGORITHM_TYPE);
    } else if (argc == 3) {
        comm_line_set_user_name(argv[1]);
        if (strcmp(argv[2], DIST1) == 0 ||
        	strcmp(argv[2], DIST2) == 0 ||
        	strcmp(argv[2], DIST3) == 0) {
        	comm_line_set_distance_type(argv[2]);
        } else {
        	comm_line_set_distance_type(DEFAULT_DISTANCE_TYPE);
        }
        comm_line_set_algorithm_type(DEFAULT_ALGORITHM_TYPE);
    } else if (argc == 4) {
        comm_line_set_user_name(argv[1]);
        if (strcmp(argv[2], DIST1) == 0 ||
        	strcmp(argv[2], DIST2) == 0) {
        	comm_line_set_distance_type(argv[2]);
        } else {
        	comm_line_set_distance_type(DEFAULT_DISTANCE_TYPE);
        }
        if (strcmp(argv[3], ALGORITHM2) == 0 ||
        	strcmp(argv[3], ALGORITHM3) == 0) {
            comm_line_set_algorithm_type(argv[3]);
        } else {
            comm_line_set_algorithm_type(DEFAULT_ALGORITHM_TYPE);
        }
	} else {
		comm_line_set_user_name(argv[1]);
		if (strcmp(argv[2], DIST1) == 0 || strcmp(argv[2], DIST2) == 0) {
			comm_line_set_distance_type(argv[2]);
		} else {
			comm_line_set_distance_type(DEFAULT_DISTANCE_TYPE);
		}
		if (strcmp(argv[3], ALGORITHM2) == 0
				|| strcmp(argv[3], ALGORITHM3) == 0) {
			comm_line_set_algorithm_type(argv[3]);
		} else {
			comm_line_set_algorithm_type(DEFAULT_ALGORITHM_TYPE);
		}
		int num[2];
		if(main_get_numbers_from_string(argv[4], num, 2)){
			comm_line_set_sub_image_width(num[0]);
			comm_line_set_sub_image_height(num[1]);
		}
	}
    printf("using parameters\n");
    printf("user:%s\n", comm_line_get_user_name());
    printf("dist:%s\n", comm_line_get_distance_type());
    printf("algorithm:%s\n", comm_line_get_algorithm_type());
    printf("sub_images_size w:%d x h:%d\n", comm_line_get_sub_image_width(), comm_line_get_sub_image_height());
    printf("using system paths\n");
    make_path_all_system_path(comm_line_get_user_name());
    make_path_print_system_path();

    initTimer();
    startTimer();
    if (strcmp(comm_line_get_algorithm_type(), ALGORITHM2) == 0) {
        main_app_alg2();
    } else {
        main_app_alg3();
    }
    stopTimer();

    printf("end, time:%fms\n", getTimer());
    deleteTimer();
    printf("End of program\n");
}
