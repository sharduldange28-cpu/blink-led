#include "main.h"
#include <math.h>

ADC_HandleTypeDef hadc1;

uint32_t adc_value;
float voltage;
float resistance;
float temperature;

// Constants
#define VREF        3.3
#define ADC_MAX     4095.0
#define R_FIXED     10000.0     // 10k resistor
#define BETA        3950.0      // NTC beta value
#define T0          298.15      // 25°C in Kelvin
#define R0          10000.0     // 10k at 25°C

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_ADC1_Init();

    while (1)
    {
        // Start ADC
        HAL_ADC_Start(&hadc1);

        // Wait for conversion
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

        // Read ADC
        adc_value = HAL_ADC_GetValue(&hadc1);

        // Convert ADC → Voltage
        voltage = (adc_value * VREF) / ADC_MAX;

        // Voltage divider formula → find NTC resistance
        resistance = (R_FIXED * voltage) / (VREF - voltage);

        // Beta equation → Temperature (Kelvin)
        temperature = 1 / ((1/T0) + (1/BETA) * log(resistance/R0));

        // Convert Kelvin → Celsius
        temperature = temperature - 273.15;

        HAL_Delay(500);
    }
}
