#ifndef ADCIN_HPP
#define ADCIN_HPP

#include "stm32f1xx_hal.h"

class AdcIn
{
private:
    ADC_HandleTypeDef* m_hadc;

public:
    AdcIn(ADC_HandleTypeDef* hadc)
        : m_hadc(hadc)
    {
    }

    uint16_t readValue()
    {
        uint16_t value = 0;

        // 1. Khởi động bộ chuyển đổi ADC
        HAL_ADC_Start(m_hadc);

        // 2. Chờ chuyển đổi hoàn tất (Timeout 10ms)
        if (HAL_ADC_PollForConversion(m_hadc, 10) == HAL_OK)
        {
            // 3. Đọc giá trị
            value = HAL_ADC_GetValue(m_hadc);
        }

        // 4. Dừng ADC
        HAL_ADC_Stop(m_hadc);

        return value;
    }
};

#endif
