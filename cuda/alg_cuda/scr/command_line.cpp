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
