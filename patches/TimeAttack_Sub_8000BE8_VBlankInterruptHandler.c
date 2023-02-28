// @Description TimeAttack_Sub_8000BE8_VBlankInterruptHandler
// @HookAddress 0x953B8
// @HookString P
// Made by beco
// Verison 1.0

#define VBlankInterruptHandlerFunc (*(volatile unsigned int*) 0x30019FC)

#define TimeDisplay (*(volatile unsigned char*) 0x3006F0E) // 0: Frame, 1: MSec
#define MaxFlag (*(volatile unsigned char*) 0x3006F0F)
#define CountFlag (*(volatile unsigned char*) 0x3006F10)
#define FrameDigit1 (*(volatile unsigned char*) 0x3006F11)
#define FrameDigit2 (*(volatile unsigned char*) 0x3006F12)
#define SecondDidit1 (*(volatile unsigned char*) 0x3006F13)
#define SecondDidit2 (*(volatile unsigned char*) 0x3006F14)
#define MinuteDidit1 (*(volatile unsigned char*) 0x3006F15)
#define MinuteDidit2 (*(volatile unsigned char*) 0x3006F16)
#define UpdateTime (*(volatile unsigned char*) 0x3006F17)
#define RetryFlag (*(volatile unsigned char*) 0x3006F18)
#define MiscCounter (*(volatile unsigned char*) 0x3006F19)
#define LockTimer (*(volatile unsigned char*) 0x3006F1A)
#define cGmTimeBackup1 (*(volatile unsigned char*) 0x3006F20) // Frog timer backup seconds' 2nd digit
#define cGmTimeBackup2 (*(volatile unsigned char*) 0x3006F21) // Frog timer backup seconds' 1st digit
#define cGmTimeBackup3 (*(volatile unsigned char*) 0x3006F22) // Frog timer backup minutes
#define LapTemps1 ((volatile unsigned char*) 0x3006F30) // 30-35
#define LapTemps2 ((volatile unsigned char*) 0x3006F36) // 36-3B
#define LapTemps3 ((volatile unsigned char*) 0x3006F3C) // 3C-41
#define LapTemps4 ((volatile unsigned char*) 0x3006F42) // 42-47
#define LapTemps5 ((volatile unsigned char*) 0x3006F48) // 48-4D
#define DeltaTime ((volatile unsigned char*) 0x3006F4E) // 4E-54

#define Sub_8000BE8_VBlankInterruptHandler ((void (*)()) 0x8000BE9)

void TimeAttack_Sub_8000BE8_VBlankInterruptHandler() {
  // Vanilla Code
  Sub_8000BE8_VBlankInterruptHandler();

  // Custom Code
  // Frame counter
  if (CountFlag == 1 && MaxFlag == 0) {
      FrameDigit1 ++;
      if (FrameDigit1 > 9) {
          FrameDigit2 ++;
          FrameDigit1 = 0;
      }
      if (FrameDigit2 > 5) {
          SecondDidit1 ++;
          FrameDigit2 = 0;
      }
      if (SecondDidit1 > 9) {
          SecondDidit2 ++;
          SecondDidit1 = 0;
      }
      if (SecondDidit2 > 5) {
          MinuteDidit1 ++;
          SecondDidit2 = 0;
      }
      if (MinuteDidit1 > 9) {
          MinuteDidit2 ++;
          MinuteDidit1 = 0;
      }
      if (MinuteDidit2 > 9) {
          FrameDigit1 = 9;
          FrameDigit2 = 5;
          SecondDidit1 = 9;
          SecondDidit2 = 5;
          MinuteDidit1 = 9;
          MinuteDidit2 = 9;
          MaxFlag = 1;
      }
  }
  
}
