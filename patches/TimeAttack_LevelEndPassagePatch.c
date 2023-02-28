// @Description TimeAttack_LevelEndPassagePatch
// @HookAddress 0x7CABA
// @HookString 0248 86460248 00470000 d3ca0708 P
// Mode: Thumb
// Made by beco

// Data
#define VRAM 0x6000000

// IRAM
#define sGameSeq (*(volatile unsigned short*) 0x3000C3C)
#define ucSelectVector (*(volatile unsigned short*) 0x3003C08)
#define ucSeldemoSeq (*(volatile unsigned char*) 0x3003C39)
#define usSeldemoCount (*(volatile unsigned short*) 0x3003C3A)
#define ucSmapWarioStatus (*(volatile unsigned char*) 0x3003CA0)
#define bSmapBlinkStart (*(volatile unsigned char*) 0x3003D54)
#define cGmTime1 (*(volatile unsigned short*) 0x3000BF0) // Frog timer seconds' 2nd digit
#define cGmTime2 (*(volatile unsigned short*) 0x3000BF1) // Frog timer seconds' 1st digit
#define cGmTime3 (*(volatile unsigned short*) 0x3000BF2) // Frog timer minutes

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

// Subroutine
#define Sub_807E768_SmapBlink ((void (*)()) 0x807E769)
#define Sub_807E6EC_SmapUzuRotate ((void (*)()) 0x807E6ED)
#define Sub_807E720_SmapColorChange ((void (*)()) 0x807E721)
#define Sub_807D5C8_SmapStatus ((int (*)()) 0x807D5C9)
#define Sub_806C304_MapBgm_Pause_FadePause ((void (*)()) 0x806C305)

int TimeAttack_LevelEndPassagePatch() {
    // Custom code
    if (RetryFlag){
        // Initialize
        CountFlag = 0;
        MaxFlag = 0;
        FrameDigit1 = 0;
        FrameDigit2 = 0;
        SecondDidit1 = 0;
        SecondDidit2 = 0;
        MinuteDidit1 = 0;
        MinuteDidit2 = 0;
        UpdateTime = 0;
        RetryFlag = 0;
        MiscCounter = 0;
        LockTimer = 0;
        ItemNum = 0;
        LoadEntityStates = 0;
        BossLife = 0;
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

        // Restore frog timer from backup
        cGmTime1 = cGmTimeBackup1;
        cGmTime2 = cGmTimeBackup2;
        cGmTime3 = cGmTimeBackup3;

        sGameSeq = 0xA; // Return to level
    } else {
        switch (ucSmapWarioStatus) {
            case 2:  // Sub_807D964_SmapWarioDrop
            case 3: // Sub_807DB74_SmapWarioBossDrop
                /*
                usSeldemoCount = 0;
                ucSeldemoSeq = 0;
                ucSelectVector = 1;
                */
                Sub_806C304_MapBgm_Pause_FadePause(); // Remove boss level BGM
                ucSeldemoSeq = 4;
                break;
            case 4: // Sub_807DDCC_SmapWarioOut
                ucSeldemoSeq = 6;
                break;
            default:
                break;
        }
    }

    // Vanilla code
    if (bSmapBlinkStart) {
      Sub_807E768_SmapBlink();
    }
    Sub_807E6EC_SmapUzuRotate();
    Sub_807E720_SmapColorChange();
    return Sub_807D5C8_SmapStatus();
}
