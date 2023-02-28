// @Description TimeAttack_MainGameLoopPatch
// @HookAddress 0x1D4
// @HookString 01 48 86 46 01 48 00 47 ED 01 00 08 P
// Mode: Thumb
// Made by beco

// IRAM
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define usRandomCount (*(volatile unsigned short*) 0x3000006)
#define ucTimeUp (*(volatile unsigned char*) 0x3000047) // 01(fighting boss) 02(Losing coins) 03(Losing coins without coin counter) 04(hide coin counter) 10(fade to grayscale) 0f(no interaction between wario and enemies)
#define GlobalGameMode (*(volatile unsigned char*) 0x3000C3A)
#define GameState (*(volatile unsigned char*) 0x3000C3C)
#define ucMainTimer (*(volatile unsigned short*) 0x3000C41)
#define unk_300001B (*(volatile unsigned char*) 0x300001B)
#define unk_3000046 (*(volatile unsigned char*) 0x3000046)
#define sub_806E08C ((void (*)()) 0x806E08D)
#define cGmStartFlg (*(volatile unsigned char*) 0x3000C3F)
#define cPauseFlag (*(volatile unsigned char*) 0x3000C35)
#define soft_reset (*(volatile unsigned char*) 0x300001E)
#define ucDokan (*(volatile unsigned char*) 0x300189A)
#define inVortex (*(volatile unsigned char*) 0x3000C0E)
#define usWarStopFlg (*(volatile unsigned char*) 0x30019F6)

#define BossLife (*(volatile unsigned char*) 0x3006F0C)
#define LoadEntityStates (*(volatile unsigned char*) 0x3006F0D) // 0: Not yet, 1: Done
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

// I/O
#define REG_DMA3SAD (*(volatile unsigned int*) 0x40000D4)
#define REG_DMA3DAD (*(volatile unsigned int*) 0x40000D8)
#define REG_DMA3CNT (*(volatile unsigned int*) 0x40000DC)

// VRAM
#define PAL_TIMER (*(volatile unsigned short*) 0x500028C) // PAL RAM
#define VRAM 0x6000000 // VRAM

// Subroutine
#define Sub_8000954_SetKeyPressWRAM ((void (*)()) 0x8000955)
#define Sub_80007BC_SoftResetCheck ((void (*)()) 0x80007BD)

// Char
#define APO_CHAR 0x8401CE8
#define MSC_CHAR 0x8409EE8
#define NUM_CHAR 0x8403AE8
#define BLK_CHAR 0x8400E28
#define B_APO_CHAR 0x84024C8
#define B_MSC_CHAR 0x8409CE8
#define B_NUM_CHAR 0x84020C8
#define B_CLK_CHAR 0x8401448

const char MSecTableDigit1[60] =
{
    0,1,3,5,6,8,0,1,3,5,6,8,0,1,3,5,6,8,0,1,3,5,6,8,0,1,3,5,6,8,
    0,1,3,5,6,8,0,1,3,5,6,8,0,1,3,5,6,8,0,1,3,5,6,8,0,1,3,5,6,8,
};

const char MSecTableDigit2[60] =
{
    0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,
    5,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,9,9,9,9,9,9,
};

void TimeAttack_MainGameLoopPatch() {
    // Vanilla code
    Sub_8000954_SetKeyPressWRAM();
    Sub_80007BC_SoftResetCheck();
    ++ucMainTimer;
    ++usRandomCount;

    // Custom code
    if (UpdateTime > 0) {
        if (++MiscCounter >= 8) {
            if (--UpdateTime == 0) {
                UpdateTime = 0;
                LockTimer = 0;
            }
            MiscCounter = 0;
        }
    } else if (LockTimer > 0) {
        LockTimer--;
    }

    // Pause menu
    if (GlobalGameMode == 4) {
        if ( TimeDisplay ) {
            // MSec 1-digit
            REG_DMA3SAD = NUM_CHAR + (MSecTableDigit1[FrameDigit2*10 + FrameDigit1] * 0x20);
            REG_DMA3DAD = (VRAM + 0x11120);
            REG_DMA3CNT = 0x80000010;
            // MSec 2-digit
            REG_DMA3SAD = MSC_CHAR + (MSecTableDigit2[FrameDigit2*10 + FrameDigit1] * 0x20);
            REG_DMA3DAD = (VRAM + 0x11100);
            REG_DMA3CNT = 0x80000010;
        } else {
            // Frames 1-digit
            REG_DMA3SAD = NUM_CHAR + (FrameDigit1 * 0x20);
            REG_DMA3DAD = (VRAM + 0x11120);
            REG_DMA3CNT = 0x80000010;
            // Frames 2-digit
            REG_DMA3SAD = NUM_CHAR + (FrameDigit2 * 0x20);
            REG_DMA3DAD = (VRAM + 0x11100);
            REG_DMA3CNT = 0x80000010;
        }
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
    } else if (GlobalGameMode == 2) {
        if (InPassageLevelID >= 4) {
            // Boss
            if (UpdateTime % 2 == 0) {
                // Clock icon
                REG_DMA3SAD = B_CLK_CHAR;
                REG_DMA3DAD = (VRAM + 0x11600);
                REG_DMA3CNT = 0x80000010;
                // Blank
                REG_DMA3SAD = BLK_CHAR;
                REG_DMA3DAD = (VRAM + 0x116E0);
                REG_DMA3CNT = 0x80000010;
                if ( TimeDisplay ) {
                    // MSec 1-digit
                    REG_DMA3SAD = B_NUM_CHAR + (MSecTableDigit1[FrameDigit2*10 + FrameDigit1] * 0x20);
                    REG_DMA3DAD = (VRAM + 0x116C0);
                    REG_DMA3CNT = 0x80000010;
                    // MSec 2-digit
                    REG_DMA3SAD = B_MSC_CHAR + (MSecTableDigit2[FrameDigit2*10 + FrameDigit1] * 0x20);
                    REG_DMA3DAD = (VRAM + 0x116A0);
                    REG_DMA3CNT = 0x80000010;
                } else {
                    // Frames 1-digit
                    REG_DMA3SAD = B_NUM_CHAR + (FrameDigit1 * 0x20);
                    REG_DMA3DAD = (VRAM + 0x116C0);
                    REG_DMA3CNT = 0x80000010;
                    // Frames 2-digit
                    REG_DMA3SAD = B_NUM_CHAR + (FrameDigit2 * 0x20);
                    REG_DMA3DAD = (VRAM + 0x116A0);
                    REG_DMA3CNT = 0x80000010;
                }
                // Seconds 1-digit
                REG_DMA3SAD = B_APO_CHAR + (SecondDidit1 * 0x20);
                REG_DMA3DAD = (VRAM + 0x11680);
                REG_DMA3CNT = 0x80000010;
                // Seconds 2-digit
                REG_DMA3SAD = B_NUM_CHAR + (SecondDidit2 * 0x20);
                REG_DMA3DAD = (VRAM + 0x11660);
                REG_DMA3CNT = 0x80000010;
                // Minutes 1-digit
                REG_DMA3SAD = B_APO_CHAR + (MinuteDidit1 * 0x20);
                REG_DMA3DAD = (VRAM + 0x11640);
                REG_DMA3CNT = 0x80000010;
                // Minutes 2-digit
                REG_DMA3SAD = B_NUM_CHAR + (MinuteDidit2 * 0x20);
                REG_DMA3DAD = (VRAM + 0x11620);
                REG_DMA3CNT = 0x80000010;
            } else {
                // Clock icon
                REG_DMA3SAD = B_CLK_CHAR;
                REG_DMA3DAD = (VRAM + 0x11600);
                REG_DMA3CNT = 0x80000010;
                // Blank
                REG_DMA3SAD = BLK_CHAR;
                REG_DMA3DAD = (VRAM + 0x116E0);
                REG_DMA3CNT = 0x80000010;
                // Frames 1-digit
                REG_DMA3DAD = (VRAM + 0x116C0);
                REG_DMA3CNT = 0x80000010;
                // Frames 2-digit
                REG_DMA3DAD = (VRAM + 0x116A0);
                REG_DMA3CNT = 0x80000010;
                // Seconds 1-digit
                REG_DMA3DAD = (VRAM + 0x11680);
                REG_DMA3CNT = 0x80000010;
                // Seconds 2-digit
                REG_DMA3DAD = (VRAM + 0x11660);
                REG_DMA3CNT = 0x80000010;
                // Minutes 1-digit
                REG_DMA3DAD = (VRAM + 0x11640);
                REG_DMA3CNT = 0x80000010;
                // Minutes 2-digit
                REG_DMA3DAD = (VRAM + 0x11620);
                REG_DMA3CNT = 0x80000010;
            }
        } else {
            // Level
            if (LockTimer == 0) {
                if (UpdateTime % 2 == 0) {
                    if ( TimeDisplay ) {
                        // MSec 1-digit
                        REG_DMA3SAD = NUM_CHAR + (MSecTableDigit1[FrameDigit2*10 + FrameDigit1] * 0x20);
                        REG_DMA3DAD = (VRAM + 0x11120);
                        REG_DMA3CNT = 0x80000010;
                        // MSec 2-digit
                        REG_DMA3SAD = MSC_CHAR + (MSecTableDigit2[FrameDigit2*10 + FrameDigit1] * 0x20);
                        REG_DMA3DAD = (VRAM + 0x11100);
                        REG_DMA3CNT = 0x80000010;
                    } else {
                        // Frames 1-digit
                        REG_DMA3SAD = NUM_CHAR + (FrameDigit1 * 0x20);
                        REG_DMA3DAD = (VRAM + 0x11120);
                        REG_DMA3CNT = 0x80000010;
                        // Frames 2-digit
                        REG_DMA3SAD = NUM_CHAR + (FrameDigit2 * 0x20);
                        REG_DMA3DAD = (VRAM + 0x11100);
                        REG_DMA3CNT = 0x80000010;
                    }
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
                } else {
                    // Frames 1-digit
                    REG_DMA3SAD = BLK_CHAR;
                    REG_DMA3DAD = (VRAM + 0x11120);
                    REG_DMA3CNT = 0x80000010;
                    // Frames 2-digit
                    REG_DMA3DAD = (VRAM + 0x11100);
                    REG_DMA3CNT = 0x80000010;
                    // Seconds 1-digit
                    REG_DMA3DAD = (VRAM + 0x110E0);
                    REG_DMA3CNT = 0x80000010;
                    // Seconds 2-digit
                    REG_DMA3DAD = (VRAM + 0x110C0);
                    REG_DMA3CNT = 0x80000010;
                    // Minutes 1-digit
                    REG_DMA3DAD = (VRAM + 0x110A0);
                    REG_DMA3CNT = 0x80000010;
                    // Minutes 2-digit
                    REG_DMA3DAD = (VRAM + 0x11080);
                    REG_DMA3CNT = 0x80000010;
                }
            } else {
                if (UpdateTime % 2 == 0) {
                    if ( TimeDisplay ) {
                        // MSec 1-digit
                        REG_DMA3SAD = NUM_CHAR + (MSecTableDigit1[DeltaTime[1]*10 + DeltaTime[0]] * 0x20);
                        REG_DMA3DAD = (VRAM + 0x11120);
                        REG_DMA3CNT = 0x80000010;
                        // MSec 2-digit
                        REG_DMA3SAD = MSC_CHAR + (MSecTableDigit2[DeltaTime[1]*10 + DeltaTime[0]] * 0x20);
                        REG_DMA3DAD = (VRAM + 0x11100);
                        REG_DMA3CNT = 0x80000010;
                    } else {
                        // Frames 1-digit
                        REG_DMA3SAD = NUM_CHAR + (DeltaTime[0] * 0x20);
                        REG_DMA3DAD = (VRAM + 0x11120);
                        REG_DMA3CNT = 0x80000010;
                        // Frames 2-digit
                        REG_DMA3SAD = NUM_CHAR + (DeltaTime[1] * 0x20);
                        REG_DMA3DAD = (VRAM + 0x11100);
                        REG_DMA3CNT = 0x80000010;
                    }
                    // Seconds 1-digit
                    REG_DMA3SAD = APO_CHAR + (DeltaTime[2] * 0x20);
                    REG_DMA3DAD = (VRAM + 0x110E0);
                    REG_DMA3CNT = 0x80000010;
                    // Seconds 2-digit
                    REG_DMA3SAD = NUM_CHAR + (DeltaTime[3] * 0x20);
                    REG_DMA3DAD = (VRAM + 0x110C0);
                    REG_DMA3CNT = 0x80000010;
                    // Minutes 1-digit
                    REG_DMA3SAD = APO_CHAR + (DeltaTime[4] * 0x20);
                    REG_DMA3DAD = (VRAM + 0x110A0);
                    REG_DMA3CNT = 0x80000010;
                    // Minutes 2-digit
                    REG_DMA3SAD = NUM_CHAR + (DeltaTime[5] * 0x20);
                    REG_DMA3DAD = (VRAM + 0x11080);
                    REG_DMA3CNT = 0x80000010;
                } else { // Blink timer when ahead
                    // Frames 1-digit
                    REG_DMA3SAD = BLK_CHAR;
                    REG_DMA3DAD = (VRAM + 0x11120);
                    REG_DMA3CNT = 0x80000010;
                    // Frames 2-digit
                    REG_DMA3DAD = (VRAM + 0x11100);
                    REG_DMA3CNT = 0x80000010;
                    // Seconds 1-digit
                    REG_DMA3DAD = (VRAM + 0x110E0);
                    REG_DMA3CNT = 0x80000010;
                    // Seconds 2-digit
                    REG_DMA3DAD = (VRAM + 0x110C0);
                    REG_DMA3CNT = 0x80000010;
                    // Minutes 1-digit
                    REG_DMA3DAD = (VRAM + 0x110A0);
                    REG_DMA3CNT = 0x80000010;
                    // Minutes 2-digit
                    REG_DMA3DAD = (VRAM + 0x11080);
                    REG_DMA3CNT = 0x80000010;
                }
            }
        }
    }
}
