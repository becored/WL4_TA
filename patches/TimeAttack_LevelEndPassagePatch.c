// @Description TimeAttack_LevelEndPassagePatch
// @HookAddress 0x7CABA
// @HookString 02 48 86 46 02 48 00 47 00 00 CF CA 07 08 P
// Mode: Thumb
// Made by beco

// Data
#define VRAM 0x6000000

// IRAM
#define sGameSeq (*(volatile unsigned short*) 0x3000C3C)
#define unk_3003D54 (*(volatile unsigned char*) 0x3003D54)
#define cGmTime1 (*(volatile unsigned short*) 0x3000BF0) // Frog timer seconds' 2nd digit
#define cGmTime2 (*(volatile unsigned short*) 0x3000BF1) // Frog timer seconds' 1st digit
#define cGmTime3 (*(volatile unsigned short*) 0x3000BF2) // Frog timer minutes

#define MaxFlag (*(volatile unsigned char*) 0x3006F0F)
#define CountFlag (*(volatile unsigned char*) 0x3006F10)
#define FrameDigit1 (*(volatile unsigned char*) 0x3006F11)
#define FrameDigit2 (*(volatile unsigned char*) 0x3006F12)
#define SecondDidit1 (*(volatile unsigned char*) 0x3006F13)
#define SecondDidit2 (*(volatile unsigned char*) 0x3006F14)
#define MinuteDidit1 (*(volatile unsigned char*) 0x3006F15)
#define MinuteDidit2 (*(volatile unsigned char*) 0x3006F16)
#define RetryFlag (*(volatile unsigned char*) 0x3006F18)
#define cGmTimeBackup1 (*(volatile unsigned char*) 0x3006F20) // Frog timer backup seconds' 2nd digit
#define cGmTimeBackup2 (*(volatile unsigned char*) 0x3006F21) // Frog timer backup seconds' 1st digit
#define cGmTimeBackup3 (*(volatile unsigned char*) 0x3006F22) // Frog timer backup minutes

// Subroutine
#define sub_807E768 ((void (*)()) 0x807E769)
#define sub_807E6EC ((void (*)()) 0x807E6ED)
#define sub_807E720 ((void (*)()) 0x807E721)
#define sub_807D5C8 ((int (*)()) 0x807D5C9)

__attribute__((no_caller_saved_registers))
void TimeAttack_LevelEndPassagePatch() {
    // Vanilla code
    if (unk_3003D54) {
      sub_807E768();
    }
    sub_807E6EC();
    sub_807E720();

    // Custom code
    if (RetryFlag){
        // Initialize
        MaxFlag = 0;
        FrameDigit1 = 0;
        FrameDigit2 = 0;
        SecondDidit1 = 0;
        SecondDidit2 = 0;
        MinuteDidit1 = 0;
        MinuteDidit2 = 0;
        RetryFlag = 0;

        // Restore frog timer from backup
        cGmTime1 = cGmTimeBackup1;
        cGmTime2 = cGmTimeBackup2;
        cGmTime3 = cGmTimeBackup3;

        sGameSeq = 0x0A; // Return to level
    }
}
