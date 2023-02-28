// @Description TimeAttack_LevelEndScreenTransitionPatch
// @HookAddress 0x7D2AE
// @HookString 02 48 86 46 02 48 00 47 00 00 CD D2 07 08 P
// Mode: Thumb
// Made by beco

// Data
#define VRAM 0x6000000

// IRAM
#define sGameSeq (*(volatile unsigned short*) 0x3000C3C)
#define sDmapWindowLeftX (*(volatile unsigned short*) 0x3003C4C)
#define sDmapWindowRightX (*(volatile unsigned short*) 0x3003C4E)
#define sDmapWindowUpY (*(volatile unsigned short*) 0x3003C50)
#define sDmapWindowDownY (*(volatile unsigned short*) 0x3003C52)

#define FrameDigit1 (*(volatile unsigned char*) 0x3006F11)
#define FrameDigit2 (*(volatile unsigned char*) 0x3006F12)
#define SecondDidit1 (*(volatile unsigned char*) 0x3006F13)
#define SecondDidit2 (*(volatile unsigned char*) 0x3006F14)
#define MinuteDidit1 (*(volatile unsigned char*) 0x3006F15)
#define MinuteDidit2 (*(volatile unsigned char*) 0x3006F16)
#define RetryFlag (*(volatile unsigned char*) 0x3006F18)

// Subroutine
#define Sub_8001DA4_m4aSongNumStart ((int (*)(int)) 0x8001DA5)
#define sub_807CADC ((void (*)()) 0x807CADD)

void TimeAttack_LevelEndScreenTransitionPatch() {
    // Vanilla code
    /*
    Sub_8001DA4_m4aSongNumStart(639);
    sub_807CADC();
    sDmapWindowLeftX = 0;
    sDmapWindowRightX = 240;
    sDmapWindowUpY = 0;
    sDmapWindowDownY = 160;
    */

    // Custom code
    if (!RetryFlag) {
        Sub_8001DA4_m4aSongNumStart(639);
        sub_807CADC();
    }
    sDmapWindowLeftX = 0;
    sDmapWindowRightX = 240;
    sDmapWindowUpY = 0;
    sDmapWindowDownY = 160;
}
