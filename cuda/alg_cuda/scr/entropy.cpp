/*
 * entropy.cpp
 *
 *  Created on: May 19, 2015
 *      Author: alex
 */
#include <entropy.h>
#include <stdint.h>
#include <math.h>

static bool from_test;

float entropy_single_case(float* ptr_case, size_t len){
	double entrp = 0;

	for(size_t i = 0; i < len; i++){
		if(from_test){
			printf("%f ", ptr_case[i]);
		}
		if(ptr_case[i] != 0){
			entrp -= ((double)ptr_case[i])*(log(ptr_case[i]) / log(2));
		}
	}

	return (float)entrp;
}

void entropy_test(void){
	float normal_count[] = {
			0.90,
			0,
			0.10,
			0,
			0
	};

	from_test = true;
	size_t n_len = sizeof(normal_count) / sizeof(normal_count[0]);
	printf("starting entropy test len:%d\n", n_len);
	printf("entropy:%f\n", entropy_single_case(normal_count, n_len));
	from_test = false;
}


