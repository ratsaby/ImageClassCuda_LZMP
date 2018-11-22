#ifndef _OCV_FUNCTIONS_H
#define _OCV_FUNCTIONS_H

#include <iostream>
#include <cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/flann/miniflann.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/calib3d/calib3d.hpp>
//#include "opencv2/ml/ml.hpp"
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>

#include <make_path.h>
#include <img_types.h>
#include <definitions.h>

/**
 *@brief  Destroy all opened windows by OpenCV 
 *@param  None
 *@retval None
 */
void destroyAllWindows(void);

/**
 *@brief  Get reference to input images linked list
 *@param  None
 *@retval reference to input images linked list
 *        This parameter can be value of @ref img_struct_t
 */
img_struct_t *ocv_get_ref_to_list(void);


/**
 *@brief  Get reference to sub images linked list
 *@param  None
 *@retval reference to sub images linked list
 *        This parameter can be value of @ref img_struct_t
 */
img_struct_t *ocv_get_ref_to_subimgs_list(void);


/**
 *@brief  Get reference to prototypes linked list
 *@param  None
 *@retval reference to prototypes linked list
 *        This parameter can be value of @ref img_struct_t
 */
img_struct_t *ocv_get_ref_to_proto_list(void);


/**
 *@brief  Push image data to sorted linked list 
 *        This function use OpenCV lib to convert image to gray and extract data 
 *@param  img_path: pointer to string path
 *@param  name: pointer to string image name
 *@retval 0 - success , -1 - not success 
 */
int ocv_push_img_to_list(char *img_path, char *name);


/**
 *@brief  Push sub images of a given image to sorted linked list 
 *        This function use OpenCV lib to convert image to gray, extract data, split 
 *@param  input_img_path: pointer to image path
 *@param  name: pointer to string file name 
 *@retval 0 - success , -1 - not success 
 */
int ocv_push_sub_imgs_to_list(char *input_img_path, char *name);


/**
 *@brief  Push prototypes images to sorted linked list 
 *        This function use OpenCV lib to convert image to gray, extract data
 *@param  input_proto_path: pointer to prototype image path
 *@param  name: pointer to string file name 
 *@retval 0 - success , -1 - not success 
 */
int ocv_push_proto_to_list(char *input_proto_path, char *name);


/**
 *@brief  Cut image to sub images and save gray sub image files 
 *        This function use OpenCV lib to convert image to gray, extract data, split 
 *@param  img: pointer to image
 *        This parameter can be a value of @ref IplImage 
 *@param  roi_size: sub image dimension
 *        This parameter can be a value of @ref CvSize 
 *@param  save_file_path: pointer to save path string
 *@retval None
 */
void ocv_split_image_dim(IplImage *img, int roi_width, int roi_height);


#endif //  _OCV_FUNCTIONS_H
