// @Description TimeAttack_MainGameLoopPatch
// @HookAddress 0x1D4
// @HookString 01 48 86 46 01 48 00 47 ED 01 00 08 P
// Mode: Thumb
// Made by beco

// IRAM
#define usRandomCount (*(volatile unsigned short*) 0x3000006)
#define ucMainTimer (*(volatile unsigned short*) 0x3000C41)

#define GlobalGameMode (*(volatile unsigned char*) 0x3000C3A)
#define GameState (*(volatile unsigned char*) 0x3000C3C)
#define unk_300001B (*(volatile unsigned char*) 0x300001B)
#define unk_3000046 (*(volatile unsigned char*) 0x3000046)
#define sub_806E08C ((void (*)()) 0x806E08D)
#define cGmStartFlg (*(volatile unsigned char*) 0x3000C3F)
#define cPauseFlag (*(volatile unsigned char*) 0x3000C35)
#define soft_reset (*(volatile unsigned char*) 0x300001E)
#define ucDokan (*(volatile unsigned char*) 0x300189A)
#define inVortex (*(volatile unsigned char*) 0x3000C0E)
#define usWarStopFlg (*(volatile unsigned char*) 0x30019F6)

#define MaxFlag (*(volatile unsigned char*) 0x3006F0F)
#define CountFlag (*(volatile unsigned char*) 0x3006F10)
#define FrameDigit1 (*(volatile unsigned char*) 0x3006F11)
#define FrameDigit2 (*(volatile unsigned char*) 0x3006F12)
#define SecondDidit1 (*(volatile unsigned char*) 0x3006F13)
#define SecondDidit2 (*(volatile unsigned char*) 0x3006F14)
#define MinuteDidit1 (*(volatile unsigned char*) 0x3006F15)
#define MinuteDidit2 (*(volatile unsigned char*) 0x3006F16)

// I/O
#define REG_DMA3SAD (*(volatile unsigned int*) 0x40000D4)
#define REG_DMA3DAD (*(volatile unsigned int*) 0x40000D8)
#define REG_DMA3CNT (*(volatile unsigned int*) 0x40000DC)

// VRAM
#define VRAM 0x6000000 // VRAM

// Subroutine
#define Sub_8000954_SetKeyPressWRAM ((void (*)()) 0x8000955)
#define Sub_80007BC_SoftResetCheck ((void (*)()) 0x80007BD)

// Char
#define APO_CHAR 0x8401CE8
#define NUM_CHAR 0x8403AE8

void TimeAttack_MainGameLoopPatch() {
    // Vanilla code
    Sub_8000954_SetKeyPressWRAM();
    Sub_80007BC_SoftResetCheck();
    ++ucMainTimer;
    ++usRandomCount;

    // Custom code
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
            FrameDigit2 = 9;
            SecondDidit1 = 9;
            SecondDidit2 = 5;
            MinuteDidit1 = 9;
            MinuteDidit2 = 9;
            MaxFlag = 1;
        }
    }

    // Pause menu
    if (GlobalGameMode == 4) {
        // Frames 1-digit
        REG_DMA3SAD = NUM_CHAR + (FrameDigit1 * 0x20);
        REG_DMA3DAD = (VRAM + 0x11120);
        REG_DMA3CNT = 0x80000010;

        // Frames 2-digit
        REG_DMA3SAD = NUM_CHAR + (FrameDigit2 * 0x20);
        REG_DMA3DAD = (VRAM + 0x11100);
        REG_DMA3CNT = 0x80000010;

        // Seconds 1-digit
        REG_DMA3SAD = APO_CHAR + (SecondDidit1 * 0x20);
        REG_DMA3DAD = (VRAM + 0x110E0);
        REG_DMA3CNT = 0x80000010;

        // Seconds 2-digit
        REG_DMA3SAD = NUM_CHAR + (SecondDidit2 * 0x20);
        REG_DMA3DAD = (VRAM + 0x110C0);
        REG_DMA3CNT = 0x80000010;

        // Minutes 1-digit
        REG_DMA3SAD = APO_CHAR + (MinuteDidit1 * 0x20);
        REG_DMA3DAD = (VRAM + 0x110A0);
        REG_DMA3CNT = 0x80000010;

        // Minutes 2-digit
        REG_DMA3SAD = NUM_CHAR + (MinuteDidit2 * 0x20);
        REG_DMA3DAD = (VRAM + 0x11080);
        REG_DMA3CNT = 0x80000010;
    }
}
