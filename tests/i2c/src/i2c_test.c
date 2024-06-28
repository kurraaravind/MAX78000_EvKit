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
int test_i2c_write(void) {
    uint8_t reg_addr = 0x40;
    uint8_t write_data = 0xFF;
    uint8_t read_data = 0;

    // Write data to the register
    if (i2c_write_register(device, reg_addr, &write_data, 1) != 0) {
        return 1; // Write failed
    }

    // Read back data from the same register
    if (i2c_read_register(device, reg_addr, &read_data, 1) != 0) {
        return 1; // Read failed
    }

    // Compare the written and read data
    if (read_data == write_data) {
        return 0; // Test passed
    } else {
        return 1; // Test failed
    }
}
/******************************************************************************/
int test_i2c_read(void) {
    uint8_t read_buff;
    uint8_t reg_addr = 0x00;
    uint8_t expected_value = 0xD1;

    int result = i2c_read_register(device, reg_addr, &read_buff, 1);
    if (result == E_NO_ERROR) {
        // Compare the read value with the expected value
        if (read_buff == expected_value) {
            printf("Test passed: Read value 0x%02X matches expected value 0x%02X\n", read_buff, expected_value);
            return 0; // Test passed
        } else {
            printf("Test failed: Read value 0x%02X does not match expected value 0x%02X\n", read_buff, expected_value);
            return 1; // Test failed
        }
    } else {
        printf("I2C read failed with error code: %d\n", result);
        return 1; // Test failed due to I2C error
    }
}
/******************************************************************************/
int test_i2c_Accelerometer_normal_mode(void){
    struct bmi160_dev dev;
    dev.chip_id = 0x69; //  I2C address of the BMI160 device
    dev.delay_ms = NULL; // Delay function
	if(set_accelerometer_normal_mode(&dev) == 0){
		return 0;
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
	int e = test_i2c_Accelerometer_normal_mode();
	if(a == 0 && b == 0 && c == 0 && d == 0 && e == 0)
	{
		printf("All Test cases of I2C PASSED!\n");
	}
	else
	{
		printf("Test cases of I2C FAILED!\n");
	}
}

/******************************************************************************/
