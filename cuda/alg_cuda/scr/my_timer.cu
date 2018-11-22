/**
 ******************************************************************************
 * @file    my_timer.cu
 * @author  Alexander Belousov
 * @version V1.0.0
 * @date    09/24/2014
 * @brief   Device timer functions
 ****************************************************************************** 
 */

#include <helper_functions.h> // helper utility functions
#include <helper_cuda.h>      // helper functions for CUDA error checking and initialization


/**
 *@brief  Private variables
 */
StopWatchInterface *hTm = NULL; /*!< pointer to timer in helper utility    */

/**
 *@brief  Init timer
 *@param  None
 *@retval None
 */
void initTimer(void) {
    sdkCreateTimer(&hTm);
}

/**
 *@brief  Start timer
 *@param  None
 *@retval None
 */
void startTimer(void) {
    sdkResetTimer(&hTm);
    sdkStartTimer(&hTm);
}

/**
 *@brief  Stop timer
 *@param  None
 *@retval None
 */
void stopTimer(void) {
    sdkStopTimer(&hTm);
}

/**
 *@brief  Get timer
 *@param  None
 *@retval timer value in ms
 */
float getTimer(void) {
    return sdkGetTimerValue(&hTm);
}

/**
 *@brief  Delete timer
 *@param  None
 *@retval None
 */
void deleteTimer(void) {
    sdkDeleteTimer(&hTm);
}
