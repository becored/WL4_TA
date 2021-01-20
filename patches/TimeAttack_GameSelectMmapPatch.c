// @Description TimeAttack_GameSelectMmapPatch
// @HookAddress 0x7A0B8
// @HookString 01 48 86 46 01 48 00 47 6B A3 07 08 P C0 46 C0 46 C0 46 C0 46 C0 46 C0 46
// Mode: Thumb
// Made by beco

// Data
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

#define VRAM 0x6000000

// IRAM
#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define CurrentDifficulty (*(volatile unsigned char*) 0x03000017) // 00 for normal, =01 for hard, =02 for S-hard
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define sGameSeq (*(volatile unsigned char*) 0x3000C3C)
#define bSelIdoFlg (*(volatile unsigned char*) 0x3003C45)
#define ucSelectVector ((volatile unsigned char*) 0x3004700) // 1: into passage, 3: back from passage, 4: into boss level
#define W4ItemStatus ((volatile unsigned char*) 0x3000A68)
#define ADDR_KEY_4 (*(volatile unsigned short*) 0x3001848)
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
#define cGmTimeBackup1 (*(volatile unsigned char*) 0x3006F20) // Frog timer backup seconds' 2nd digit
#define cGmTimeBackup2 (*(volatile unsigned char*) 0x3006F21) // Frog timer backup seconds' 1st digit
#define cGmTimeBackup3 (*(volatile unsigned char*) 0x3006F22) // Frog timer backup minutes

// I/O
#define REG_DMA3SAD (*(volatile unsigned int*) 0x40000D4)
#define REG_DMA3DAD (*(volatile unsigned int*) 0x40000D8)
#define REG_DMA3CNT (*(volatile unsigned int*) 0x40000DC)

// VRAM
#define MapCrown1 (*(volatile unsigned short*) 0x600C4A0)
#define MapCrown2 (*(volatile unsigned short*) 0x600C4A2)
#define MapCrown3 (*(volatile unsigned short*) 0x600C4E0)
#define MapCrown4 (*(volatile unsigned short*) 0x600C4E2)

// Subroutine
#define sub_80845F0 ((int (*)()) 0x80845F1)
#define sub_807A700 ((int (*)()) 0x807A701)
#define sub_8001DA4_m4aSongNumStart ((int (*)(int)) 0x8001DA5)

// SRAM
#define BestTimes ((volatile unsigned char*) 0xE000A00)

// Char
#define NORMAL1_CHAR 0x869EF88
#define NORMAL2_CHAR 0x869F388
#define HARD1_CHAR 0x869F708
#define HARD2_CHAR 0x869FB08
#define SHARD1_CHAR 0x869F648
#define SHARD2_CHAR 0x869FA48
#define APO_CHAR 0x869F888
#define NUM_CHAR 0x869FC88
#define VLK_CHAR 0x869EE68

__attribute__((no_caller_saved_registers))
void TimeAttack_GameSelectMmapPatch() {
    // Vanilla code
    if (sub_80845F0() && sub_807A700()) {
        sGameSeq = 0x24;
    }

    // Custom code
    // Initialize timer
    MaxFlag = 0;
    CountFlag = 0;
    FrameDigit1 = 0;
    FrameDigit2 = 0;
    SecondDidit1 = 0;
    SecondDidit2 = 0;
    MinuteDidit1 = 0;
    MinuteDidit2 = 0;

    // Frog timer backup for retry
    cGmTimeBackup1 = cGmTime1;
    cGmTimeBackup2 = cGmTime2;
    cGmTimeBackup3 = cGmTime3;

    // Hidden clown
    MapCrown1 = 0;
    MapCrown2 = 0;
    MapCrown3 = 0;
    MapCrown4 = 0;

    // Difficulty select
    if (ADDR_KEY_4 == KEY_SELECT) {
        CurrentDifficulty ++;
        if (CurrentDifficulty > 2) {
            CurrentDifficulty = 0;
        }
        sub_8001DA4_m4aSongNumStart(215);
    }

    // Difficulty VRAM
    if (CurrentDifficulty == 1) {
        REG_DMA3SAD = VLK_CHAR;
        REG_DMA3DAD = (VRAM + 0x2980);
        REG_DMA3CNT = 0x80000020;
        REG_DMA3SAD = VLK_CHAR;
        REG_DMA3DAD = (VRAM + 0x2D80);
        REG_DMA3CNT = 0x80000020;
        REG_DMA3SAD = HARD1_CHAR;
        REG_DMA3DAD = (VRAM + 0x29C0);
        REG_DMA3CNT = 0x80000040;
        REG_DMA3SAD = HARD2_CHAR;
        REG_DMA3DAD = (VRAM + 0x2DC0);
        REG_DMA3CNT = 0x80000040;
    } else if (CurrentDifficulty == 2) {
        REG_DMA3SAD = SHARD1_CHAR;
        REG_DMA3DAD = (VRAM + 0x2980);
        REG_DMA3CNT = 0x80000060;
        REG_DMA3SAD = SHARD2_CHAR;
        REG_DMA3DAD = (VRAM + 0x2D80);
        REG_DMA3CNT = 0x80000060;
    } else {
        REG_DMA3SAD = VLK_CHAR;
        REG_DMA3DAD = (VRAM + 0x2980);
        REG_DMA3CNT = 0x80000010;
        REG_DMA3SAD = VLK_CHAR;
        REG_DMA3DAD = (VRAM + 0x2D80);
        REG_DMA3CNT = 0x80000010;
        REG_DMA3SAD = NORMAL1_CHAR;
        REG_DMA3DAD = (VRAM + 0x29A0);
        REG_DMA3CNT = 0x80000050;
        REG_DMA3SAD = NORMAL2_CHAR;
        REG_DMA3DAD = (VRAM + 0x2DA0);
        REG_DMA3CNT = 0x80000050;
    }

    // Best time VRAM
    int i = (PassageID * 24) + (InPassageLevelID * 6) + (CurrentDifficulty * 144);
    // Hidden best time
    if (ucSelectVector[0] == 1 || ucSelectVector[0] == 3 || bSelIdoFlg == 1 || InPassageLevelID > 3 ||
        (BestTimes[i] == 0 && BestTimes[i+1] == 0 &&
        BestTimes[i+2] == 0 && BestTimes[i+3] == 0 &&
        BestTimes[i+4] == 0 && BestTimes[i+5] == 0)) {
        for(int i = 0; i < 6; i ++) {
            REG_DMA3SAD = VLK_CHAR;
            REG_DMA3DAD = (VRAM + 0x26A0 + (i * 0x20));
            REG_DMA3CNT = 0x80000010;
        }
    // Visible best time
    } else {
        // Frames 1-digit
        REG_DMA3SAD = NUM_CHAR + (BestTimes[i] * 0x20);
        REG_DMA3DAD = (VRAM + 0x02740);
        REG_DMA3CNT = 0x80000010;
        // Frames 2-digit
        REG_DMA3SAD = NUM_CHAR + (BestTimes[i+1] * 0x20);
        REG_DMA3DAD = (VRAM + 0x02720);
        REG_DMA3CNT = 0x80000010;
        // Seconds 1-digit
        REG_DMA3SAD = APO_CHAR + (BestTimes[i+2] * 0x20);
        REG_DMA3DAD = (VRAM + 0x02700);
        REG_DMA3CNT = 0x80000010;
        // Seconds 2-digit
        REG_DMA3SAD = NUM_CHAR + (BestTimes[i+3] * 0x20);
        REG_DMA3DAD = (VRAM + 0x026E0);
        REG_DMA3CNT = 0x80000010;
        // Minutes 1-digit
        REG_DMA3SAD = APO_CHAR + (BestTimes[i+4] * 0x20);
        REG_DMA3DAD = (VRAM + 0x026C0);
        REG_DMA3CNT = 0x80000010;
        // Minutes 2-digit
        REG_DMA3SAD = NUM_CHAR + (BestTimes[i+5] * 0x20);
        REG_DMA3DAD = (VRAM + 0x026A0);
        REG_DMA3CNT = 0x80000010;
    }
}
