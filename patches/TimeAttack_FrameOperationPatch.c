// @Description code will be excute once every frame, modified from UnlimitedRockBouncing
// @HookAddress 0x6C75E
// Mode: Thumb
// Made by Goldensunboy, ssp(shinespeciall)
// Modified by beco
// Verison 1
// P.S. I make changes to the code frequently, so the version is only some kind of release number record -- ssp

/* Hook details
------------------------- this only works when the new function push lr at first and bx lr at last.
0x806C75E: LDR R0, 0x806C767    | 4803
0x806C760: MOV LR, R0           | 4686
0x806C762: LDR R0, pointer      | 4801
0x806C764: BX R0                | 4700
0x806C766: B 0x806C770          | E002
0x806C768: .fill a pointer      | 0XXXXXXX ; end with 1 (in binary) to make it run in thumb mode
0x806C76C: .fill 67C70608       | 0806C767 ; end with 1 (in binary) to make it run in thumb mode
0x806C770: nop                  | 46C0     ; i.e. mov r8, r8
0x806C772: nop....
-------------------------
Hook String:
@HookString 03 48 86 46 01 48 00 47 02 E0 P 67 C7 06 08 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46
count:                                     ^14                                                                     ^38
Hook length: 38 Bytes
*/

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

#define ADDR_KEY_4 (*(volatile unsigned short*) 0x3001848)

// Key control
#define	KEY_L		0x200 // L
#define	KEY_R		0x100 // R
#define	KEY_A		0x001 // A
#define	KEY_B		0x002 // B
#define	KEY_DOWN	0x080 // Down
#define	KEY_UP		0x040 // Up
#define	KEY_LEFT	0x020 // Left
#define	KEY_RIGHT	0x010 // Right
#define	KEY_START	0x008 // Start
#define	KEY_SELECT	0x004 // Select
#define	KEY_ALL		0x3FF // Any key

// IRAM
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
#define PAL_RAM ((volatile unsigned char*) 0x5000000) // PAL RAM
#define VRAM 0x6000000 // VRAM
#define OBJ_MODE0_VRAM 0x6010000 // OBJ Character RAM
#define OAM 0x7000000 // OAM

// SRAM
#define BestTimes ((volatile unsigned char*) 0xE000E00)

// Char
#define APO_CHAR 0x8401CE8
#define NUM_CHAR 0x8403AE8

__attribute__((no_caller_saved_registers))
void TimeAttack_FrameOperationPatch() {
    // Vanilla code for animated tiles loading
    if ( (GameState == 2 || GameState == 6 || GameState == 4 && unk_300001B == 1) && !unk_3000046 ) {
        sub_806E08C();
    }

    // Custom code
    if (cGmStartFlg == 1 && cPauseFlag == 0 && soft_reset == 0) {
        /*
        // Press L to trigger debug mode
        if (ADDR_KEY_4 == KEY_L) {
            if (GameState == 8) {
                GameState = 2;
            } else if (GameState == 2) {
                GameState = 8;
            }
        }
        */

        if (inVortex) {
            CountFlag = 0;
        } else {
            CountFlag = 1;
        }

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
