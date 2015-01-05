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
    
    m_acc_x_filt = new filt_floating_avg<MIN_DATA_SAMPLES_FOR_CALIB>();
    m_acc_y_filt = new filt_floating_avg<MIN_DATA_SAMPLES_FOR_CALIB>();
    m_acc_z_filt = new filt_floating_avg<MIN_DATA_SAMPLES_FOR_CALIB>();
    
    m_mag_x_filt = new filt_floating_avg<MIN_DATA_SAMPLES_FOR_CALIB>();
    m_mag_y_filt = new filt_floating_avg<MIN_DATA_SAMPLES_FOR_CALIB>();
    m_mag_z_filt = new filt_floating_avg<MIN_DATA_SAMPLES_FOR_CALIB>();
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
        
        // retrieve gyro drift
        m_gyro_z_avg_drift = m_gyro_z_filt->get();
        
        // calculate heading based on mag and acc
        
        // normalise mag vector
        float const mag_x = m_mag_x_filt->get();    
        float const mag_y = m_mag_y_filt->get();
        float const mag_z = m_mag_z_filt->get();
        
        float const M = sqrt(pow(mag_x, 2) + pow(mag_y, 2) + pow(mag_z, 2));
        float const mx = mag_x / M;
        float const my = mag_y / M;
        float const mz = mag_z / M;
        
        // normalise acc vector
        
        float const acc_x = m_acc_x_filt->get();    
        float const acc_y = m_acc_y_filt->get();
        float const acc_z = m_acc_z_filt->get();
        
        float const A = sqrt(pow(acc_x, 2) + pow(acc_y, 2) + pow(acc_z, 2));
        float const ax = acc_x / A;
        float const ay = acc_x / A;

        // calc pitch and roll
        float const pitch = asin((-1.0) * ax);
        float roll = 0.0f;
        if ((fabs(pitch) - (M_PI / 2)) < 0.001) 
        { // pitch is 90 degrees
            roll = 0.0;
        } 
        else 
        {
            roll = asin(ay / cos(pitch));
        }
        
        // calc tilt compensated mag vector values
        float const mx2 = mx * cos(pitch) + mz * sin(pitch);
        float const my2 = mx * sin(roll) * sin(pitch) + my * cos(roll) - mz * sin(roll) * cos(pitch);
        
        // calculate the heading in radiant
        if (mx2 > 0 && my2 >= 0) 
        {
            m_heading = atan(my2 / mx2);
        } 
        else if (mx2 < 0) 
        {
            m_heading = (M_PI + atan(my2 / mx2));
        } 
        else if (mx2 > 0 && my2 <= 0)
        {
            m_heading = (2 * M_PI + atan(my2 / mx2));
        } 
        else if (mx2 == 0 && my2 < 0) 
        {
            m_heading = (M_PI / 2.0);
        } 
        else if (mx2 == 0 && my2 > 0) 
        {
            m_heading = (M_PI + atan(my2 / mx2));
        } 
        else 
        {
            m_heading = 0.0f;
        }
        
        // convert from rad to deg
        m_heading *= 180.0f/M_PI;
        
        // cleanup the unused filters
        delete m_gyro_z_filt; m_gyro_z_filt = 0;
        
        delete m_acc_x_filt; m_acc_x_filt = 0;
        delete m_acc_y_filt; m_acc_y_filt = 0;
        delete m_acc_z_filt; m_acc_z_filt = 0;
        
        delete m_mag_x_filt; m_mag_x_filt = 0;
        delete m_mag_y_filt; m_mag_y_filt = 0;
        delete m_mag_z_filt; m_mag_z_filt = 0;
        
        // calibration is complete
        return true;
    } 
    else 
    {
        // sample the values in the filter
        if(m_gyro_z_filt) m_gyro_z_filt->update(gz);
        
        if(m_acc_x_filt) m_acc_x_filt->update(ax);
        if(m_acc_y_filt) m_acc_y_filt->update(ay);
        if(m_acc_z_filt) m_acc_z_filt->update(az);
        
        if(m_mag_x_filt) m_mag_x_filt->update(mx);
        if(m_mag_y_filt) m_mag_y_filt->update(my);
        if(m_mag_z_filt) m_mag_z_filt->update(mz);
        
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