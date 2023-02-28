// @Description TimeAttack_GameDeletePatch
// @HookAddress 0x9286C
// @HookString 01 48 86 46 01 48 00 47 CB 28 09 08 P C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46
// Mode: Thumb
// Made by beco

// IRAM
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define sGameSeq (*(volatile unsigned short*) 0x3000C3C)
#define cNextFlg (*(volatile unsigned char*) 0x3000C3E)
#define usFadeTimer (*(volatile unsigned short*) 0x300188E)
#define ucDelete (*(volatile unsigned short*) 0x3004AB8)

// I/O
#define REG_BLDCNT (*(volatile unsigned short*) 0x4000050)

// Subroutine
#define sub_80928E4 ((int (*)()) 0x80928E5)

// SRAM
#define LastDifficulty (*(volatile unsigned char*) 0xE0009F0)
#define BestTimes ((volatile unsigned char*) 0xE000A00)
#define BestTimes_Boss ((volatile unsigned char*) 0xE000BA0)
#define LapTimes ((volatile unsigned char*) 0xE000C10)

void TimeAttack_GameDeletePatch() {
    // Vanilla code
    cNextFlg = sub_80928E4();
    if ( cNextFlg ) {
        ++sGameSeq;
        usFadeTimer = 0;
        if ( cNextFlg != 1 ) {
            REG_BLDCNT = 255;
        }
        // Custom code
        // Initialize best times
        /*
        if ( ucDelete == 3 ) {
            LastDifficulty = 0;
            for (int i = 0; i <= 432; i++) {
                BestTimes[i] = 0;
            }
        }
        */
    }
}
