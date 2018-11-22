/**
 ******************************************************************************
 * @file    dist.cu
 * @author  Alexander Belousov
 * @version V1.0.0
 * @date    09/24/2014
 * @brief   Host and Device functions
 ****************************************************************************** 
 */

#include "dist.h"


#define max_val(val1, val2) (val1 > val2 ? val1:val2) /*!< max. val from val1 and val2*/
#define min_val(val1, val2) (val1 < val2 ? val1:val2) /*!< min. val from val1 and val2*/


/**
 *@brief  Compute single distance value from sequence pair LZ-complexity
 *        This function can be called for Host(CPU) or from Device(GPU) 
 *@param  c1: first LZ-complexity value
 *@param  c2: second LZ-complexity value
 *@param  c12: concatenation LZ-complexity value
 *@retval distance value 
 */
float __host__ __device__ dist_calc_val(int c1, int c2, int c12){
	return ((float)(c12 - min_val(c1, c2))/max_val(c1, c2));
}

