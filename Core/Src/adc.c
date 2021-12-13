#include "adc.h"

uint16 ADC_CH6_Raw;
uint16 ADC_CH7_Raw;
uint16 ADC_BATT_Raw;
uint16 ADC_CPU_Raw;
uint16 ADC_CH6_Volt;
uint16 ADC_CH7_Volt;
uint16 ADC_BATT_Volt;
uint16 ADC_CPU_Volt;

void Adc_Read(void)
{
    HAL_ADC_Start(&hadc1);
    if(HAL_OK == HAL_ADC_PollForConversion(&hadc1,10))
    {
        ADC_CH6_Raw = HAL_ADC_GetValue(&hadc1);
    }
    HAL_ADC_Start(&hadc1);
    if(HAL_OK == HAL_ADC_PollForConversion(&hadc1,10))
    {
        ADC_CH7_Raw = HAL_ADC_GetValue(&hadc1);
    }
    HAL_ADC_Start(&hadc3);
    if(HAL_OK == HAL_ADC_PollForConversion(&hadc3,10))
    {
        ADC_BATT_Raw = HAL_ADC_GetValue(&hadc3);
    }
    HAL_ADC_Start(&hadc3);
    if(HAL_OK == HAL_ADC_PollForConversion(&hadc3,10))
    {
        ADC_CPU_Raw = HAL_ADC_GetValue(&hadc3);
    }
    return;
}

void Adc_Calc(void)
{
    ADC_CH6_Volt = (uint16)((float)ADC_CH6_Raw*5000.0f/65535.0f);
    ADC_CH7_Volt = (uint16)((float)ADC_CH7_Raw*5000.0f/65535.0f);
    ADC_BATT_Volt = (uint16)((float)ADC_BATT_Raw*3300.0f/65535.0f);
    ADC_CPU_Volt = (uint16)((float)ADC_CPU_Raw*3300.0f/65535.0f);
}