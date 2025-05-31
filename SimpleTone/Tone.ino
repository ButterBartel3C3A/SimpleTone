#include<stm32f407xx.h>
#include<Arduino.h>

#define bpm 220.0 //定义曲速
#include<SimpleTone.h> //若使用自定义bpm，调用SimpleTone库前就需要定义bpm

void note(uint32_t freq, float duration_sec);

// 实例化蜂鸣器，使用PD14作为输出引脚
SimpleTone buzzer(GPIOD, GPIO_PIN_14);

void setup() {
  //蜂鸣器初始化
  buzzer.begin();
}

void loop() {
  // bpm=160 beat=3/4
  note(E4 octdown, half); note(G4 octdown octdown, half);
  note(D4 octdown, half); note(C4 octdown, half);
  note(G4 octdown octdown, half); note(D4 octdown, half);
  note(E4 octdown, dotted half);
  note(F4 octdown, quater); note(E4 octdown, half);
  note(D4 octdown, whole);
  note(C4 octdown, quater); note(D4 octdown, quater); note(E4 octdown, half);
  note(G4 octdown octdown, half); note(D4 octdown, half);
  note(C4 octdown, half); note(G4 octdown octdown, half);
  note(D4 octdown, half); note(E4 octdown, dotted half);
  note(F4 octdown, quater); note(E4 octdown, half);
  note(D4 octdown, whole);
  note(C4 octdown, quater); note(D4 octdown, quater); note(E4 octdown, quater);
  note(rest, quater); note(E4 octdown, half);
  note(D4 octdown, half); note(F4 octdown, half);
  note(E4 octdown, half); note(D4 octdown, half);
  note(D4 octdown, half); note(D4 octdown, half);
  note(C4 octdown, half); note(F4 octdown, half);
  note(E4 octdown, half); note(D4 octdown, half);
  note(D4 octdown, whole);
  note(C4 octdown, quater); note(D4 octdown, quater); note(E4 octdown, whole);
  note(rest, whole *2); note(E4 octdown, half);
  note(G4 octdown, half); note(C4, half);
  note(B4 octdown, half); note(rest, half); note(C4, half);
  note(B4 octdown, half); note(rest, half); note(C4, half);
  note(B4 octdown, quater); note(A4 octdown, quater); note(G4 octdown, half);
  note(rest, half); note(G4 octdown, half);
  note(D4 octdown, half); note(F4 octdown, half);
  note(F4 octdown, half); note(rest, half); note(E4 octdown, half);
  note(E4 octdown, half); note(rest, half); note(G4 octdown octdown, half);
  note(F4 octdown, half); note(E4 octdown, half);
  note(D4 octdown, half); note(E4 octdown, half);
  note(rest, half); note(G4 octdown, half);
  note(C4 octdown, whole);
  note(rest, whole *2); note(C4 octdown, half);
  note(D4 octdown, half); note(C4 octdown, half);
  note(rest, half); note(C4 octdown, half);
  note(G4 octdown, half); note(C4 octdown, half);
  note(F4 octdown, half); note(E4 octdown, half);
  note(D4 octdown, half); note(D4 octdown, half);
  note(rest, half); note(C4 octdown, half);
  note(C4 octdown, half); note(rest, whole *2); note(A4 octdown, half);
  note(G4 octdown, half); note(G4 octdown, half);
  note(G4 octdown, half); note(F4 octdown, half);
  note(F4 octdown, half); note(E4 octdown, half);
  note(D4 octdown, half); note(D4 octdown, half);
  note(rest, whole *2); note(G4 octdown, half);
  note(F4 octdown, half); note(F4 octdown, half);
  note(F4 octdown, half); note(E4 octdown, half);
  note(D4 octdown, half); note(D4 octdown, half);
  note(rest, half); note(C4 octdown, quater);
  note(B4 octdown octdown, quater); note(C4 octdown, half);
  note(rest, half); note(C4 octdown, half);
  note(A4 octdown, half); note(G4 octdown, half);
  note(G4 octdown, half); note(G4 octdown, half);
  note(F4 octdown, half); note(F4 octdown, half);
  note(E4 octdown, half); note(D4 octdown, half);
  note(D4 octdown, half); note(rest, whole); note(C4 octdown, quater);
  note(D4 octdown, quater); note(E4 octdown, half);
  note(E4 octdown, half); note(D4 octdown, half);
  note(E4 octdown, whole);
  note(G4 octdown, half); note(D4, whole);
  note(C4, half); note(C4, half);
  note(rest, half); note(C4, half);
  note(B4 octdown, half); note(rest, half); note(A4 octdown, half);
  note(A4 octdown, whole);
  note(rest, whole *2); note(A4 octdown, half);
  note(A4 octdown, half); note(G4 octdown, half);
  note(F4 octdown, half); note(F4 octdown, whole);
  note(E4 octdown, quater); note(F4 octdown, quater); note(G4 octdown, whole);
  note(rest, whole *4); note(E4 octdown, quater);
  note(D4 octdown, quater); note(E4 octdown, quater); note(D4 octdown, quater);
  note(E4 octdown, quater); note(F4 octdown, quater); note(G4 octdown, quater);
  note(rest, dotted half); note(F4 octdown, quater);
  note(G4 octdown, quater); note(A4 octdown, quater); note(rest, dotted half); note(A4 octdown, quater);
  note(B4 octdown, quater); note(C4, quater); note(rest, dotted half); note(D4, quater);
  note(C4, quater); note(G4 octdown, quater); note(rest, dotted half); note(G4 octdown, half);
  note(G4 octdown, half); note(D4 octdown, half);
  note(F4 octdown, half); note(F4 octdown, whole);
  note(E4 octdown, quater); note(D4 octdown, quater); note(E4 octdown, whole);
  note(rest, half); note(E4 octdown, quater);
  note(D4 octdown, quater); note(E4 octdown, quater); note(D4 octdown, quater);
  note(E4 octdown, quater); note(F4 octdown, quater); note(G4 octdown, quater);
  note(rest, dotted half); note(F4 octdown, quater);
  note(G4 octdown, quater); note(A4 octdown, quater); note(rest, dotted half); note(G4sharp octdown, quater);
  note(A4 octdown, quater); note(B4 octdown, quater); note(rest, dotted half); note(E4 octdown, half);
  note(E4, half); note(E4, half);
  note(E4, half); note(F4, half);
  note(E4, half); note(D4, half);
  note(D4, whole);
  note(C4, quater); note(B4 octdown, quater); note(C4, half);
  note(rest, half); note(C4, half);
  note(B4 octdown, whole);
  note(A4 octdown, half); note(A4 octdown, whole);
  note(rest, whole *2); note(A4 octdown, half);
  note(A4 octdown, half); note(G4 octdown, half);
  note(F4 octdown, half); note(F4 octdown, whole);
  note(E4 octdown, quater); note(F4 octdown, quater); note(G4 octdown, whole);
  note(rest, half); note(E4 octdown, half);
  note(E4 octdown, half); note(E4 octdown, half);
  note(F4 octdown, half); note(E4 octdown, half);
  note(D4 octdown, half); note(C4 octdown, whole);
}

void note(uint32_t freq, float duration_sec) {
  buzzer.tone(freq, duration_sec);
  buzzer.handle(); // 等待播放完毕，或者用buzzer.handle()轮询
  delay(1);
}