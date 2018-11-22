#ifndef DIST_CALCULATE_H
#define DIST_CALCULATE_H

/**
 *@brief  Compute single distance value from sequence pair LZ-complexity
 *        This function can be called for Host(CPU) or from Device(GPU) 
 *@param  c1: first LZ-complexity value
 *@param  c2: second LZ-complexity value
 *@param  c12: concatenation LZ-complexity value
 *@retval distance value 
 */
#ifdef __CUDACC__
__host__ __device__
#endif
float dist_calc_val(int c1, int c2, int c12);

#endif
