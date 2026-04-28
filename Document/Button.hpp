#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "stm32f1xx_hal.h"

class Button
{
private:
    GPIO_TypeDef* m_port;
    uint16_t m_pin;

    bool m_lastState;
    uint32_t m_lastDebounceTime;
    const uint32_t DEBOUNCE_DELAY = 50; // Chống dội 50ms

public:
    Button(GPIO_TypeDef* port, uint16_t pin)
        : m_port(port), m_pin(pin), m_lastState(false), m_lastDebounceTime(0)
    {
    }

    bool isPressed()
    {
        // Đọc mức 0 (RESET) vì nút nhấn nối GND
        bool currentState = (HAL_GPIO_ReadPin(m_port, m_pin) == GPIO_PIN_RESET);

        if (currentState != m_lastState)
        {
            if ((HAL_GetTick() - m_lastDebounceTime) > DEBOUNCE_DELAY)
            {
                m_lastDebounceTime = HAL_GetTick();
                m_lastState = currentState;

                if (currentState == true)
                {
                    return true; // Chỉ trả về true 1 lần khi bắt đầu nhấn xuống
                }
            }
        }
        return false;
    }
};

#endif
