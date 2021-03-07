#include <nds/input.h>
#include <nds/touch.h>

void title_screen()
{
	PrintConsole topScreen;
	PrintConsole bottomScreen;

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);

	consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
	consoleInit(&bottomScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);

	touchPosition touch;

	consoleSelect(&bottomScreen);
	consoleSetWindow(&bottomScreen, 1, 17, 30, 30);
	iprintf("       VS OTHER PLAYER");
	consoleSetWindow(&bottomScreen, 1, 11, 30, 30);
	iprintf("------------------------------");
	consoleSetWindow(&bottomScreen, 1, 5, 30, 30);
	iprintf("         VS COMPUTER");
	consoleSelect(&topScreen);
	consoleSetWindow(&topScreen, 1, 11, 30, 30);
	iprintf("      TOUCH TO CONTINUE!");

	while(1)
	{
		touchRead(&touch);

		if (touch.px > 0 && touch.py > 97)
		{
			consoleSelect(&topScreen);
			consoleClear();
			consoleSelect(&bottomScreen);
			consoleClear();
			break;
		}
		else if (touch.px > 0 && touch.py < 97)
		{
			consoleSelect(&topScreen);
			consoleClear();
			consoleSelect(&bottomScreen);
			consoleClear();
			break;
		}
	}
}
