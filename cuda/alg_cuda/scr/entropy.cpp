/**
  ******************************************************************************
  * @file    entropy.cpp
  * @author  alexb
  * @brief   entropy
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015, Alexander Belousov and Joel Ratsaby All rights reserved.</center></h2>
  *
  * LICENSE CONDITIONS
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Ariel University nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
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


