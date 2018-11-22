#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/**
 *@brief  Command line option Algorithms
 */
#define ALGORITHM2                         "alg2" /*!< Command line option Algorithm2*/
#define ALGORITHM3                         "alg3" /*!< Command line option Algorithm3*/

/**
 *@brief  Command line option Distance type
 */
#define DIST1                         "eucl" /*!< Command line option Algorithm2*/
#define DIST2                         "expl" /*!< Command line option Algorithm3*/
#define DIST3					      "both"
/**
 *@brief  Default Command line options 
 */
#define DEFAULT_NAME                       "alex" /*!< Default Command line option user name*/
#define DEFAULT_DISTANCE_TYPE              DIST3 /*!< Default Command line option distance*/
#define DEFAULT_ALGORITHM_TYPE             ALGORITHM3 /*!< Default Command line option algorithm*/


/**
 *@brief  Command line option Help
 */
#define COMMAND_LINE_HELP                  "-help" /*!< Command line option Help*/

/**
 *@brief  System paths
 */
#define HOME_PATH 			   "/home/"
#define SEARCH_PATH_FOLDER                 "/Pictures/CUDAImageRuns/1.UnlabImagePrototypes/"
#define GRAY_IMAGE_PATH_TO_SAVE            "/Pictures/CUDAImageRuns/1.UnlabImagePrototypes/gray/"
#define IMAGE_PATH_SORTED_PROT             "/Pictures/CUDAImageRuns/2.LabImagePrototypes/"
#define INPUT_IMAGE_PATH                   "/Pictures/CUDAImageRuns/3.InputImageFolder/"
#define GRAY_INPUT_IMAGE_PATH_TO_SAVE      "/Pictures/CUDAImageRuns/3.InputImageFolder/gray/"
#define SAVE_SUB_IMAGE_PATH                "/Pictures/CUDAImageRuns/TEMP/"
#define SAVE_DISTANCE_MAT_PATH             "/Pictures/CUDAImageRuns/"
#define CASES_PATH                         "/Pictures/CUDAImageRuns/4.LearningCases/"


/**
 *@brief  definitions
 */
#define SEARCH_FILE_EXTENSIONS_IN_FOLDER   "jpg"
#define PREFIX_TO_FILE_TO_SAVE             "gray_"
#define POSTFIX_TO_FILE_TO_SAVE            "_gray"
#define POSTFIX_TO_SUB_IMAGE_TO_SAVE       "_sub_"
#define SAVE_DISTANCE_MAT_FILE             "CUDA_DIST_MAT"
#define SAVE_DISTANCE_MAT_FILE_EXTENSION   ".txt"
#define SAVE_CASES_FILE   				   "CUDA_CASES"
#define SAVE_CASES_FILE_EXTENSION	 	   ".dat"

#define SEPERATOR                          "/"
#define SEPERATOR2                         ", "
#define SEPERATOR3                         "\""
#define	TARGET_CLASS  			   "target class"
#define	TARGET_CLASS_FILE_NAME         	   "imageFileName"

#define FILE_NAME_MAX_LENGTH               0xff

#define SUB_IMAGE_WIDTH                    150
#define SUB_IMAGE_HEIGHT                   150

#define MAX_STRING_SIZE_IN_BYTES           24000
#if(MAX_STRING_SIZE_IN_BYTES < 100)
#define USE_DEBUG_MODE
#endif

#define MAX_ARRAY_SIZE                     MAX_STRING_SIZE_IN_BYTES
#define MAX_SEQUENCE_ARRAY_SIZE            (2 * MAX_ARRAY_SIZE)
#define MAX_THREADS_PER_BLOCK              1024

#endif // DEFINITIONS_H
