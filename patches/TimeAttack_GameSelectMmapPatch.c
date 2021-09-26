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

// VRAM+
#define ItemChar1 ((volatile unsigned short*) 0x600C364)
#define ItemChar2 ((volatile unsigned short*) 0x600C3A4)
#define ItemChar3 ((volatile unsigned short*) 0x600C3E4)
#define ItemChar4 ((volatile unsigned short*) 0x600C424)
#define ItemChar5 ((volatile unsigned short*) 0x600C464)
#define ItemNum1 (*(volatile unsigned short*) 0x600C36C)
#define ItemNum2 (*(volatile unsigned short*) 0x600C3AC)
#define ItemNum3 (*(volatile unsigned short*) 0x600C3EC)
#define ItemNum4 (*(volatile unsigned short*) 0x600C42C)
#define ItemNum5 (*(volatile unsigned short*) 0x600C46C)
#define ClockItem1 ((volatile unsigned short*) 0x600C36C)
#define ClockItem2 ((volatile unsigned short*) 0x600C3AC)
#define ClockItem3 ((volatile unsigned short*) 0x600C3EC)
#define ClockItem4 ((volatile unsigned short*) 0x600C42C)
#define ClockItem5 ((volatile unsigned short*) 0x600C46C)
#define LapTimeItem1 ((volatile unsigned short*) 0x600C36E)
#define LapTimeItem2 ((volatile unsigned short*) 0x600C3AE)
#define LapTimeItem3 ((volatile unsigned short*) 0x600C3EE)
#define LapTimeItem4 ((volatile unsigned short*) 0x600C42E)
#define LapTimeItem5 ((volatile unsigned short*) 0x600C46E)
#define LapTimeItem1 ((volatile unsigned short*) 0x600C36E)
#define MapCrown1 (*(volatile unsigned short*) 0x600C4A0)
#define MapCrown2 (*(volatile unsigned short*) 0x600C4A2)
#define MapCrown3 (*(volatile unsigned short*) 0x600C4E0)
#define MapCrown4 (*(volatile unsigned short*) 0x600C4E2)

// Subroutine
#define sub_80845F0 ((int (*)()) 0x80845F1)
#define sub_807A700 ((int (*)()) 0x807A701)
#define sub_8001DA4_m4aSongNumStart ((int (*)(int)) 0x8001DA5)

// SRAM
#define LastDifficulty (*(volatile unsigned char*) 0xE0009F0)
#define BestTimes ((volatile unsigned char*) 0xE000A00)
#define BestTimes_Boss ((volatile unsigned char*) 0xE000BA0)
#define LapTimes ((volatile unsigned char*) 0xE000C10)

// Char
#define NORMAL1_CHAR 0x87A0400
#define NORMAL2_CHAR 0x87A0600
#define HARD1_CHAR 0x87A04A0
#define HARD2_CHAR 0x87A06A0
#define SHARD1_CHAR 0x87A0520
#define SHARD2_CHAR 0x87A0720
#define ITEM_CHAR 0x87A0800
#define ITEM_NUM_CHAR 0x87A0880
#define APO_CHAR 0x869F888
#define NUM_CHAR 0x869FC88
#define BLK_CHAR 0x869EE68

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
    UpdateTime = 0;
    MiscCounter = 0;
    LockTimer = 0;
    ItemNum = 0;
    for (int i = 0; i < 6; i ++) {
        LapTemps1[i] = 0;
    }
    for (int i = 0; i < 6; i ++) {
        LapTemps2[i] = 0;
    }
    for (int i = 0; i < 6; i ++) {
        LapTemps3[i] = 0;
    }
    for (int i = 0; i < 6; i ++) {
        LapTemps4[i] = 0;
    }
    for (int i = 0; i < 6; i ++) {
        LapTemps5[i] = 0;
    }

    // Frog timer backup for retry
    cGmTimeBackup1 = cGmTime1;
    cGmTimeBackup2 = cGmTime2;
    cGmTimeBackup3 = cGmTime3;

    // Hidden clown
    MapCrown1 = 0;
    MapCrown2 = 0;
    MapCrown3 = 0;
    MapCrown4 = 0;

    // Load Last Difficulty
    if (CurrentDifficulty != LastDifficulty) {
        CurrentDifficulty = LastDifficulty;
    }

    // Difficulty select
    if (ADDR_KEY_4 == KEY_SELECT) {
        CurrentDifficulty ++;
        if (CurrentDifficulty > 2) {
            CurrentDifficulty = 0;
        }
        sub_8001DA4_m4aSongNumStart(215);
        LastDifficulty = CurrentDifficulty;
    }

    // Difficulty VRAM
    if (CurrentDifficulty == 1) {
        REG_DMA3SAD = BLK_CHAR;
        REG_DMA3DAD = (VRAM + 0x2980);
        REG_DMA3CNT = 0x80000020;
        REG_DMA3SAD = BLK_CHAR;
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
        REG_DMA3SAD = BLK_CHAR;
        REG_DMA3DAD = (VRAM + 0x2980);
        REG_DMA3CNT = 0x80000010;
        REG_DMA3SAD = BLK_CHAR;
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
    if (InPassageLevelID == 4) {
        // Boss
        int i = (PassageID * 6) + (CurrentDifficulty * 36);
        // Hidden best time
        if (ucSelectVector[0] == 1 || ucSelectVector[0] == 3 || bSelIdoFlg == 1 || InPassageLevelID == 5 ||
            (BestTimes_Boss[i] == 0 && BestTimes_Boss[i+1] == 0 &&
            BestTimes_Boss[i+2] == 0 && BestTimes_Boss[i+3] == 0 &&
            BestTimes_Boss[i+4] == 0 && BestTimes_Boss[i+5] == 0)) {
            for (int i = 0; i < 6; i ++) {
                REG_DMA3SAD = BLK_CHAR;
                REG_DMA3DAD = (VRAM + 0x26A0 + (i * 0x20));
                REG_DMA3CNT = 0x80000010;
            }
            // ITEM
            REG_DMA3SAD = BLK_CHAR;
            REG_DMA3DAD = (VRAM + 0x2B80);
            REG_DMA3CNT = 0x80000040;
            // Item Numbers
            REG_DMA3SAD = BLK_CHAR;
            REG_DMA3DAD = (VRAM + 0x22C0);
            REG_DMA3CNT = 0x80000050;
        // Visible best time
        } else {
            // Frames 1-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes_Boss[i] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2740);
            REG_DMA3CNT = 0x80000010;
            // Frames 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes_Boss[i+1] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2720);
            REG_DMA3CNT = 0x80000010;
            // Seconds 1-digit
            REG_DMA3SAD = APO_CHAR + (BestTimes_Boss[i+2] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2700);
            REG_DMA3CNT = 0x80000010;
            // Seconds 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes_Boss[i+3] * 0x20);
            REG_DMA3DAD = (VRAM + 0x26E0);
            REG_DMA3CNT = 0x80000010;
            // Minutes 1-digit
            REG_DMA3SAD = APO_CHAR + (BestTimes_Boss[i+4] * 0x20);
            REG_DMA3DAD = (VRAM + 0x26C0);
            REG_DMA3CNT = 0x80000010;
            // Minutes 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes_Boss[i+5] * 0x20);
            REG_DMA3DAD = (VRAM + 0x26A0);
            REG_DMA3CNT = 0x80000010;
        }
    } else {
        // Level
        int i = (PassageID * 24) + (InPassageLevelID * 6) + (CurrentDifficulty * 144);
        // Hidden best time
        if (ucSelectVector[0] == 1 || ucSelectVector[0] == 3 || bSelIdoFlg == 1 || InPassageLevelID == 5 ||
            (BestTimes[i] == 0 && BestTimes[i+1] == 0 &&
            BestTimes[i+2] == 0 && BestTimes[i+3] == 0 &&
            BestTimes[i+4] == 0 && BestTimes[i+5] == 0)) {
            for (int i = 0; i < 6; i ++) {
                // Total Time
                REG_DMA3SAD = BLK_CHAR;
                REG_DMA3DAD = (VRAM + 0x26A0 + (i * 0x20));
                REG_DMA3CNT = 0x80000010;
                // ITEM
                REG_DMA3DAD = (VRAM + 0x2B80);
                REG_DMA3CNT = 0x80000040;
                // Item Numbers
                REG_DMA3DAD = (VRAM + 0x22C0);
                REG_DMA3CNT = 0x80000050;
                // Item 1 Lap Time
                REG_DMA3DAD = (VRAM + 0x2140 + (i * 0x20));
                REG_DMA3CNT = 0x80000010;
                // Item 2 Lap Time
                REG_DMA3DAD = (VRAM + 0x2540 + (i * 0x20));
                REG_DMA3CNT = 0x80000010;
                // Item 3 Lap Time
                REG_DMA3DAD = (VRAM + 0x2200 + (i * 0x20));
                REG_DMA3CNT = 0x80000010;
                // Item 4 Lap Time
                REG_DMA3DAD = (VRAM + 0x2800 + (i * 0x20));
                REG_DMA3CNT = 0x80000010;
                // Item 5 Lap Time
                REG_DMA3DAD = (VRAM + 0x2C00 + (i * 0x20));
                REG_DMA3CNT = 0x80000010;
            }
        // Visible best time
        } else {
            // Total Time
            // Frames 1-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes[i] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2740);
            REG_DMA3CNT = 0x80000010;
            // Frames 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes[i+1] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2720);
            REG_DMA3CNT = 0x80000010;
            // Seconds 1-digit
            REG_DMA3SAD = APO_CHAR + (BestTimes[i+2] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2700);
            REG_DMA3CNT = 0x80000010;
            // Seconds 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes[i+3] * 0x20);
            REG_DMA3DAD = (VRAM + 0x26E0);
            REG_DMA3CNT = 0x80000010;
            // Minutes 1-digit
            REG_DMA3SAD = APO_CHAR + (BestTimes[i+4] * 0x20);
            REG_DMA3DAD = (VRAM + 0x26C0);
            REG_DMA3CNT = 0x80000010;
            // Minutes 2-digit
            REG_DMA3SAD = NUM_CHAR + (BestTimes[i+5] * 0x20);
            REG_DMA3DAD = (VRAM + 0x26A0);
            REG_DMA3CNT = 0x80000010;

            // ITEM
            REG_DMA3SAD = ITEM_CHAR;
            REG_DMA3DAD = (VRAM + 0x2B80);
            REG_DMA3CNT = 0x80000040;
            // Item Numbers
            REG_DMA3SAD = ITEM_NUM_CHAR;
            REG_DMA3DAD = (VRAM + 0x22C0);
            REG_DMA3CNT = 0x80000050;
            int i = (InPassageLevelID * 30) + (PassageID * 120) + (CurrentDifficulty * 720);
            // Item 1 Lap Time
            // Frames 1-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i] * 0x20);
            REG_DMA3DAD = (VRAM + 0x21E0);
            REG_DMA3CNT = 0x80000010;
            // Frames 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+1] * 0x20);
            REG_DMA3DAD = (VRAM + 0x21C0);
            REG_DMA3CNT = 0x80000010;
            // Seconds 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+2] * 0x20);
            REG_DMA3DAD = (VRAM + 0x21A0);
            REG_DMA3CNT = 0x80000010;
            // Seconds 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+3] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2180);
            REG_DMA3CNT = 0x80000010;
            // Minutes 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+4] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2160);
            REG_DMA3CNT = 0x80000010;
            // Minutes 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+5] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2140);
            REG_DMA3CNT = 0x80000010;

            i += 6;
            // Item 2 Lap Time
            // Frames 1-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i] * 0x20);
            REG_DMA3DAD = (VRAM + 0x25E0);
            REG_DMA3CNT = 0x80000010;
            // Frames 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+1] * 0x20);
            REG_DMA3DAD = (VRAM + 0x25C0);
            REG_DMA3CNT = 0x80000010;
            // Seconds 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+2] * 0x20);
            REG_DMA3DAD = (VRAM + 0x25A0);
            REG_DMA3CNT = 0x80000010;
            // Seconds 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+3] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2580);
            REG_DMA3CNT = 0x80000010;
            // Minutes 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+4] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2560);
            REG_DMA3CNT = 0x80000010;
            // Minutes 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+5] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2540);
            REG_DMA3CNT = 0x80000010;

            i += 6;
            // Item 3 Lap Time
            // Frames 1-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i] * 0x20);
            REG_DMA3DAD = (VRAM + 0x22A0);
            REG_DMA3CNT = 0x80000010;
            // Frames 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+1] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2280);
            REG_DMA3CNT = 0x80000010;
            // Seconds 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+2] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2260);
            REG_DMA3CNT = 0x80000010;
            // Seconds 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+3] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2240);
            REG_DMA3CNT = 0x80000010;
            // Minutes 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+4] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2220);
            REG_DMA3CNT = 0x80000010;
            // Minutes 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+5] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2200);
            REG_DMA3CNT = 0x80000010;

            i += 6;
            // Item 4 Lap Time
            // Frames 1-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i] * 0x20);
            REG_DMA3DAD = (VRAM + 0x28A0);
            REG_DMA3CNT = 0x80000010;
            // Frames 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+1] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2880);
            REG_DMA3CNT = 0x80000010;
            // Seconds 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+2] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2860);
            REG_DMA3CNT = 0x80000010;
            // Seconds 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+3] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2840);
            REG_DMA3CNT = 0x80000010;
            // Minutes 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+4] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2820);
            REG_DMA3CNT = 0x80000010;
            // Minutes 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+5] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2800);
            REG_DMA3CNT = 0x80000010;

            i += 6;
            // Item 5 Lap Time
            // Frames 1-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2CA0);
            REG_DMA3CNT = 0x80000010;
            // Frames 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+1] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2C80);
            REG_DMA3CNT = 0x80000010;
            // Seconds 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+2] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2C60);
            REG_DMA3CNT = 0x80000010;
            // Seconds 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+3] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2C40);
            REG_DMA3CNT = 0x80000010;
            // Minutes 1-digit
            REG_DMA3SAD = APO_CHAR + (LapTimes[i+4] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2C20);
            REG_DMA3CNT = 0x80000010;
            // Minutes 2-digit
            REG_DMA3SAD = NUM_CHAR + (LapTimes[i+5] * 0x20);
            REG_DMA3DAD = (VRAM + 0x2C00);
            REG_DMA3CNT = 0x80000010;
        }
    }
    // Layer 0 Mapping
    /*
    // Item Lap Clocks
    for (int i = 0; i < 5; i ++) {
        ClockItem1[i] = 0xC134;
        ClockItem2[i] = 0xC134;
        ClockItem3[i] = 0xC134;
        ClockItem4[i] = 0xC134;
        ClockItem5[i] = 0xC134;
    }
    */
    // Item Chars
    for (int i = 0; i < 4; i ++) {
        ItemChar1[i] = 0xC15C + i;
    }
    // Item Chars
    ItemNum1 = 0xC116;
    ItemNum2 = 0xC117;
    ItemNum3 = 0xC118;
    ItemNum4 = 0xC119;
    ItemNum5 = 0xC11A;
    // Item Lap Times
    for (int i = 0; i < 6; i ++) {
        LapTimeItem1[i] = 0xE10A + i;
        LapTimeItem2[i] = 0xE12A + i;
        LapTimeItem3[i] = 0xE110 + i;
        LapTimeItem4[i] = 0xE140 + i;
        LapTimeItem5[i] = 0xE160 + i;
    }
}
