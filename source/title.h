#include <nds/input.h>
#include <nds/touch.h>

void title_screen()
{
	PrintConsole topScreen;
	PrintConsole bottomScreen;

	consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
	consoleInit(&bottomScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);

	touchPosition touch;
	consoleDemoInit();

	consoleSelect(&topScreen);
	consoleSetWindow(&topScreen, 1, 10, 100, 100);
	iprintf("      TOUCH TO CONTINUE!");
	consoleSelect(&bottomScreen);
	consoleSetWindow(&bottomScreen, 1, 15, 30, 30);
	iprintf("       VS OTHER PLAYER");
	consoleSetWindow(&bottomScreen, 1, 10, 30, 30);
	iprintf("------------------------------");
	consoleSetWindow(&bottomScreen, 1, 5, 30, 30);
	iprintf("         VS COMPUTER");

	while(1)
	{
		touchRead(&touch);

		if (touch.px > 0 && touch.py > 97)
		{
			consoleClear();
			break;
		}
		else if (touch.px > 0 && touch.py < 97)
		{
			consoleClear();
			break;
		}
	}
	consoleClear();
}
