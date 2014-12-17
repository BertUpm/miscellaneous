/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this class estimates the current heading based on the data of a pololu min imu 9 v2
 * @file heading_estimator.cpp
 */

#include "heading_estimator.h"

/**
 * @brief Constructor
 */
heading_estimator::heading_estimator(double const sample_time_ms) : m_heading(0.0), m_sample_time_ms(sample_time_ms), m_gyro_z_avg_drift(0.0)
{
    m_gyro_z_filt = new filt_floating_avg<MIN_DATA_SAMPLES_FOR_CALIB>();
}


/**
 * @brief calibrates the sensor - returns true when fully calibrated
 */
bool heading_estimator::calib(float const gx, float const gy, float const gz, float const ax, float const ay, float const az, float const mx, float const my, float const mz)
{
    static int data_sample_cnt = 0;

    if(data_sample_cnt > MIN_DATA_SAMPLES_FOR_CALIB) 
    {
        // perform calibration
        m_gyro_z_avg_drift = m_gyro_z_filt->get();
        // cleanup the unused filters
        delete m_gyro_z_filt; m_gyro_z_filt = 0;
        // calibration is complete
        return true;
    } 
    else 
    {
        // sample the values in the filter
        if(m_gyro_z_filt) m_gyro_z_filt->update(gz);
        // update counter
        data_sample_cnt++;
        // calibration still uncomplete
        return false;
    }
}

/**
 * @brief updates the heading info after calibration is complete
 */
void heading_estimator::update(float const gz)
{
    m_heading += (gz - m_gyro_z_avg_drift) * (m_sample_time_ms/1000.0);
}