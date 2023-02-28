// @Description TimeAttack_PauseInitPatch
// @HookAddress 0x88DEC
// @HookString 01 48 86 46 01 48 00 47 11 8E 08 08 P C0 46 C0 46
// Mode: Thumb
// Made by beco

// Data
#define VRAM 0x6000000
#define APO_CHAR 0x869F888
#define MSC_CHAR 0x869EC88
#define NUM_CHAR 0x869FC88
#define BLK_CHAR 0x869EE68

// IRAM
#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define CurrentDifficulty (*(volatile unsigned char*) 0x03000017) // 00 for normal, =01 for hard, =02 for S-hard
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define sDmapWindowUpY (*(volatile unsigned short*) 0x3003C50)
#define sDmapWindowDownY (*(volatile unsigned short*) 0x3003C52)
#define ucPauseKakeraStatus ((volatile unsigned char*) 0x30047B0)

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
#define REG_BG0VOFS (*(volatile unsigned short*) 0x4000012)
#define REG_BG0HOFS (*(volatile unsigned short*) 0x4000010)
#define REG_BG1VOFS (*(volatile unsigned short*) 0x4000016)
#define REG_BG1HOFS (*(volatile unsigned short*) 0x4000014)
#define REG_BG2VOFS (*(volatile unsigned short*) 0x400001A)
#define REG_BG2HOFS (*(volatile unsigned short*) 0x4000018)
#define REG_DMA3SAD (*(volatile unsigned int*) 0x40000D4)
#define REG_DMA3DAD (*(volatile unsigned int*) 0x40000D8)
#define REG_DMA3CNT (*(volatile unsigned int*) 0x40000DC)

// SRAM
#define BestTimes ((volatile unsigned char*) 0xE000A00)
#define BestTimes_Boss ((volatile unsigned char*) 0xE000BA0)

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

void TimeAttack_PauseInitPatch() {
    // Custom code
    int i;
    if (InPassageLevelID == 4) {
        // Boss
        i = (PassageID * 6) + (CurrentDifficulty * 36);
        // Hidden best time
        if (BestTimes_Boss[i] == 0 && BestTimes_Boss[i+1] == 0 &&
            BestTimes_Boss[i+2] == 0 && BestTimes_Boss[i+3] == 0 &&
            BestTimes_Boss[i+4] == 0 && BestTimes_Boss[i+5] == 0) {
            for(int i = 0; i < 6; i ++) {
                REG_DMA3SAD = BLK_CHAR;
                REG_DMA3DAD = (VRAM + 0x2A80 + (i * 0x20));
                REG_DMA3CNT = 0x80000010;
            }
        // Visible best time
        } else {
            if ( TimeDisplay ) {
                // MSec 1-digit
                REG_DMA3SAD = NUM_CHAR + (MSecTableDigit1[BestTimes_Boss[i+1]*10 + BestTimes_Boss[i]] * 0x20);
                REG_DMA3DAD = (VRAM + 0x02B20);
                REG_DMA3CNT = 0x80000010;
                // MSec 2-digit
                REG_DMA3SAD = MSC_CHAR + (MSecTableDigit2[BestTimes_Boss[i+1]*10 + BestTimes_Boss[i]] * 0x20);
                REG_DMA3DAD = (VRAM + 0x02B00);
                REG_DMA3CNT = 0x80000010;
            } else {
                // Frames 1-digit
                REG_DMA3SAD = NUM_CHAR + (BestTimes_Boss[i] * 0x20);
                REG_DMA3DAD = (VRAM + 0x02B20);
                REG_DMA3CNT = 0x80000010;
                // Frames 2-digit
                REG_DMA3SAD = NUM_CHAR + (BestTimes_Boss[i+1] * 0x20);
                REG_DMA3DAD = (VRAM + 0x02B00);
                REG_DMA3CNT = 0x80000010;
            }
            // Seconds 1-digit
            REG_DMA3SAD = APO_CHAR + (BestTimes_Boss[i+2] * 0x20);
            REG_DMA3DAD = (VRAM + 0x02AE0);
            REG_DMA3CNT = 0x80000010;
            // Seconds 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes_Boss[i+3] * 0x20);
            REG_DMA3DAD = (VRAM + 0x02AC0);
            REG_DMA3CNT = 0x80000010;
            // Minutes 1-digit
            REG_DMA3SAD = APO_CHAR + (BestTimes_Boss[i+4] * 0x20);
            REG_DMA3DAD = (VRAM + 0x02AA0);
            REG_DMA3CNT = 0x80000010;
            // Minutes 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes_Boss[i+5] * 0x20);
            REG_DMA3DAD = (VRAM + 0x02A80);
            REG_DMA3CNT = 0x80000010;
        }
    } else {
        // Level
        i = (PassageID * 24) + (InPassageLevelID * 6) + (CurrentDifficulty * 144);
        // Hidden best time
        if (BestTimes[i] == 0 && BestTimes[i+1] == 0 &&
            BestTimes[i+2] == 0 && BestTimes[i+3] == 0 &&
            BestTimes[i+4] == 0 && BestTimes[i+5] == 0) {
            for(int i = 0; i < 6; i ++) {
                REG_DMA3SAD = BLK_CHAR;
                REG_DMA3DAD = (VRAM + 0x2A80 + (i * 0x20));
                REG_DMA3CNT = 0x80000010;
            }
        // Visible best time
        } else {
            if ( TimeDisplay ) {
                // MSec 1-digit
                REG_DMA3SAD = NUM_CHAR + (MSecTableDigit1[BestTimes[i+1]*10 + BestTimes[i]] * 0x20);
                REG_DMA3DAD = (VRAM + 0x02B20);
                REG_DMA3CNT = 0x80000010;
                // MSec 2-digit
                REG_DMA3SAD = MSC_CHAR + (MSecTableDigit2[BestTimes[i+1]*10 + BestTimes[i]] * 0x20);
                REG_DMA3DAD = (VRAM + 0x02B00);
                REG_DMA3CNT = 0x80000010;
            } else {
                // Frames 1-digit
                REG_DMA3SAD = NUM_CHAR + (BestTimes[i] * 0x20);
                REG_DMA3DAD = (VRAM + 0x02B20);
                REG_DMA3CNT = 0x80000010;
                // Frames 2-digit
                REG_DMA3SAD = NUM_CHAR + (BestTimes[i+1] * 0x20);
                REG_DMA3DAD = (VRAM + 0x02B00);
                REG_DMA3CNT = 0x80000010;
            }
            // Seconds 1-digit
            REG_DMA3SAD = APO_CHAR + (BestTimes[i+2] * 0x20);
            REG_DMA3DAD = (VRAM + 0x02AE0);
            REG_DMA3CNT = 0x80000010;
            // Seconds 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes[i+3] * 0x20);
            REG_DMA3DAD = (VRAM + 0x02AC0);
            REG_DMA3CNT = 0x80000010;
            // Minutes 1-digit
            REG_DMA3SAD = APO_CHAR + (BestTimes[i+4] * 0x20);
            REG_DMA3DAD = (VRAM + 0x02AA0);
            REG_DMA3CNT = 0x80000010;
            // Minutes 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes[i+5] * 0x20);
            REG_DMA3DAD = (VRAM + 0x02A80);
            REG_DMA3CNT = 0x80000010;
        }
    }

    // Vanilla code
    sDmapWindowUpY = 160;
    sDmapWindowDownY = 160;
    REG_BG0VOFS = 0;
    REG_BG0HOFS = 0;
    REG_BG1VOFS = 0;
    REG_BG1HOFS = 0;
    REG_BG2VOFS = 0;
    REG_BG2HOFS = 0;
}
