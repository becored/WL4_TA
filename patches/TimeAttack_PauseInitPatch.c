// @Description TimeAttack_PauseInitPatch
// @HookAddress 0x88DEC
// @HookString 01 48 86 46 01 48 00 47 11 8E 08 08 P C0 46 C0 46
// Mode: Thumb
// Made by beco

// Data
#define VRAM 0x6000000
#define APO_CHAR 0x869F888
#define NUM_CHAR 0x869FC88
#define VLK_CHAR 0x869EE68

// IRAM
#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define CurrentDifficulty (*(volatile unsigned char*) 0x03000017) // 00 for normal, =01 for hard, =02 for S-hard
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define sDmapWindowUpY (*(volatile unsigned short*) 0x3003C50)
#define sDmapWindowDownY (*(volatile unsigned short*) 0x3003C52)
#define ucPauseKakeraStatus ((volatile unsigned char*) 0x30047B0)

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

void TimeAttack_PauseInitPatch() {
    // Custom code
    int i = (PassageID * 24) + (InPassageLevelID * 6) + (CurrentDifficulty * 144);
    // Hidden best time
    if (BestTimes[i] == 0 && BestTimes[i+1] == 0 &&
        BestTimes[i+2] == 0 && BestTimes[i+3] == 0 &&
        BestTimes[i+4] == 0 && BestTimes[i+5] == 0) {
        for(int i = 0; i < 6; i ++) {
            REG_DMA3SAD = VLK_CHAR;
            REG_DMA3DAD = (VRAM + 0x2A80 + (i * 0x20));
            REG_DMA3CNT = 0x80000010;
        }
    // Visible best time
    } else {
        // Frames 1-digit
        REG_DMA3SAD = NUM_CHAR + (BestTimes[i] * 0x20);
        REG_DMA3DAD = (VRAM + 0x02B20);
        REG_DMA3CNT = 0x80000010;
        // Frames 2-digit
        REG_DMA3SAD = NUM_CHAR + (BestTimes[i+1] * 0x20);
        REG_DMA3DAD = (VRAM + 0x02B00);
        REG_DMA3CNT = 0x80000010;
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
