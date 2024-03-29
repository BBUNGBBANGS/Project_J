#include "stdint.h"
#include "main.h"
#include "os.h"
#include "mqtt_interface.h"

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

extern void __libc_init_array();

void Reset_Handler()
{
    uint32_t *dataInit = &_sidata;
    uint32_t *data = &_sdata;
    while (data < &_edata)
    {
        *data++ = *dataInit++;
    }

    uint32_t *bss = &_sbss;
    while (bss < &_ebss)
    {
        *bss++ = 0;
    }

    SystemInit();
    __libc_init_array();
    main();

    while (1);
}

void Default_Handler(void) 
{
    while (1);
}

void TIM15_Handler(void)
{
    HAL_TIM_IRQHandler(&htim15);
}

void TIM16_Handler(void)
{
    HAL_TIM_IRQHandler(&htim16);
}

void TIM17_Handler(void)
{
    HAL_TIM_IRQHandler(&htim17);
}

void USART1_Handler(void)
{
    HAL_UART_IRQHandler(&huart1);
}

void UART4_Handler(void)
{
    HAL_UART_IRQHandler(&huart4);
}

void SystemTick_Handler(void)
{
    /* USER CODE BEGIN SysTick_IRQn 0 */

    /* USER CODE END SysTick_IRQn 0 */
    HAL_IncTick();
    MilliTimer++;
    /* USER CODE BEGIN SysTick_IRQn 1 */
    /* USER CODE END SysTick_IRQn 1 */
}
__weak void NMI_Handler(void)                                             {Default_Handler();}
__weak void HardFault_Handler(void)                                       {Default_Handler();}
__weak void MemManage_Handler(void)                                       {Default_Handler();}
__weak void BusFault_Handler(void)                                        {Default_Handler();}
__weak void UsageFault_Handler(void)                                      {Default_Handler();}
__weak void SVC_Handler(void)                                             {Default_Handler();}
__weak void DebugMon_Handler(void)                                        {Default_Handler();}
__weak void PendSV_Handler(void)                                          {Default_Handler();}
__weak void SysTick_Handler(void)                                         {SystemTick_Handler();}
__weak void WWDG_IRQHandler(void)                                         {Default_Handler();}
__weak void PVD_AVD_IRQHandler(void)                                      {Default_Handler();}
__weak void TAMP_STAMP_IRQHandler(void)                                   {Default_Handler();}
__weak void RTC_WKUP_IRQHandler(void)                                     {Default_Handler();}
__weak void FLASH_IRQHandler(void)                                        {Default_Handler();}
__weak void RCC_IRQHandler(void)                                          {Default_Handler();}
__weak void EXTI0_IRQHandler(void)                                        {Default_Handler();}
__weak void EXTI1_IRQHandler(void)                                        {Default_Handler();}
__weak void EXTI2_IRQHandler(void)                                        {Default_Handler();}
__weak void EXTI3_IRQHandler(void)                                        {Default_Handler();}
__weak void EXTI4_IRQHandler(void)                                        {Default_Handler();}
__weak void DMA1_Stream0_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA1_Stream1_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA1_Stream2_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA1_Stream3_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA1_Stream4_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA1_Stream5_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA1_Stream6_IRQHandler(void)                                 {Default_Handler();}
__weak void ADC_IRQHandler(void)                                          {Default_Handler();}
__weak void FDCAN1_IT0_IRQHandler(void)                                   {Default_Handler();}
__weak void FDCAN2_IT0_IRQHandler(void)                                   {Default_Handler();}
__weak void FDCAN1_IT1_IRQHandler(void)                                   {Default_Handler();}
__weak void FDCAN2_IT1_IRQHandler(void)                                   {Default_Handler();}
__weak void EXTI9_5_IRQHandler(void)                                      {Default_Handler();}
__weak void TIM1_BRK_IRQHandler(void)                                     {Default_Handler();}
__weak void TIM1_UP_IRQHandler(void)                                      {Default_Handler();}
__weak void TIM1_TRG_COM_IRQHandler(void)                                 {Default_Handler();}
__weak void TIM1_CC_IRQHandler(void)                                      {Default_Handler();}
__weak void TIM2_IRQHandler(void)                                         {Default_Handler();}
__weak void TIM3_IRQHandler(void)                                         {Default_Handler();}
__weak void TIM4_IRQHandler(void)                                         {Default_Handler();}
__weak void I2C1_EV_IRQHandler(void)                                      {Default_Handler();}
__weak void I2C1_ER_IRQHandler(void)                                      {Default_Handler();}
__weak void I2C2_EV_IRQHandler(void)                                      {Default_Handler();}
__weak void I2C2_ER_IRQHandler(void)                                      {Default_Handler();}
__weak void SPI1_IRQHandler(void)                                         {Default_Handler();}
__weak void SPI2_IRQHandler(void)                                         {Default_Handler();}
__weak void USART1_IRQHandler(void)                                       {USART1_Handler();}
__weak void USART2_IRQHandler(void)                                       {Default_Handler();}
__weak void USART3_IRQHandler(void)                                       {Default_Handler();}
__weak void EXTI15_10_IRQHandler(void)                                    {Default_Handler();}
__weak void RTC_Alarm_IRQHandler(void)                                    {Default_Handler();}
__weak void TIM8_BRK_TIM12_IRQHandler(void)                               {Default_Handler();}
__weak void TIM8_UP_TIM13_IRQHandler(void)                                {Default_Handler();}
__weak void TIM8_TRG_COM_TIM14_IRQHandler(void)                           {Default_Handler();}
__weak void TIM8_CC_IRQHandler(void)                                      {Default_Handler();}
__weak void DMA1_Stream7_IRQHandler(void)                                 {Default_Handler();}
__weak void FMC_IRQHandler(void)                                          {Default_Handler();}
__weak void SDMMC1_IRQHandler(void)                                       {Default_Handler();}
__weak void TIM5_IRQHandler(void)                                         {Default_Handler();}
__weak void SPI3_IRQHandler(void)                                         {Default_Handler();}
__weak void UART4_IRQHandler(void)                                        {UART4_Handler();}
__weak void UART5_IRQHandler(void)                                        {Default_Handler();}
__weak void TIM6_DAC_IRQHandler(void)                                     {Default_Handler();}
__weak void TIM7_IRQHandler(void)                                         {Default_Handler();}
__weak void DMA2_Stream0_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA2_Stream1_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA2_Stream2_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA2_Stream3_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA2_Stream4_IRQHandler(void)                                 {Default_Handler();}
__weak void ETH_IRQHandler(void)                                          {Default_Handler();}
__weak void ETH_WKUP_IRQHandler(void)                                     {Default_Handler();}
__weak void FDCAN_CAL_IRQHandler(void)                                    {Default_Handler();}
__weak void DMA2_Stream5_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA2_Stream6_IRQHandler(void)                                 {Default_Handler();}
__weak void DMA2_Stream7_IRQHandler(void)                                 {Default_Handler();}
__weak void USART6_IRQHandler(void)                                       {Default_Handler();}
__weak void I2C3_EV_IRQHandler(void)                                      {Default_Handler();}
__weak void I2C3_ER_IRQHandler(void)                                      {Default_Handler();}
__weak void OTG_HS_EP1_OUT_IRQHandler(void)                               {Default_Handler();}
__weak void OTG_HS_EP1_IN_IRQHandler(void)                                {Default_Handler();}
__weak void OTG_HS_WKUP_IRQHandler(void)                                  {Default_Handler();}
__weak void OTG_HS_IRQHandler(void)                                       {Default_Handler();}
__weak void DCMI_IRQHandler(void)                                         {Default_Handler();}
__weak void RNG_IRQHandler(void)                                          {Default_Handler();}
__weak void FPU_IRQHandler(void)                                          {Default_Handler();}
__weak void UART7_IRQHandler(void)                                        {Default_Handler();}
__weak void UART8_IRQHandler(void)                                        {Default_Handler();}
__weak void SPI4_IRQHandler(void)                                         {Default_Handler();}
__weak void SPI5_IRQHandler(void)                                         {Default_Handler();}
__weak void SPI6_IRQHandler(void)                                         {Default_Handler();}
__weak void SAI1_IRQHandler(void)                                         {Default_Handler();}
__weak void LTDC_IRQHandler(void)                                         {Default_Handler();}
__weak void LTDC_ER_IRQHandler(void)                                      {Default_Handler();}
__weak void DMA2D_IRQHandler(void)                                        {Default_Handler();}
__weak void SAI2_IRQHandler(void)                                         {Default_Handler();}
__weak void QUADSPI_IRQHandler(void)                                      {Default_Handler();}
__weak void LPTIM1_IRQHandler(void)                                       {Default_Handler();}
__weak void CEC_IRQHandler(void)                                          {Default_Handler();}
__weak void I2C4_EV_IRQHandler(void)                                      {Default_Handler();}
__weak void I2C4_ER_IRQHandler(void)                                      {Default_Handler();}
__weak void SPDIF_RX_IRQHandler(void)                                     {Default_Handler();}
__weak void OTG_FS_EP1_OUT_IRQHandler(void)                               {Default_Handler();}
__weak void OTG_FS_EP1_IN_IRQHandler(void)                                {Default_Handler();}
__weak void OTG_FS_WKUP_IRQHandler(void)                                  {Default_Handler();}
__weak void OTG_FS_IRQHandler(void)                                       {Default_Handler();}
__weak void DMAMUX1_OVR_IRQHandler(void)                                  {Default_Handler();}
__weak void HRTIM1_Master_IRQHandler(void)                                {Default_Handler();}
__weak void HRTIM1_TIMA_IRQHandler(void)                                  {Default_Handler();}
__weak void HRTIM1_TIMB_IRQHandler(void)                                  {Default_Handler();}
__weak void HRTIM1_TIMC_IRQHandler(void)                                  {Default_Handler();}
__weak void HRTIM1_TIMD_IRQHandler(void)                                  {Default_Handler();}
__weak void HRTIM1_TIME_IRQHandler(void)                                  {Default_Handler();}
__weak void HRTIM1_FLT_IRQHandler(void)                                   {Default_Handler();}
__weak void DFSDM1_FLT0_IRQHandler(void)                                  {Default_Handler();}
__weak void DFSDM1_FLT1_IRQHandler(void)                                  {Default_Handler();}
__weak void DFSDM1_FLT2_IRQHandler(void)                                  {Default_Handler();}
__weak void DFSDM1_FLT3_IRQHandler(void)                                  {Default_Handler();}
__weak void SAI3_IRQHandler(void)                                         {Default_Handler();}
__weak void SWPMI1_IRQHandler(void)                                       {Default_Handler();}
__weak void TIM15_IRQHandler(void)                                        {TIM15_Handler();}
__weak void TIM16_IRQHandler(void)                                        {TIM16_Handler();}
__weak void TIM17_IRQHandler(void)                                        {TIM17_Handler();}
__weak void MDIOS_WKUP_IRQHandler(void)                                   {Default_Handler();}
__weak void MDIOS_IRQHandler(void)                                        {Default_Handler();}
__weak void JPEG_IRQHandler(void)                                         {Default_Handler();}
__weak void MDMA_IRQHandler(void)                                         {Default_Handler();}
__weak void SDMMC2_IRQHandler(void)                                       {Default_Handler();}
__weak void HSEM1_IRQHandler(void)                                        {Default_Handler();}
__weak void ADC3_IRQHandler(void)                                         {Default_Handler();}
__weak void DMAMUX2_OVR_IRQHandler(void)                                  {Default_Handler();}
__weak void BDMA_Channel0_IRQHandler(void)                                {Default_Handler();}
__weak void BDMA_Channel1_IRQHandler(void)                                {Default_Handler();}
__weak void BDMA_Channel2_IRQHandler(void)                                {Default_Handler();}
__weak void BDMA_Channel3_IRQHandler(void)                                {Default_Handler();}
__weak void BDMA_Channel4_IRQHandler(void)                                {Default_Handler();}
__weak void BDMA_Channel5_IRQHandler(void)                                {Default_Handler();}
__weak void BDMA_Channel6_IRQHandler(void)                                {Default_Handler();}
__weak void BDMA_Channel7_IRQHandler(void)                                {Default_Handler();}
__weak void COMP1_IRQHandler(void)                                        {Default_Handler();}
__weak void LPTIM2_IRQHandler(void)                                       {Default_Handler();}
__weak void LPTIM3_IRQHandler(void)                                       {Default_Handler();}
__weak void LPTIM4_IRQHandler(void)                                       {Default_Handler();}
__weak void LPTIM5_IRQHandler(void)                                       {Default_Handler();}
__weak void LPUART1_IRQHandler(void)                                      {Default_Handler();}
__weak void CRS_IRQHandler(void)                                          {Default_Handler();}
__weak void ECC_IRQHandler(void)                                          {Default_Handler();}
__weak void SAI4_IRQHandler(void)                                         {Default_Handler();}
__weak void WAKEUP_PIN_IRQHandler(void)                                   {Default_Handler();}

__attribute__((section(".isr_vector")))
const void (*VectorTable[])(void) = 
{
    (const void (*)(void))&_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,
    PVD_AVD_IRQHandler,
    TAMP_STAMP_IRQHandler,
    RTC_WKUP_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Stream0_IRQHandler,
    DMA1_Stream1_IRQHandler,
    DMA1_Stream2_IRQHandler,
    DMA1_Stream3_IRQHandler,
    DMA1_Stream4_IRQHandler,
    DMA1_Stream5_IRQHandler,
    DMA1_Stream6_IRQHandler,
    ADC_IRQHandler,
    FDCAN1_IT0_IRQHandler,
    FDCAN2_IT0_IRQHandler,
    FDCAN1_IT1_IRQHandler,
    FDCAN2_IT1_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_IRQHandler,
    TIM1_UP_IRQHandler,
    TIM1_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_Alarm_IRQHandler,
    0,
    TIM8_BRK_TIM12_IRQHandler,
    TIM8_UP_TIM13_IRQHandler,
    TIM8_TRG_COM_TIM14_IRQHandler,
    TIM8_CC_IRQHandler,
    DMA1_Stream7_IRQHandler,
    FMC_IRQHandler,
    SDMMC1_IRQHandler,
    TIM5_IRQHandler,
    SPI3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    TIM6_DAC_IRQHandler,
    TIM7_IRQHandler,
    DMA2_Stream0_IRQHandler,
    DMA2_Stream1_IRQHandler,
    DMA2_Stream2_IRQHandler,
    DMA2_Stream3_IRQHandler,
    DMA2_Stream4_IRQHandler,
    ETH_IRQHandler,
    ETH_WKUP_IRQHandler,
    FDCAN_CAL_IRQHandler,
    0,
    0,
    0,
    0,
    DMA2_Stream5_IRQHandler,
    DMA2_Stream6_IRQHandler,
    DMA2_Stream7_IRQHandler,
    USART6_IRQHandler,
    I2C3_EV_IRQHandler,
    I2C3_ER_IRQHandler,
    OTG_HS_EP1_OUT_IRQHandler,
    OTG_HS_EP1_IN_IRQHandler,
    OTG_HS_WKUP_IRQHandler,
    OTG_HS_IRQHandler,
    DCMI_IRQHandler,
    0,
    RNG_IRQHandler,
    FPU_IRQHandler,
    UART7_IRQHandler,
    UART8_IRQHandler,
    SPI4_IRQHandler,
    SPI5_IRQHandler,
    SPI6_IRQHandler,
    SAI1_IRQHandler,
    LTDC_IRQHandler,
    LTDC_ER_IRQHandler,
    DMA2D_IRQHandler,
    SAI2_IRQHandler,
    QUADSPI_IRQHandler,
    LPTIM1_IRQHandler,
    CEC_IRQHandler,
    I2C4_EV_IRQHandler,
    I2C4_ER_IRQHandler,
    SPDIF_RX_IRQHandler,
    OTG_FS_EP1_OUT_IRQHandler,
    OTG_FS_EP1_IN_IRQHandler,
    OTG_FS_WKUP_IRQHandler,
    OTG_FS_IRQHandler,
    DMAMUX1_OVR_IRQHandler,
    HRTIM1_Master_IRQHandler,
    HRTIM1_TIMA_IRQHandler,
    HRTIM1_TIMB_IRQHandler,
    HRTIM1_TIMC_IRQHandler,
    HRTIM1_TIMD_IRQHandler,
    HRTIM1_TIME_IRQHandler,
    HRTIM1_FLT_IRQHandler,
    DFSDM1_FLT0_IRQHandler,
    DFSDM1_FLT1_IRQHandler,
    DFSDM1_FLT2_IRQHandler,
    DFSDM1_FLT3_IRQHandler,
    SAI3_IRQHandler,
    SWPMI1_IRQHandler,
    TIM15_IRQHandler,
    TIM16_IRQHandler,
    TIM17_IRQHandler,
    MDIOS_WKUP_IRQHandler,
    MDIOS_IRQHandler,
    JPEG_IRQHandler,
    MDMA_IRQHandler,
    0,
    SDMMC2_IRQHandler,
    HSEM1_IRQHandler,
    0,
    ADC3_IRQHandler,
    DMAMUX2_OVR_IRQHandler,
    BDMA_Channel0_IRQHandler,
    BDMA_Channel1_IRQHandler,
    BDMA_Channel2_IRQHandler,
    BDMA_Channel3_IRQHandler,
    BDMA_Channel4_IRQHandler,
    BDMA_Channel5_IRQHandler,
    BDMA_Channel6_IRQHandler,
    BDMA_Channel7_IRQHandler,
    COMP1_IRQHandler,
    LPTIM2_IRQHandler,
    LPTIM3_IRQHandler,
    LPTIM4_IRQHandler,
    LPTIM5_IRQHandler,
    LPUART1_IRQHandler,
    0,
    CRS_IRQHandler,
    ECC_IRQHandler,
    SAI4_IRQHandler,
    0,
    0,
    WAKEUP_PIN_IRQHandler,
};