 #include "i2c1.h"             // Include the I2C driver header file
 
// Initialize the I2C master interface
int i2c_init(void) {
    int error = MXC_I2C_Init(I2C_MASTER, 1, 0);    // Initialize I2C with the defined master interface
    if (error != E_NO_ERROR) {
        printf("-->I2C Master Initialization failed, error:%d\n", error); // Print error message if initialization fails
        return 1;
    } else {
        printf("\n-->I2C Master Initialization Complete\n");
        return 0;
    }
}

// Scan for I2C slave devices on the bus
int i2c_scan(void) {
    printf("-->Scanning started\n");
    MXC_I2C_SetFrequency(I2C_MASTER, I2C_FREQ);      // Set the I2C frequency
    mxc_i2c_req_t reqMaster;                         // Create an I2C request structure for the scan
    reqMaster.i2c = I2C_MASTER;
    reqMaster.addr = 0;
    reqMaster.tx_buf = NULL;
    reqMaster.tx_len = 0;
    reqMaster.rx_buf = NULL;
    reqMaster.rx_len = 0;
    reqMaster.restart = 0;
    reqMaster.callback = NULL;
    
    int found = 0; // Flag to check if any device is found
    // Scan all possible addresses (0 to 127)
    for (uint8_t address = 0; address < 128; address++) {
        printf(".");
        fflush(0);

        reqMaster.addr = address;
        if ((MXC_I2C_MasterTransaction(&reqMaster)) == 0) {
            printf("\nFound slave ID %03d; 0x%02X\n", address, address);
            found = 1; // Set flag to indicate a device is found
        }
        MXC_Delay(MXC_DELAY_MSEC(200));             // Delay for 200 milliseconds 
    }
       if (found) {
        return 0; // At least one device was found
    } else {
        return 1; // No devices found
    }
}


// Write data to a specific register of an I2C slave device
int i2c_write_register(uint8_t address, uint8_t reg_address, uint8_t* data, uint8_t length) {
    uint8_t write_buf[length + 1];          // Buffer to hold register address and data
    write_buf[0] = reg_address;             // First byte is the register address
    
    // Copy data to be written into the buffer
    if (data != NULL) {
        memcpy(&write_buf[1], data, length); // Copy data to be written
    } else {
        length = 0; // No data to write
    }
    
    // Print the data being written for debugging
    printf("Writing to address 0x%02X, register 0x%02X, data: ", address, reg_address);
    for (int i = 0; i < length; i++) {
        printf("0x%02X ", data[i]);
    }
    printf("\n");
    
    // Create an I2C request structure for the write operation
    mxc_i2c_req_t req;
    req.i2c = I2C_MASTER;
    req.addr = address;
    req.tx_buf = write_buf;
    req.tx_len = length + 1;
    req.rx_buf = NULL;
    req.rx_len = 0;
    req.restart = 0;
    req.callback = NULL;

    return MXC_I2C_MasterTransaction(&req); // Perform the I2C write transaction
}

// Read data from a specific register of an I2C slave device
int i2c_read_register(uint8_t address, uint8_t reg_address, uint8_t* buffer, uint8_t length) {
    printf("Setting register address 0x%02X for reading\n", reg_address);
    
    // Create an I2C request structure to set the register address for reading
    mxc_i2c_req_t req;
    req.i2c = I2C_MASTER;
    req.addr = address;
    req.tx_buf = &reg_address;
    req.tx_len = 1;
    req.rx_buf = NULL;
    req.rx_len = 0;
    req.restart = 1; // Restart without sending stop condition
    req.callback = NULL;
    
    // Perform the write transaction to set the register address
    int ret = MXC_I2C_MasterTransaction(&req);
    if (ret != E_NO_ERROR) {
        printf("I2C write (register address) error: %d\n", ret);
        return ret;
    }
    
    // Modify the request structure for the read operation
    req.tx_buf = NULL;
    req.tx_len = 0;
    req.rx_buf = buffer;
    req.rx_len = length;
    req.restart = 0; // No restart, complete the transaction

    ret = MXC_I2C_MasterTransaction(&req);
    if (ret != E_NO_ERROR) {
        printf("I2C read error: %d\n", ret);
        return ret;
    }
    printf("\n");
    // Print the data being read for debugging
    printf("Read from address 0x%02X, register 0x%02X, data: ", address, reg_address);
    for (int i = 0; i < length; i++) {
        printf("0x%02X ", buffer[i]);
    }
    printf("\n");

    return ret;
}
//Setting the accelerometer to Normal mode
int set_accelerometer_normal_mode(struct bmi160_dev *dev)
{
    uint8_t cmd = 0x11; // Command to set accelerometer to normal mode
    return i2c_write_register(dev->chip_id, BMI160_CMD_REG, &cmd, 1);
}
// Checking the Power mode
int check_accelerometer_power_mode(struct bmi160_dev *dev, uint8_t *status)
{
    // Perform an I2C read operation to read the PMU status register
    // The result will be stored in the 'status' variable
    int result = i2c_read_register(dev->chip_id, BMI160_PMU_STATUS_REG, status, 1);
    
    // Return the result of the I2C read operation
    return result;
}
// Function to set gyroscope to Normal mode
int set_gyroscope_Normal_mode(struct bmi160_dev *dev)
{
    uint8_t cmd = 0x15; // Command to set Gyroscope to normal mode
    int result = i2c_write_register(dev->chip_id, BMI160_CMD_REG, &cmd, 1);
    if (result != 0) {
        return result;
    }

    // Optional delay after sending the command to ensure the device has time to switch modes
    if (dev->delay_ms) {
        dev->delay_ms(15); // Delay for 10ms
    }

    return 0;
}
// Checking the Power mode
int check__gyroscope_power_mode(struct bmi160_dev *dev, uint8_t *status)
{
    // Perform an I2C read operation to read the PMU status register
    // The result will be stored in the 'status' variable
    int result = i2c_read_register(dev->chip_id, BMI160_PMU_STATUS_REG, status, 1);
    // Return the result of the I2C read operation
    return result;
}
//Soft Reset of CMD_REG
int bmi160_softi_reset(void)
{
    // BMI160 soft reset command
    uint8_t cmd = 0xB6; // Soft reset command for BMI160
    printf("Writing to address 0x%02X, register 0x%02X, data: 0x%02X\n", BMI160_I2C_ADDR, BMI160_CMD_REG, cmd);

    int result = i2c_write_register(BMI160_I2C_ADDR, BMI160_CMD_REG, &cmd, 1);
    if (result != E_NO_ERROR)
    {
        printf("Failed to perform soft reset, error: %d\n", result);
        return result;
    }

    // Delay to allow the reset to complete
    MXC_Delay(MXC_DELAY_MSEC(100));

    printf("Soft reset performed successfully.\n");
    return E_NO_ERROR;
}
//Checks whether register Reset or Not
int check_bmi160_reset(void)
{
    uint8_t reg_value;
    int result = i2c_read_register(BMI160_I2C_ADDR, BMI160_CMD_REG, &reg_value, 1);
    if (result != E_NO_ERROR)
    {
        printf("Failed to read PMU_STATUS register, error: %d\n", result);
        return result;
    }

    // Compare with the default value expected after a soft reset
    if (reg_value == 0x00)
    { 
        printf("Soft reset verified: CMD_Register = 0x%02X\n", reg_value);
        return E_NO_ERROR;
    }
    else
    {
        printf("Soft reset failed or not verified: INT_MAP = 0x%02X\n", reg_value);
        return -1;
    }
}
