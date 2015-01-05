/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this class allow for floating average filtering
 * @file filt_floating_avg.h
 */

#include "mbed.h"

#ifndef FILT_FLOATING_AVG_H_
#define FILT_FLOATING_AVG_H_

template <size_t length> class filt_floating_avg
{
public:
    filt_floating_avg() : m_buf_idx(0) { }
    
    double get() const
    {
        double sum = 0.0;
        for(size_t i = 0; i < m_buf_idx; i++)
        {
            sum += m_buffer[i];
        }
        return (sum/(double)(length));
    }
    
    void update(double const val)
    {
        m_buffer[m_buf_idx] = val;
        m_buf_idx++;
        if(m_buf_idx == length) m_buf_idx = 0;        
    }

private:
    double m_buffer[length];
    size_t m_buf_idx;
};

#endif