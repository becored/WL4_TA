// @Description TimeAttack_SeisanSavePatch
// @HookAddress 0x81262
// @HookString 02 48 86 46 02 48 00 47 00 00 85 12 08 08 P C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46
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
#define SPACE_CHAR 0x869EE68
#define DIAMOND_CHAR 0x869F8C8
#define SLASH_CHAR 0x869F928
#define NUM_CHAR 0x869FC88

// IRAM
#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define CurrentDifficulty (*(volatile unsigned char*) 0x03000017) // 00 for normal, =01 for hard, =02 for S-hard
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define sGameSeq (*(volatile unsigned char*) 0x3000C3C)
#define ADDR_KEY_4 (*(volatile unsigned short*) 0x3001848)
#define bSelIdoFlg (*(volatile unsigned char*) 0x3003C45)
#define ucSelectVector ((volatile unsigned char*) 0x3004700) // 1: into passage, 3: back from passage, 4: into boss level
#define ucKakera1GetFlg (*(volatile unsigned char*) 0x3000C07) // 00(no) 02(yes)
#define ucKakera2GetFlg (*(volatile unsigned char*) 0x3000C08) // 00(no) 02(yes)
#define ucKakera3GetFlg (*(volatile unsigned char*) 0x3000C09) // 00(no) 02(yes)
#define ucKakera4GetFlg (*(volatile unsigned char*) 0x3000C0A) // 00(no) 02(yes)
#define ucCardGetFlg (*(volatile unsigned char*) 0x3000C0B) // 00(no) 02(yes)
#define ucKagiGetFlg (*(volatile unsigned char*) 0x3000C0C) // 00(no) 01(yes)
#define W4ItemStatus ((volatile unsigned char*) 0x3000A68)

// IRAM
#define CountFlag (*(volatile unsigned char*) 0x3006F10)
#define FrameDigit1 (*(volatile unsigned char*) 0x3006F11)
#define FrameDigit2 (*(volatile unsigned char*) 0x3006F12)
#define SecondDidit1 (*(volatile unsigned char*) 0x3006F13)
#define SecondDidit2 (*(volatile unsigned char*) 0x3006F14)
#define MinuteDidit1 (*(volatile unsigned char*) 0x3006F15)
#define MinuteDidit2 (*(volatile unsigned char*) 0x3006F16)

// SRAM
#define BestTimes ((volatile unsigned char*) 0xE000A00)

// Char
#define APO_CHAR 0x869F888
#define NUM_CHAR 0x869FC88

void TimeAttack_SeisanSavePatch() {
    // Vanilla code
    if (ucKagiGetFlg) {
        W4ItemStatus[24 * PassageID + 4 * InPassageLevelID] |= 0x20;
    }

    // Custom code
    int i = (PassageID * 24) + (InPassageLevelID * 6) + (CurrentDifficulty * 144);
    if (ucKakera1GetFlg == 2 && ucKakera2GetFlg == 2 && ucKakera3GetFlg == 2 && ucKakera4GetFlg == 2 && ucKagiGetFlg == 1) {
        if (FrameDigit1+(FrameDigit2*10)+(SecondDidit1*100)+(SecondDidit2*1000)+(MinuteDidit1*10000)+(MinuteDidit2*100000) <
            BestTimes[i]+(BestTimes[i+1]*10)+(BestTimes[i+2]*100)+(BestTimes[i+3]*1000)+(BestTimes[i+4]*10000)+(BestTimes[i+5]*100000)) {
            BestTimes[i] = FrameDigit1;
            BestTimes[i+1] = FrameDigit2;
            BestTimes[i+2] = SecondDidit1;
            BestTimes[i+3] = SecondDidit2;
            BestTimes[i+4] = MinuteDidit1;
            BestTimes[i+5] = MinuteDidit2;
        } else if (BestTimes[i] == 0 && BestTimes[i+1] == 0 &&
                   BestTimes[i+2] == 0 && BestTimes[i+3] == 0 &&
                   BestTimes[i+4] == 0 && BestTimes[i+5] == 0) {
            BestTimes[i] = FrameDigit1;
            BestTimes[i+1] = FrameDigit2;
            BestTimes[i+2] = SecondDidit1;
            BestTimes[i+3] = SecondDidit2;
            BestTimes[i+4] = MinuteDidit1;
            BestTimes[i+5] = MinuteDidit2;
        }
    }
    ucKagiGetFlg = 0; // Remove Keyzer flag for correct level escape cutscene
    CountFlag = 0;
}
