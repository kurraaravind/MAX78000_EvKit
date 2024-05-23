/**
 * @file        main.c
 * @brief       GPIO Example
 * @details	Toggling the LED's on P0.2 and P0.3 GPIO pins 
 */

/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. All Rights Reserved.
 * (now owned by Analog Devices, Inc.),
 * Copyright (C) 2023 Analog Devices, Inc. All Rights Reserved. This software
 * is proprietary to Analog Devices, Inc. and its licensors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

/***** Includes *****/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "gpio1.h"

int main(void)
{
	while(1)
	{
		gpio_set(0,2,1);	// Setting P0.2(Port0 Pin2) to High
		gpio_set(0,3,1);	// setting P0.3(Port0 Pin3) to High
        	MXC_Delay(1000000);	// Delay of mS
		gpio_set(0,2,0);	// Setting P0.2(Port0 Pin2) to Low
		gpio_set(0,3,0);	// Setting P0.3(Port0 Pin3) to Low
        	MXC_Delay(1000000);	// Delay of 
	}
    return 0;
}
