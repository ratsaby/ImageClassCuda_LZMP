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
