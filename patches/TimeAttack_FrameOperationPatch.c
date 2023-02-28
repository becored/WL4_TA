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

#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define CurrentDifficulty (*(volatile unsigned char*) 0x03000017) // 00 for normal, =01 for hard, =02 for S-hard
#define unk_300001B (*(volatile unsigned char*) 0x300001B)
#define ucGmapSubSeq (*(volatile unsigned char*) 0x3000021)
#define CurrentRoomId (*(volatile unsigned char*) 0x3000024)
#define ucGateNum (*(volatile unsigned char*) 0x3000025)
#define unk_3000046 (*(volatile unsigned char*) 0x3000046)
#define ucSTEndType (*(volatile unsigned char*) 0x3000048)
#define sub_806E08C ((void (*)()) 0x806E08D)

#define cGmStartFlg (*(volatile unsigned char*) 0x3000C3F)
#define cPauseFlag (*(volatile unsigned char*) 0x3000C35)
#define soft_reset (*(volatile unsigned char*) 0x300001E)
#define CurrentEntityInfoList_TEbuf ((volatile unsigned char*) 0x3000104)
#define ucBWorks ((volatile unsigned char*) 0x3000A58)
#define W4ItemStatus ((volatile unsigned char*) 0x3000A68)
#define inVortex (*(volatile unsigned char*) 0x3000C0E)
#define GlobalGameMode (*(volatile unsigned char*) 0x3000C3A)
#define sGameSeq (*(volatile unsigned char*) 0x3000C3C)
#define ucDokan (*(volatile unsigned char*) 0x300189A)
#define WarioHeart (*(volatile unsigned char*) 0x3001910)
#define usWarStopFlg (*(volatile unsigned short*) 0x30019F6)
#define ucTimeUp (*(volatile unsigned char*) 0x3000047) // 01(fighting boss) 02(Losing coins) 03(Losing coins without coin counter) 04(hide coin counter) 10(fade to grayscale) 0f(no interaction between wario and enemies)

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
#define ItemNum (*(volatile unsigned char*) 0x3006F1B)
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
#define PAL_RAM ((volatile unsigned char*) 0x5000000) // PAL RAM
#define PAL_TIMER (*(volatile unsigned char*) 0x500028C)
#define PAL_TIMER_BOSS (*(volatile unsigned char*) 0x50002EA)
#define VRAM 0x6000000 // VRAM
#define OBJ_MODE0_VRAM 0x6010000 // OBJ Character RAM
#define OAM 0x7000000 // OAM

// SRAM
#define BestTimes ((volatile unsigned char*) 0xE000A00)
#define BestTimes_Boss ((volatile unsigned char*) 0xE000BA0)
#define LapTimes ((volatile unsigned char*) 0xE000C10)

// Char
#define APO_CHAR 0x8401CE8
#define NUM_CHAR 0x8403AE8

void TimeAttack_FrameOperationPatch() {
    // Vanilla code for animated tiles loading
    if ( (sGameSeq == 2 || sGameSeq == 6 || sGameSeq == 4 && unk_300001B == 1) && !unk_3000046 ) {
        sub_806E08C();
    }

    // Custom code
    if (InPassageLevelID == 4) {
        // Skip boss corridor
        if (GlobalGameMode == 2 && sGameSeq == 1 && CurrentRoomId == 0) {
            ucGmapSubSeq = 0x08;
            ucGateNum = 0x02;
            ucSTEndType = 0x80;
            sGameSeq = 0x06;
        }
        // Skip boss outro
        if (ucSTEndType == 5 && CurrentRoomId == 1) {
            ucSTEndType = 6;
        }
    }

    // Stop timer when defeating boss
    if (InPassageLevelID == 6) {
        int i = (PassageID * 6) + (CurrentDifficulty * 36);
        if (FrameDigit1+(FrameDigit2*10)+(SecondDidit1*100)+(SecondDidit2*1000)+(MinuteDidit1*10000)+(MinuteDidit2*100000) <
            BestTimes_Boss[i]+(BestTimes_Boss[i+1]*10)+(BestTimes_Boss[i+2]*100)+(BestTimes_Boss[i+3]*1000)+(BestTimes_Boss[i+4]*10000)+(BestTimes_Boss[i+5]*100000)) {
            BestTimes_Boss[i] = FrameDigit1;
            BestTimes_Boss[i+1] = FrameDigit2;
            BestTimes_Boss[i+2] = SecondDidit1;
            BestTimes_Boss[i+3] = SecondDidit2;
            BestTimes_Boss[i+4] = MinuteDidit1;
            BestTimes_Boss[i+5] = MinuteDidit2;
            UpdateTime = 15;
        } else if (BestTimes_Boss[i] == 0 && BestTimes_Boss[i+1] == 0 &&
                   BestTimes_Boss[i+2] == 0 && BestTimes_Boss[i+3] == 0 &&
                   BestTimes_Boss[i+4] == 0 && BestTimes_Boss[i+5] == 0) {
            BestTimes_Boss[i] = FrameDigit1;
            BestTimes_Boss[i+1] = FrameDigit2;
            BestTimes_Boss[i+2] = SecondDidit1;
            BestTimes_Boss[i+3] = SecondDidit2;
            BestTimes_Boss[i+4] = MinuteDidit1;
            BestTimes_Boss[i+5] = MinuteDidit2;
            UpdateTime = 15;
        }
        CountFlag = 0;
        InPassageLevelID = 4;
        // Unlock levels
        for (int i = 16; i < 140; i += 24) {
            // Boss
            W4ItemStatus[i] = 0x07;
        }
    }

    // Stop timer when Wario dies
    if (WarioHeart == 0) {
        CountFlag = 0;
    }

    /*
    if (cGmStartFlg == 1 && cPauseFlag == 0 && soft_reset == 0) {
        // Press L to trigger debug mode
        if (ADDR_KEY_4 == KEY_L) {
            if (sGameSeq == 8) {
                sGameSeq = 2;
            } else if (sGameSeq == 2) {
                sGameSeq = 8;
            }
        }
    }
    */
}
