#ifndef SOFTTIMER_HPP
#define SOFTTIMER_HPP

#include "stm32f1xx_hal.h"

class SoftTimer
{
private:
    uint32_t m_interval;
    uint32_t m_lastTick;

public:
    SoftTimer() : m_interval(0), m_lastTick(0)
    {
    }

    SoftTimer(uint32_t interval)
        : m_interval(interval), m_lastTick(HAL_GetTick())
    {
    }

    void setInterval(uint32_t interval)
    {
        m_interval = interval;
        m_lastTick = HAL_GetTick();
    }

    bool check()
    {
        if (m_interval == 0) {
            return false;
        }

        uint32_t now = HAL_GetTick();

        if ((now - m_lastTick) >= m_interval)
        {
            m_lastTick = now;
            return true;
        }

        return false;
    }

    void reset()
    {
        m_lastTick = HAL_GetTick();
    }
};

#endif
