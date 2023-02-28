// @Description TimeAttack_Sub_801C1C0_LoadNewRoom
// @HookAddress 0x1C218
// @HookString 01 48 86 46 01 48 00 47 59 C2 01 08 P
// Mode: Thumb
// Made by beco

#define unk_8400A68 0x8400A68
#define c_82DF094_cap_Char 0x82DF094
#define kontoge2_Char 0x83B889C
#define mouja_zako_Char 0x83EDC88

#define BossLifeMeterChars ((volatile unsigned long*) 0x878F674)

#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define CurrentRoomId (*(volatile unsigned char*) 0x3000024)

#define BossLife (*(volatile unsigned char*) 0x3006F0C)

#define REG_DMA3SAD (*(volatile unsigned int*) 0x40000D4)
#define REG_DMA3DAD (*(volatile unsigned int*) 0x40000D8)
#define REG_DMA3CNT (*(volatile unsigned int*) 0x40000DC)

#define Sub_80746C0_LoadBasicElementAndHeartTiles ((void (*)()) 0x80746C1)
#define Sub_801C43C_GmWarInit ((void (*)()) 0x801C43D)

void TimeAttack_Sub_801C1C0_LoadNewRoom() {
    // Vanilla code
    REG_DMA3SAD = c_82DF094_cap_Char;
    REG_DMA3DAD = 0x6010B00;
    REG_DMA3CNT = 0x80000080;
    Sub_80746C0_LoadBasicElementAndHeartTiles();

    // Custom code
    if (InPassageLevelID == 4 && CurrentRoomId == 1) {
    // Fix the boss life chars after pause/unpause
        REG_DMA3SAD = BossLifeMeterChars[BossLife];
        REG_DMA3DAD = 0x6012C00;
        REG_DMA3CNT = 0x800000A0;
    // Fix the boss entity chars after pause/unpause
        // Ruby passage boss
        if (PassageID == 2) {
            REG_DMA3SAD = kontoge2_Char;
            REG_DMA3DAD = 0x6013000;
            REG_DMA3CNT = 0x80000800;
        }
        // Golden passage boss
        if (PassageID == 5) {
            REG_DMA3SAD = mouja_zako_Char;
            REG_DMA3DAD = 0x6013000;
            REG_DMA3CNT = 0x80000800;
        }
    }


    // Vanilla code
    REG_DMA3SAD = unk_8400A68;
    REG_DMA3DAD = 0x5000280;
    REG_DMA3CNT = 0x80000040;
    Sub_801C43C_GmWarInit();
}
