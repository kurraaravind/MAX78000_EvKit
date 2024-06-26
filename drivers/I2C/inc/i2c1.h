/**
 * @file       I2C1.h
 * @brief      I2C drivers.
 * @details    This driver can be used to access the I2C pins.
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
 
/* Define to prevent redundant inclusion */
#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/***** Includes *****/
#include <stdint.h>           // Standard integer types
#include <stddef.h>	      // Standard definitions
#include <stdio.h>            // Standard input/output functions 	
#include <string.h>           // String handling functions
#include "board.h"            // Board-specific definitions
#include "mxc_device.h"       // Device-specific definitions
#include "mxc_delay.h"        // Delay functions
#include "nvic_table.h"       // NVIC (Interrupt Controller) definitions
#include "mxc_errors.h"       // Error codes
#include "i2c.h"              // Include Maxim's I2C header

/***** Definitions *****/
#ifdef BOARD_EVKIT_V1
#define I2C_MASTER MXC_I2C2   // Define I2C2 as the master if using EVKIT_V1 board
#define I2C_SCL_PIN 30        // SCL pin number for I2C2
#define I2C_SDA_PIN 31        // SDA pin number for I2C2
#else
#define I2C_MASTER MXC_I2C1   // Define I2C1 as the master otherwise
#define I2C_SCL_PIN 16        // SCL pin number for I2C1
#define I2C_SDA_PIN 17        // SDA pin number for I2C1
#endif

#define I2C_FREQ 100000       // I2C frequency set to 100kHz
#define BMI160_CMD_REG 0x7E   //command register for BMI160
#define BMI160_PMU_STATUS_REG 0x03  // PMU status register for BMI160
#define BMI160_I2C_ADDR 0x69       //Device Address


/***** Function Prototypes *****/
/**
 * @brief      Initializes the I2C master interface
 *             Prints error message if initialization fails.
 * @return     return 0, If function is successful.
*/
int i2c_init(void);
/**
 * @brief      Scan for I2C slave devices on the bus.
 *             Setup the I2C frequency.
 * @return     return 0, If function is successful.
*/
int i2c_scan(void);
/**
 * @brief      Writes data to a specific register of an I2C slave device.
 * @param      address	     Address of the slave device.
 * @param      reg_adress    Address of the register to which writing to be done.
 * @param      data	     Pointer to the address of the data to be written in the Register address.
 * @param      length	     Length of the data to be written.
 * @return     return 0, If function is successful.
*/
int i2c_write_register(uint8_t address, uint8_t reg_adress, uint8_t* data, uint8_t length);
/**
 * @brief      Reads data from the specific register of an I2C slave device.
 * @param      address	     Address of the slave device.
 * @param      reg_adress    Address of the register from which reading to be done.
 * @param      buffer	     Pointer to the address of the buffer where reading is to be done.
 * @param      length	     Length of the buffer.
 * @return     return 0, If function is successful.
*/
int i2c_read_register(uint8_t address, uint8_t reg_adress, uint8_t* buffer, uint8_t length);
/**
 * @brief      Structure to hold BMI160 device information.
 *
 * This structure holds the necessary information for communicating with the BMI160
 * device over I2C. It includes the I2C address of the device, register addresses
 * for various functionalities, and a delay function pointer.
 */
struct bmi160_dev {
    uint8_t chip_id;                   // I2C address of the BMI160 device
    uint8_t gyro_self_test_enable_reg; // Register address to enable gyro self-test
    uint8_t gyro_self_test_status_reg; // Register address for gyro self-test status
    void (*delay_ms)(uint32_t);        // Pointer to delay function (optional)
};
/**
 * @brief      Sets the accelerometer to normal mode.
 *
 * This function sends the appropriate command to the BMI160 device to set the
 * accelerometer into normal operating mode.
 *
 * @param[in]  dev   Pointer to the device structure containing device information.
 *
 * @return     Returns 0 if the function is successful, non-zero error code otherwise.
 */
int set_accelerometer_normal_mode(struct bmi160_dev *dev);
/**
 * @brief      Checks the power mode status of the BMI160 accelerometer.
 *
 * This function reads the PMU status register of the BMI160 accelerometer to determine
 * its current power mode.
 *
 * @param[in]  dev    Pointer to the device structure containing device information.
 * @param[out] status Pointer to a variable where the power mode status will be stored.
 *
 * @return     Returns 0 if the function successfully reads the status, non-zero error code otherwise.
 */
int check_accelerometer_power_mode(struct bmi160_dev *dev, uint8_t *status);
/**
 * @brief      Sets the gyroscope to suspend mode.
 *
 * This function sends the appropriate command to the BMI160 device to set the
 * gyroscope into suspend mode.
 *
 * @param[in]  dev   Pointer to the device structure containing device information.
 *
 * @return     Returns 0 if the function is successful, non-zero error code otherwise.
 */
int set_gyroscope_Normal_mode(struct bmi160_dev *dev);
/**
 * @brief      Checks the power mode status of the BMI160 gyroscope.
 *
 * This function reads the PMU status register of the BMI160 gyroscope to determine
 * its current power mode.
 *
 * @param[in]  dev    Pointer to the device structure containing device information.
 * @param[out] status Pointer to a variable where the power mode status will be stored.
 *
 * @return     Returns 0 if the function successfully reads the status, non-zero error code otherwise.
 */
int check__gyroscope_power_mode(struct bmi160_dev *dev, uint8_t *status);
/**
 * @brief      Performs a software reset on the BMI160 sensor.
 *
 * This function sends the soft reset command to the BMI160 device and waits
 * for the reset to complete.
 *
 * @return     Returns 0 if the reset is successful, non-zero error code otherwise.
 */
int bmi160_softi_reset(void);
/**
 * @brief      Checks if the BMI160 sensor has been reset successfully.
 *
 * This function reads a register (e.g., INT_MAP register) after performing a soft reset
 * to verify if the reset was successful.
 *
 * @return     Returns 0 if the reset was verified successfully, -1 if verification failed.
 */
int check_bmi160_reset(void);
#ifdef __cplusplus
}
#endif

#endif // I2C_H
