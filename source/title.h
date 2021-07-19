int title_screen()
{
	int difficulty = 0;

	vramSetBankC(VRAM_C_SUB_BG);

	PrintConsole bottomScreen;
	consoleInit(&bottomScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);;

	touchPosition touch;
	touchRead(&touch);

	consoleSelect(&bottomScreen);
	consoleSetWindow(&bottomScreen, 1, 17, 30, 30);
	iprintf("       VS OTHER PLAYER");
	consoleSetWindow(&bottomScreen, 1, 11, 30, 30);
	iprintf("------------------------------");
	consoleSetWindow(&bottomScreen, 1, 5, 30, 30);
	iprintf("         VS COMPUTER");

	while(touch.px > 0 && touch.py > 0)
	{
		touchRead(&touch);
	}

	while(1)
	{
		touchRead(&touch);

		if (touch.px > 0 && touch.py < 97)
		{
			consoleClear();
			consoleSetWindow(&bottomScreen, 1, 9, 30, 30);
			iprintf("------------------------------");
			consoleSetWindow(&bottomScreen, 1, 12, 30, 30);
			iprintf("            MEDIUM");
			consoleSetWindow(&bottomScreen, 1, 15, 30, 30);
			iprintf("------------------------------");
			consoleSetWindow(&bottomScreen, 1, 18, 30, 30);
			iprintf("             HARD");
			consoleSetWindow(&bottomScreen, 1, 6, 30, 30);
			iprintf("             EASY");

			while(touch.px > 0 && touch.py > 0)
			{
				touchRead(&touch);
			}

			while(1)
			{
				touchRead(&touch);

				if (touch.px > 0 && touch.py < 64)
				{
					difficulty = difficulty + 1;
					break;
				}
				else if (touch.px > 0 && touch.py < 128)
				{
					difficulty = difficulty + 2;
					break;
				}
				else if (touch.px > 0 && touch.py < 192)
				{
					difficulty = difficulty + 3;
					break;
				}
			}
			consoleClear();
			break;
		}
		else if (touch.px > 0 && touch.py > 97)
		{
			consoleClear();
			break;
		}
	}

	consoleSetWindow(&bottomScreen, 1, 17, 30, 30);
	iprintf("------------------------------");
	consoleSetWindow(&bottomScreen, 1, 11, 30, 30);
	iprintf("      RETURN TO THE MENU");
	consoleSetWindow(&bottomScreen, 1, 5, 30, 30);
	iprintf("------------------------------");
	scanKeys();
	int keys = keysHeld();
	if (keys & KEY_R && keys & KEY_L)
	{
		return difficulty + 10;
	}
	else 
	{
		return difficulty;
	}
}
