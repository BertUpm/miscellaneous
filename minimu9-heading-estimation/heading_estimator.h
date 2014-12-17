/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this class estimates the current heading based on the data of a pololu min imu 9 v2
 * @file heading_estimator.h
 */

#ifndef HEADING_ESTIMATOR_H_
#define HEADING_ESTIMATOR_H_

#include "mbed.h"
#include "filt_floating_avg.h"

class heading_estimator
{
public:
    /**
     * @brief Constructor
     */
    heading_estimator(double const sample_time_ms);

    /**
     * @brief calibrates the sensor - returns true when fully calibrated
     */
    bool calib(float const gx, float const gy, float const gz, float const ax, float const ay, float const az, float const mx, float const my, float const mz);

    /**
     * @brief updates the heading info after calibration is complete
     */
    void update(float const gz);

    /**
     * @brief returns the heading
     */
    inline float get_heading() const {
        return m_heading;
    }

    static size_t const MIN_DATA_SAMPLES_FOR_CALIB = 256;
    
private:
    double m_heading;
    double m_sample_time_ms;

    float m_gyro_z_avg_drift;
    
    filt_floating_avg<MIN_DATA_SAMPLES_FOR_CALIB> *m_gyro_z_filt;    
};

#endif