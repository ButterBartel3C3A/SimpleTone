/* v 0.1.1 ：将note()函数集成至SimpleTone库内了。*/
/*
 请在你使用这个库的时候在主程序内添加以下这个函数。
 因为Python转换脚本并不知道你的实例名是什么，这么做保证Python脚本简单易用的同时代码同样保持简洁。
  ```c
  void note(uint32_t freq, float duration_sec);{
    {实例名}.note(freq, duration_sec);
  }
  ```
*/
#pragma once
#include <Arduino.h> // 在使用纯HAL库开发时注释掉这行即可
#include <stm32f4xx_hal.h> //请根据你使用的MCU来选择对应的头文件
#ifdef USE_FREERTOS
  #include "FreeRTOS.h"
  #include "task.h"
#endif

//节拍表
#ifndef bpm
 #define bpm 160.0 // beat per minute 主程序内未定义bpm则默认bpm160
#endif

#define rest 0            // 休止符
#define beat (60.0/bpm)   // 四四拍，每拍一个四分音符
#define quaver beat/2.0   // 八分音符
#define quater beat       // 四分音符
#define half beat*2.0     // 二分音符
#define whole beat*4.0    // 全音符
#define dotted 1.5*       // 附点音符

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

  void note(uint32_t freq, float duration_sec); // 音符函数。
  // 它相当于直接集成了tone(), handle()的功能，自动轮询音符时长，自动关闭。
  // 里面包含一个HAL_Delay(1)用于避免过长时间高速占用IO与CPU，理论上来说不会过度占用程序。
  // 在后期对RTOS进行优化后，会使用其他办法代替该delay。

private:
  GPIO_TypeDef* _GPIOx;
  uint16_t _GPIO_Pin;

  TIM_HandleTypeDef _htim;
  uint32_t _tim_channel;

  bool _active;
  unsigned long _endTime;
  
  void pwmSetFrequency(uint32_t freq);
};
