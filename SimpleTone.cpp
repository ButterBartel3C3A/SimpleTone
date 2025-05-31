#include "SimpleTone.h"

// 选择TIM4通道3对应PD14，对应C板电路

SimpleTone::SimpleTone(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
  : _GPIOx(GPIOx), _GPIO_Pin(GPIO_Pin), _active(false), _endTime(0)
{
  _tim_channel = TIM_CHANNEL_3; // PD14对应TIM4_CH3
}

void SimpleTone::begin() {
  // 使能GPIO和TIM4时钟
  if (_GPIOx == GPIOD && _GPIO_Pin == GPIO_PIN_14) {
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_TIM4_CLK_ENABLE();

    // GPIO初始化为复用推挽
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = _GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(_GPIOx, &GPIO_InitStruct);

    // TIM4 初始化，先默认1000Hz频率，后面再改
    _htim.Instance = TIM4;
    _htim.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() * 2 / 1000000) - 1; // 计数频率1MHz（APB1定时器时钟一般是PCLK1*2）
    _htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    _htim.Init.Period = 1000 - 1; // 默认1kHz频率周期
    _htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    _htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_PWM_Init(&_htim) != HAL_OK) {
      // 错误处理（简单示意）
      while (1);
    }

    // 配置PWM通道
    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = (_htim.Init.Period + 1) / 2; // 50%占空比
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    if (HAL_TIM_PWM_ConfigChannel(&_htim, &sConfigOC, _tim_channel) != HAL_OK) {
      while (1);
    }
  }
}

void SimpleTone::pwmSetFrequency(uint32_t freq) {
  
  uint32_t timer_clock = HAL_RCC_GetPCLK1Freq() * 2; // APB1定时器时钟一般是PCLK1*2
  uint32_t prescaler = _htim.Init.Prescaler + 1; // 当前预分频器+1

  // 计算周期ARR
  uint32_t period = timer_clock / (prescaler * freq) - 1;

  if (freq == 0) period = -1;

  __HAL_TIM_SET_AUTORELOAD(&_htim, period);
  // 占空比保持50%
  __HAL_TIM_SET_COMPARE(&_htim, _tim_channel, (period + 1) / 2);
  __HAL_TIM_ENABLE(&_htim); // 保证定时器使能
  // 重载计数器
  __HAL_TIM_SET_COUNTER(&_htim, 0);
  HAL_TIM_PWM_Start(&_htim, _tim_channel);
}

void SimpleTone::tone(uint32_t freq, float duration_sec) {

  pwmSetFrequency(freq);
  _active = true;

  if (duration_sec > 0) {
    _endTime = millis() + (unsigned long)(duration_sec * 1000);
  } else {
    _endTime = 0;
  }
}

void SimpleTone::noTone() {
  HAL_TIM_PWM_Stop(&_htim, _tim_channel);
  HAL_GPIO_WritePin(_GPIOx, _GPIO_Pin, GPIO_PIN_RESET);
  _active = false;
  _endTime = 0;
}

void SimpleTone::handle() {
  while(1){
    if (_active && _endTime > 0 && millis() >= _endTime) {
      noTone();
      return;
    }
  }
}
