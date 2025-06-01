/* v 0.1.1 ：将note()函数集成至SimpleTone库内了。*/
/* 这是一个例程。为了使例程能够直接烧录，使用与库同名的.ino编写该例程。*/
/* 现在这份例程可以直接烧录到C板上播放春日影！*/
/* Author：人造黄油（ButterBartel3C3A）*/
/* 广告位：请大家支持天津理工大学Nirnava战队喵谢谢喵 */

#include<stm32f407xx.h>
#include<Arduino.h>

#define bpm 180.0 //定义曲速
#include<SimpleTone.h> //若使用自定义bpm，调用SimpleTone库前就需要定义bpm

// 实例化蜂鸣器，使用PD14作为输出引脚
SimpleTone buzzer(GPIOD, GPIO_PIN_14); // 由于STM32duino框架的varient.h内未定义GPIOD系列引脚，故此行请使用HAL库语法进行实例化。

// 请在你使用这个库的时候在主程序内添加这一个函数。
// 因为Python转换脚本并不知道你的实例名是什么，这么做保证Python脚本简单易用的同时代码同样保持简洁。
void note(uint32_t freq, float duration_sec);

void setup() {
  //蜂鸣器初始化
  buzzer.begin();
}

void loop() {
  // bpm=180 beat=3/4
  note(E4, quater); note(G4 octdown, quater); note(D4, quater);
  note(C4, quater); note(G4 octdown, quater); note(D4, quater);
  note(E4, dotted quater); note(F4, quaver); note(E4, quater);
  note(D4, half); note(C4, quaver); note(D4, quaver);
  note(E4, quater); note(G4 octdown, quater); note(D4, quater);
  note(C4, quater); note(G4 octdown, quater); note(D4, quater);
  note(E4, dotted quater); note(F4, quaver); note(E4, quater);
  note(D4, half); note(C4, quaver); note(D4, quaver);
  note(E4, quaver); note(rest, quaver); note(E4, quater); note(D4, quater);
  note(F4, quater); note(E4, quater); note(D4, quater);
  note(D4, quater); note(D4, quater); note(C4, quater);
  note(F4, quater); note(E4, quater); note(D4, quater);
  note(D4, half); note(C4, quaver); note(D4, quaver);
  note(E4, half); note(rest, whole); note(E4, quater);
  note(G4, quater); note(C4 octup, quater); note(B4, quater);
  note(rest, quater); note(C4 octup, quater); note(B4, quater);
  note(rest, quater); note(C4 octup, quater); note(B4, quaver); note(A4, quaver);
  note(G4, quater); note(rest, quater); note(G4, quater);
  note(D4, quater); note(F4, quater); note(F4, quater);
  note(rest, quater); note(E4, quater); note(E4, quater);
  note(rest, quater); note(G4 octdown, quater); note(F4, quater);
  note(E4, quater); note(D4, quater); note(E4, quater);
  note(rest, quater); note(G4, quater); note(C4, half);
  note(rest, dotted half); note(C4, quater);
  note(D4, quater); note(C4, quater); note(rest, quater); note(C4, quater);
  note(G4, quater); note(C4, quater); note(F4, quater);
  note(E4, quater); note(D4, quater); note(D4, quater);
  note(rest, quater); note(C4, quater); note(C4, quater);
  note(rest, whole *1); note(A4, quater);
  note(G4, quater); note(G4, quater); note(G4, quater);
  note(F4, quater); note(F4, quater); note(E4, quater);
  note(D4, quater); note(D4, quater); note(rest, dotted half); note(G4, quater);
  note(F4, quater); note(F4, quater); note(F4, quater);
  note(E4, quater); note(D4, quater); note(D4, quater);
  note(rest, quater); note(C4, quaver); note(B4 octdown, quaver); note(C4, quater);
  note(rest, quater); note(C4, quater); note(A4, quater);
  note(G4, quater); note(G4, quater); note(G4, quater);
  note(F4, quater); note(F4, quater); note(E4, quater);
  note(D4, quater); note(D4, quater); note(rest, half); note(C4, quaver);
  note(D4, quaver); note(E4, quater); note(E4, quater); note(D4, quater);
  note(E4, half); note(G4, quater);
  note(D4 octup, half); note(C4 octup, quater);
  note(C4 octup, quater); note(rest, quater); note(C4 octup, quater);
  note(B4, quater); note(rest, quater); note(A4, quater);
  note(A4, half); note(rest, dotted half); note(A4, quater);
  note(A4, quater); note(G4, quater); note(F4, quater);
  note(F4, half); note(E4, quaver); note(F4, quaver);
  note(G4, half); note(rest, whole *2); note(E4, quaver);
  note(D4, quaver); note(E4, quaver); note(D4, quaver); note(E4, quaver); note(F4, quaver); note(G4, quaver);
  note(rest, dotted quater); note(F4, quaver); note(G4, quaver); note(A4, quaver);
  note(rest, dotted quater); note(A4, quaver); note(B4, quaver); note(C4 octup, quaver);
  note(rest, dotted quater); note(D4 octup, quaver); note(C4 octup, quaver); note(G4, quaver);
  note(rest, dotted quater); note(G4, quater); note(G4, quater);
  note(D4, quater); note(F4, quater); note(F4, half);
  note(E4, quaver); note(D4, quaver); note(E4, half);
  note(rest, quater); note(E4, quaver); note(D4, quaver); note(E4, quaver); note(D4, quaver);
  note(E4, quaver); note(F4, quaver); note(G4, quaver); note(rest, dotted quater); note(F4, quaver);
  note(G4, quaver); note(A4, quaver); note(rest, dotted quater); note(G4sharp, quaver);
  note(A4, quaver); note(B4, quaver); note(rest, dotted quater); note(E4, quater);
  note(E4 octup, quater); note(E4 octup, quater); note(E4 octup, quater);
  note(F4 octup, quater); note(E4 octup, quater); note(D4 octup, quater);
  note(D4 octup, half); note(C4 octup, quaver); note(B4, quaver);
  note(C4 octup, quater); note(rest, quater); note(C4 octup, quater);
  note(B4, half); note(A4, quater);
  note(A4, half); note(rest, dotted half); note(A4, quater);
  note(A4, quater); note(G4, quater); note(F4, quater);
  note(F4, half); note(E4, quaver); note(F4, quaver);
  note(G4, half); note(rest, quater); note(E4, quater);
  note(E4, quater); note(E4, quater); note(F4, quater);
  note(E4, quater); note(D4, quater); note(C4, half);
  // Generated by Midi2NoteConvertor.py
}

void note(uint32_t freq, float duration_sec){
  buzzer.note(freq, duration_sec);
}

