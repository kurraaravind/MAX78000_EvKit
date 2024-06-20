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
#include "i2c_test.h"
#include "i2c1.h"


/******************************************************************************/
int test_i2c_init(void)
{
	if(i2c_init() == 0){
		return 0;
	}
	else{
		return 1;
	}
}

/******************************************************************************/
int test_i2c_scan(void)
{
	if(i2c_scan()==0){
		return 0;
	}
	else{
		return 1;
	}

}
/******************************************************************************/
int test_i2c_write(void)
{
    uint8_t reg_addr = 0x40; 
    uint8_t data = 0xFF; // Declare and initialize the data variable
    if(i2c_write_register(device, reg_addr, &data, 1) == 0){
        return 0;
    }
    else{
        return 1;
    }
}
/******************************************************************************/
int test_i2c_read(void)
{
	uint8_t read_buff;
	uint8_t reg_addr = 0x00; 
    if(i2c_read_register(device, reg_addr, &read_buff, 1) == 0){
	    	if(read_buff == "D1"){
			return 0;
		}
	    	else{
			return 1;
		}
	}
	else{
		return 1;
	}
}
/******************************************************************************/
void test_i2c(void)
{
	int a = test_i2c_init();
	int b = test_i2c_scan();
	int c = test_i2c_write();
	int d = test_i2c_read();
	if(a == 0 && b == 0 && c == 0 && d == 0)
	{
		printf("All Test cases of I2C PASSED!\n");
	}
	else
	{
		printf("Test cases of I2C FAILED!\n");
	}
}

/******************************************************************************/
