#pragma once
#include <Arduino.h>
#include "stm32f4xx_hal.h"

#ifndef
  #define true 1
  #define false 0
#endif

//节拍表
#ifndef bpm
 #define bpm 150.0 //beat per minute 默认bpm150
#endif

#define rest 0 //休止符
#define beat (60.0/bpm) //四四拍，每拍一个四分音符
#define quaver beat/2.0 //八分音符
#define quater beat //四分音符
#define half beat*2.0 //二分音符
#define whole beat*4.0 //全音符
#define dotted 1.5* //附点

//音符表
#define A3 440
#define A3sharp 466
#define B3 494
#define C4 523
#define C4sharp 554
#define D4 587
#define D4sharp 622
#define E4 659
#define F4 698
#define F4sharp 740
#define G4 784
#define G4sharp 831
#define A4 880
#define A4sharp 932
#define B4 988
#define octup *2
#define octdown /2

class SimpleTone {
public:
  SimpleTone(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
  void begin();  // 初始化PWM定时器与GPIO
  void tone(uint32_t freq, float duration_sec = 0); // 频率+可选时长（秒）
  void noTone(); // 停止PWM输出
  void handle(); // 轮询调用，处理超时自动关闭

private:
  GPIO_TypeDef* _GPIOx;
  uint16_t _GPIO_Pin;

  TIM_HandleTypeDef _htim;
  uint32_t _tim_channel;

  bool _active;
  unsigned long _endTime;
  
  void pwmSetFrequency(uint32_t freq);
};
