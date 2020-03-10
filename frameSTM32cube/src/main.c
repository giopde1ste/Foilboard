#if F0
#include <stm32f0xx_hal.h>
#endif

                                                // Pins assigments for STM32F0xx
#define LED_PIN_GREEN                           GPIO_PIN_9
#define LED_PIN_BLUE                            GPIO_PIN_8
#define LED_GPIO_PORT                           GPIOC
#define LED_GPIO_CLK_ENABLE()                   __HAL_RCC_GPIOC_CLK_ENABLE()
#define USER_BUTTON                             GPIO_PIN_0
#define USER_BUTTON_GPIO_PORT                   GPIOA
#define USER_BUTTON_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()


void EXTI0_1_IRQHandler(void){
    switch(HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON)){
    case GPIO_PIN_SET:
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN_BLUE, GPIO_PIN_SET);
        break;
    case GPIO_PIN_RESET:
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN_BLUE, GPIO_PIN_RESET);
        break;
    default:
        //undifined
        break;
    }
    //HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_BLUE); // <-- Inconsistend
    /**
     * @brief Prototype external interrupt pin
     * 
     * switch(HAL_GPIO_ReadPin(SOME_PIN_PORT, SOME_PIN)){
     * case GPIO_PIN_SET: // <-- Rising egde detection
     *    doSomething();
     *    break;
     * case GPIO_PIN_RESET: // <-- falling egde detection
     *    doSomething();
     *    break;
     * default;
     *    break;  
     * }
     **/
    HAL_GPIO_EXTI_IRQHandler(USER_BUTTON);
}

void GPIO_Init(){
    // enable clk, @vraag : waarom moet dit?
    LED_GPIO_CLK_ENABLE();
    USER_BUTTON_GPIO_CLK_ENABLE();

    // Make struct for GPIO's
    GPIO_InitTypeDef GPIO_InitStruct;

    // Set LED green
    GPIO_InitStruct.Pin = LED_PIN_GREEN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct); 

    // Set LED blue
    GPIO_InitStruct.Pin = LED_PIN_BLUE;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    // Set user button
    GPIO_InitStruct.Pin = USER_BUTTON;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStruct);

    HAL_GPIO_WritePin(USER_BUTTON_GPIO_PORT, USER_BUTTON, GPIO_PIN_RESET);

    // EXTI Priority set
    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 3, 0);
    // enable EXTI
    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
    // set Priority of systick (needed?)
    //HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

int main(void){
    HAL_Init();
    GPIO_Init();

    while (1){
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_GREEN);
        HAL_Delay(250);
    }
}


// @Vraag : Wat doet dit?
void SysTick_Handler(void){
  HAL_IncTick();
}

void NMI_Handler(void){
}

void HardFault_Handler(void){
  while (1) {}
}

void MemManage_Handler(void){
  while (1) {}
}

void BusFault_Handler(void){
  while (1) {}
}

void UsageFault_Handler(void){
  while (1) {}
}

void SVC_Handler(void){
}


void DebugMon_Handler(void){
}

void PendSV_Handler(void){
}
