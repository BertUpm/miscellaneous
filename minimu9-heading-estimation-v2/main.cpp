/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief main file for the minimu9 yaw estimation test project
 * @file main.cpp
 */

/* INCLUDE SECTION */

#include "L3GD20.h"
#include "LSM303DLHC.h"
#include "heading_estimator.h"

/* PROTOTYPE SECTION */

void init_application();
void set_min_imu_9_read_flag();
void print_heading();

/* GLOBAL CONSTANT SECTION */

static int const USB_UART_BAUDRATE = 115200;
static PinName const SDA = p9;
static PinName const SCL = p10;
static int const MIN_IMU_9_UPDATE_PERIOD_US = 5000; // 5 ms
static int const PRINT_HEADING_PERIOD_US = 100000; // 100 ms

/* GLOBAL VARIABLE SECTION */

Serial usb_uart(USBTX, USBRX);

L3GD20 gyro(SDA, SCL);
LSM303DLHC acc_mag(SDA, SCL);

Ticker min_imu_9_read_ticker;
Ticker usb_uart_ticker;

heading_estimator hdg_est(5.0);

static bool min_imu_9_read_flag = false;

/* CODE */

int main()
{
  
    init_application();
    
    for(;;) 
    {
        if(min_imu_9_read_flag) 
        {
            // clear read flag
            min_imu_9_read_flag = false;

            // read the values
            float gx = 0.0, gy = 0.0, gz = 0.0;
            bool const gyro_success = gyro.read(&gx, &gy, &gz);
        
            if(gyro_success)
            {
                hdg_est.update(gz);
            }    
        }
    }
}

/**
 * @brief intializes the application
 */
void init_application()
{
    // set baudrate to 115200
    usb_uart.baud(USB_UART_BAUDRATE);
    
    // wait 2 seconds so the sensor is lying still
    wait(2);

    // attach a ticker to regularly read data from the sensor
    min_imu_9_read_ticker.attach_us(&set_min_imu_9_read_flag, MIN_IMU_9_UPDATE_PERIOD_US);

    // attach a ticker to regularly write info to the output
    usb_uart_ticker.attach_us(&print_heading, PRINT_HEADING_PERIOD_US);

    // run the sensor calibration
    bool hdg_est_calib_complete = false;
    while(!hdg_est_calib_complete) 
    {
        if(min_imu_9_read_flag) 
        {
            // clear read flag
            min_imu_9_read_flag = false;

            // read the values
            float gx = 0.0, gy = 0.0, gz = 0.0;
            bool const gyro_success = gyro.read(&gx, &gy, &gz);

            float ax = 0.0, ay = 0.0, az = 0.0;
            float mx = 0.0, my = 0.0, mz = 0.0;
            bool const acc_mag_success = acc_mag.read(&ax, &ay, &az, &mx, &my, &mz);

            // perform the calibration
            if(gyro_success && acc_mag_success) 
            {
                hdg_est_calib_complete = hdg_est.calib(gx, gy, gz, ax, ay, az, mx, my, mz);
            }
        }
    }
}

/**
 * @brief sets the min_imu_9_read_flag resulting in a readout of the min imu 9 in the main loop
 */
void set_min_imu_9_read_flag()
{
    min_imu_9_read_flag = true;
}

/**
 * @brief prints the heading to the output if it yet available
 */
void print_heading()
{
    usb_uart.printf("hdg = %f\n", hdg_est.get_heading());
}