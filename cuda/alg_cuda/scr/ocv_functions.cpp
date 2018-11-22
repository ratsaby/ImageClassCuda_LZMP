
#include <ocv_functions.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <command_line.h>

/**
 *@brief  Private variables
 */
static img_struct_t *list = NULL; /*!< pointer to input images linked list*/
static img_struct_t *sub_img_list = NULL; /*!< pointer to sub images linked list*/
static img_struct_t *proto_list = NULL; /*!< pointer to prototypes linked list*/


/**
 *@brief  Destroy all opened windows by OpenCV 
 *@param  None
 *@retval None
 */
void destroyAllWindows(void) {
    cvDestroyAllWindows();
}

/**
 *@brief  Get reference to input images linked list
 *@param  None
 *@retval reference to input images linked list
 *        This parameter can be value of @ref img_struct_t
 */
img_struct_t *ocv_get_ref_to_list(void) {
    return list;
}

/**
 *@brief  Get reference to sub images linked list
 *@param  None
 *@retval reference to sub images linked list
 *        This parameter can be value of @ref img_struct_t
 */
img_struct_t *ocv_get_ref_to_subimgs_list(void) {
    return sub_img_list;
}

/**
 *@brief  Get reference to prototypes linked list
 *@param  None
 *@retval reference to prototypes linked list
 *        This parameter can be value of @ref img_struct_t
 */
img_struct_t* ocv_get_ref_to_proto_list(void) {
    return proto_list;
}


/**
 *@brief  Push to sorted linked list (first will be last in list)
 *@param  headRef: double pointer do head list
 *@param  data: pointer to image data
 *@param  dataSize: image data size
 *@param  imgNum: image current number
 *@param  width: image width
 *@param  height: image height
 *@param  fileName: pointer to file name string
 *@retval None
 */
void push_to_list(img_struct_t **headRef, char *data, int dataSize, int imgNum, int width, int height, char* fileName) {
    img_struct_t *newNode = (img_struct_t*) malloc(sizeof (img_struct_t));

    if (newNode == NULL) {
        printf("PushToList:Could not allocate memory space\n");
        assert(false);
    }
    assert(dataSize < sizeof (newNode->img_data));
    printf("nodeNum[%u] dataSize:%u width:%u height:%u\n", imgNum, dataSize, width, height);

    memcpy(newNode->img_data, data, dataSize);
    strcpy(newNode->file_name, fileName);
    newNode->img_num = imgNum;
    newNode->image_size = dataSize;
    newNode->width = width;
    newNode->height = height;
    newNode->next = *headRef;
    *headRef = newNode;
}

/**
 *@brief  Push image data to sorted linked list 
 *        This function use OpenCV lib to convert image to gray and extract data 
 *@param  img_path: pointer to string path
 *@param  name: pointer to string image name
 *@retval 0 - success , -1 - not success 
 */
int ocv_push_img_to_list(char *img_path, char *name) {
    char newFilePath[2 * 256];
    char newFileName[256];
    char cat[256];
    char full_path_to_file_category[256];
    static int nodeNum = 0;

    make_path_add_strings(newFilePath, img_path, name);
    IplImage* img_gray = cvLoadImage(newFilePath, CV_LOAD_IMAGE_GRAYSCALE);
    if (img_gray == NULL) {
        printf("OcvError:Can't open image path or image bad extension\n");
        return -1;
    }

    make_path_category_from_path(name, cat);
    make_path_add_strings(full_path_to_file_category, make_path_get_sorted_prot_path(), cat);
    printf("path to category:%s\n", full_path_to_file_category);
    if (mkdir(full_path_to_file_category, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
        printf("path to category created\n");
    }

    make_path_add_postfix_to_image(newFileName, POSTFIX_TO_FILE_TO_SAVE, name);
    char* ptr = strchr(full_path_to_file_category, '\0');
    strcpy(ptr, newFileName);
    cvSaveImage(full_path_to_file_category, img_gray);

    make_path_add_strings(newFilePath, make_path_get_save_unlab_prot_gray_path(), newFileName);
    mkdir(make_path_get_save_unlab_prot_gray_path(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    printf("Save image GrayScale:%s\n", newFilePath);
    cvSaveImage(newFilePath, img_gray);

    int img_size = img_gray->width * img_gray->height;
    push_to_list(&list, img_gray->imageData, img_size, nodeNum, img_gray->width,
            img_gray->height, newFileName);

    cvReleaseImage(&img_gray);
    nodeNum++;
    return 0;
}


/**
 *@brief  Cut image to sub images with a given dimensions 
 *        and push image data to sorted linked list 
 *        This function use OpenCV lib to convert image to gray, extract data, split 
 *@param  img: pointer to image
 *        This parameter can be a value of @ref IplImage 
 *@param  roi_size: sub image dimension
 *        This parameter can be a value of @ref CvSize 
 *@param  save_file_path: pointer to save path string
 *@retval number of sub images 
 */
int ocv_split_image_dim_save_to_list(IplImage *img, CvSize roi_size, char *save_file_path) {
    CvRect roi;
    CvSize size;
    IplImage* img_to_list;
    int r, c;
    char new_save_file_path[256];
    char postfix_save_file_path[256];
    int i;
    int img_size;
    int current_img_num = 0;
    static int img_num = 0;

    i = 0;
    size = cvGetSize(img);
    printf("img size.height:%d\n", size.height);
    printf("img size.width:%d\n", size.width);

    for (r = 0; r < size.height; r += roi_size.height) {
        for (c = 0; c < size.width; c += roi_size.width) {
            roi.x = c;
            roi.y = r;
            roi.width = (c + roi_size.width > size.width) ? (size.width - c) : roi_size.width;
            roi.height = (r + roi_size.height > size.height) ? (size.height - r) : roi_size.height;
            cvSetImageROI(img, roi);
            make_path_add_postfix_to_image(postfix_save_file_path, POSTFIX_TO_SUB_IMAGE_TO_SAVE, save_file_path);
            make_path_add_int_postfix_to_image(new_save_file_path, i, postfix_save_file_path);
            cvSaveImage(new_save_file_path, img);
            img_to_list = cvLoadImage(new_save_file_path, CV_LOAD_IMAGE_GRAYSCALE);
            //	        make_path_add_int_postfix_to_image(postfix_save_file_path_temp, i*2, new_save_file_path);
            //	        cvSaveImage(postfix_save_file_path_temp, img_to_list);
            assert(img_to_list != NULL);
            img_size = img_to_list->width * img_to_list->height;
            push_to_list(&sub_img_list, img_to_list->imageData, img_size, img_num, img_to_list->width, img_to_list->height, new_save_file_path);
            cvReleaseImage(&img_to_list);
            current_img_num++;
            img_num++;
            i++;
        }
    }
    cvResetImageROI(img);
    return current_img_num;
}


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
void ocv_split_image_dim(IplImage *img, CvSize roi_size, char *save_file_path) {
    CvRect roi;
    CvSize size;
    int r, c;
    char new_save_file_path[256];
    char postfix_save_file_path[256];
    int i = 0;

    size = cvGetSize(img);
    printf("img size.height:%d\n", size.height);
    printf("img size.width:%d\n", size.width);

    for (r = 0; r < size.height; r += roi_size.height) {
        for (c = 0; c < size.width; c += roi_size.width) {
            roi.x = c;
            roi.y = r;
            roi.width = (c + roi_size.width > size.width) ? (size.width - c) : roi_size.width;
            roi.height = (r + roi_size.height > size.height) ? (size.height - r) : roi_size.height;
            cvSetImageROI(img, roi);
            make_path_add_postfix_to_image(postfix_save_file_path, POSTFIX_TO_SUB_IMAGE_TO_SAVE, save_file_path);
            make_path_add_int_postfix_to_image(new_save_file_path, i, postfix_save_file_path);
            cvSaveImage(new_save_file_path, img);
            i++;
        }
    }
    cvResetImageROI(img);
}

/**
 *@brief  Calculate best split dimension (sub image dimensions)
 *@param  None
 *@retval sub image dimensions
 *        This parameter can be a value of @ref CvSize
 */
CvSize ocv_get_best_size_for_split(void) {
    CvSize best_size;
    int array;

    best_size.width = comm_line_get_sub_image_width();
    best_size.height = comm_line_get_sub_image_height();
    array = best_size.width * best_size.height;
    printf("best_size.width:%d best_size.height:%d\n", best_size.width, best_size.height);
    assert(array < MAX_ARRAY_SIZE);
    return best_size;
}

/**
 *@brief  Push sub images of a given image to sorted linked list 
 *        This function use OpenCV lib to convert image to gray, extract data, split 
 *@param  input_img_path: pointer to image path
 *@param  name: pointer to string file name 
 *@retval 0 - success , -1 - not success 
 */
int ocv_push_sub_imgs_to_list(char *input_img_path, char *name) {
    CvSize roi;
    char newFilePath[FILE_NAME_MAX_LENGTH];
    char path_to_save_input_image[FILE_NAME_MAX_LENGTH];
    char full_path_to_save_input_image[FILE_NAME_MAX_LENGTH];
    char path_to_save_subimage_image[FILE_NAME_MAX_LENGTH];
    char full_path_to_save_subimage_image[FILE_NAME_MAX_LENGTH];
    int sub_images;

    make_path_add_strings(newFilePath, input_img_path, name);
    IplImage* img_gray = cvLoadImage(newFilePath, CV_LOAD_IMAGE_GRAYSCALE);
    if (img_gray == NULL) {
        printf("OcvError:Can't open image path or image bad extension\n");
        return -1;
    }

    strcpy(path_to_save_input_image, make_path_get_input_image_save_gray_path());
    if (mkdir(path_to_save_input_image, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
        printf("path to gray input image created\n");
    }
    make_path_add_strings(full_path_to_save_input_image, path_to_save_input_image, name);
    cvSaveImage(full_path_to_save_input_image, img_gray);

    if (mkdir(make_path_get_distance_mat_save_path(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
        printf("path to sub image created\n");
    }

    roi = ocv_get_best_size_for_split();
    strcpy(path_to_save_subimage_image, make_path_get_sub_image_save_gray_path());
    make_path_add_strings(full_path_to_save_subimage_image, path_to_save_subimage_image, name);
    sub_images = ocv_split_image_dim_save_to_list(img_gray, roi, full_path_to_save_subimage_image);
    cvReleaseImage(&img_gray);

    return sub_images;
}

/**
 *@brief  Push prototypes images to sorted linked list 
 *        This function use OpenCV lib to convert image to gray, extract data
 *@param  input_proto_path: pointer to prototype image path
 *@param  name: pointer to string file name 
 *@retval 0 - success , -1 - not success 
 */
int ocv_push_proto_to_list(char *input_proto_path, char *name) {
    char full_path[FILE_NAME_MAX_LENGTH];
    int img_size;
    static int proto_num = 0;

    make_path_add_strings(full_path, input_proto_path, name);
    printf("proto path:%s\n", full_path);
    IplImage* img = cvLoadImage(full_path, CV_LOAD_IMAGE_GRAYSCALE);
    if (img == NULL) {
        printf("OcvError:Can't open image path or image bad extension\n");
        return -1;
    }
    img_size = img->width * img->height;
    push_to_list(&proto_list, img->imageData, img_size, proto_num, img->width, img->height, name);
    cvReleaseImage(&img);
    proto_num++;

    return 0;
}
