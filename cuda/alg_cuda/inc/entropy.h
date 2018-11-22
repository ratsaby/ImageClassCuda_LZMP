/*
 * entropy.h
 *
 *  Created on: May 19, 2015
 *      Author: alex
 */

#ifndef ENTROPY_H_
#define ENTROPY_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

float entropy_single_case(float* ptr_case, size_t len);
void entropy_test(void);


#endif /* ENTROPY_H_ */
