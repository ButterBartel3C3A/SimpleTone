# SimpleTone库与其Python上位机Midi2NoteConverter使用说明

## 简介

SimpleTone库是一个基于STM32 HAL库，可支持HAL库与Arduino两个框架的，使用定时器与PWM进行输出的音频信号生成库。可直接驱动IO上的蜂鸣器播放音符。
默认的，其IO口设置于`TIM4`通道3对应`PD14`引脚，对应RobomasterC板电路。若有需要可直接修改`SimpleTone.cpp`中的相关引脚变量。后续更新会更新为宏定义或可传参。

Midi2NoteConverter是一个Python上位机，可将Midi文件转换为SinpleTone库中对应Note格式 ，并一键粘贴至`main.cpp`中的`while(1){}`或`void loop()`函数中。

## SimpleTone库使用说明

SimpleTone库存在以下两表，分别对应音高与时值。

```c
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
```

```c
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
```

在使用中，先实例化SimpleTone对象，如左：`SimpleTone 对象名(GPIOD, GPIO_PIN_14);`。由于并未测试该库在其他GPIO上的可用性，故暂时不建议在其他GPIO上使用。随后在初始化函数中调用 对象名.begin()函数，如右：`对象名.begin();`。
最后，即可在while(1){}或void loop()函数中使用note(音符, 时值);函数来播放音符。具体语法如下：

```c
#define bpm 150.0 //设置bpm
//若不设置bpm，则默认为150.0。请在#include "SimpleTone.h"之前设置。

#include "SimpleTone.h"

SimpleTone 对象名(GPIOD, GPIO_PIN_14); //实例化SimpleTone对象

void setup() {
  对象名.begin(); //初始化
}

void loop() {
  note(音符, 时值); //播放音符
  //若存在八度移调，请如下使用
  note(A4 octup, quater) //音高为A5的四分音符
  note(A4 octdown, quater) //音高为A3的四分音符
  //若存在附点音符，请如下使用
  note(A4, dotted quater); //音高为A4的附点四分音符
  //若存在休止符，请如下使用
  note(rest, half); //休止符为二分音符
  //若存在音符组，请如下使用
  note(C4, whole); //播放C4全音符
  note(D4, quaver); //播放D4八分音符
}
```

## Midi2NoteConverter使用说明

Midi2NoteConverter是一个Python上位机，可将Midi文件转换为SinpleTone库中对应Note格式，并一键粘贴至`main.cpp`中的`while(1){}`或`void loop()`函数中。
使用时，确保你已有python3环境，并已添加于环境变量。随后双击 `run_temp_env.bat`，一键创建虚拟环境并安装所需依赖，并运行 `Midi2NoteConverter.py`。
打开软件后，选择Midi文件，点击“转换”按钮。使用默认bpm或自定义bpm使用默认4/4拍或修改拍号（如3/4），点击生成，即可生成对应的Note格式代码。将以`output.txt`文件保存至当前目录。
导入的Midi文件应当有且仅有一条轨道有合法音符，轨道内有且仅有一最大复音数，且已量化。具体术语解析请参照维基百科。
