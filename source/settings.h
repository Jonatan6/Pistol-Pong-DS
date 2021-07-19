#define SETTINGSX 20
#define SETTINGSY 40

int settings(int choice)
{
	// Clear the top screen
	oamClear(&oamMain, 0, 0);

	vramSetBankC(VRAM_C_SUB_BG);

	PrintConsole bottomScreen;
	consoleInit(&bottomScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);;

	touchPosition touch;
	touchRead(&touch);

	// Draw the word "OPTIONS" on the top screen

	// O
	oamSet(&oamMain, 0, SETTINGSX+18, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 1, SETTINGSX+18, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 2, SETTINGSX+18 - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 3, SETTINGSX+18 - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 4, SETTINGSX+18 - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 5, SETTINGSX+18 - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// P
	oamSet(&oamMain, 6, 24+SETTINGSX+18, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 7, 24+SETTINGSX+18, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 8, 24+SETTINGSX+18 - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 9, 24+SETTINGSX+18 - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 10, 24+SETTINGSX+18 - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// T
	oamSet(&oamMain, 11, 24+24+SETTINGSX+18, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 12, 24+24+SETTINGSX+18 - 14, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 13, 24+24+SETTINGSX+18 - 14, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// I
	oamSet(&oamMain, 14, 24+24+24+SETTINGSX+18, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 15, 24+24+24+SETTINGSX+18, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 16, 24+24+24+SETTINGSX+18 - 14, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 17, 24+24+24+SETTINGSX+18 - 14, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// O
	oamSet(&oamMain, 18, 24+24+24+24+SETTINGSX+18, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 19, 24+24+24+24+SETTINGSX+18, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 20, 24+24+24+24+SETTINGSX+18 - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 21, 24+24+24+24+SETTINGSX+18 - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 22, 24+24+24+24+SETTINGSX+18 - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 23, 24+24+24+24+SETTINGSX+18 - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// N
	oamSet(&oamMain, 24, 24+24+24+24+24+SETTINGSX+18 - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 25, 24+24+24+24+24+SETTINGSX+18 - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 26, 24+24+24+24+24+SETTINGSX+18 - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 27, 24+24+24+24+24+SETTINGSX+18 - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 28, 24+24+24+24+24+SETTINGSX+18+2, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[8], -1, false, false, true, false, false);
	// S
	oamSet(&oamMain, 29, 24+24+24+24+24+24+SETTINGSX+18, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 30, 24+24+24+24+24+24+SETTINGSX+18, SETTINGSY + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 31, 24+24+24+24+24+24+SETTINGSX+18, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 32, 24+24+24+24+24+24+SETTINGSX+18 - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 33, 24+24+24+24+24+24+SETTINGSX+18 - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);

	oamUpdate(&oamMain);

	consoleSetWindow(&bottomScreen, 1, 4, 30, 30);
	iprintf("MYSTERY BOXES     MAGIC BALLS");
	consoleSetWindow(&bottomScreen, 1, 5, 30, 30);

	consoleSetWindow(&bottomScreen, 1, 5, 30, 30);
	iprintf("  ---------        ---------");
	consoleSetWindow(&bottomScreen, 1, 6, 30, 30);
	iprintf("  |       |        |       |");
	consoleSetWindow(&bottomScreen, 1, 7, 30, 30);
	iprintf("  |       |        |       |");
	consoleSetWindow(&bottomScreen, 1, 8, 30, 30);
	iprintf("  |       |        |       |");
	consoleSetWindow(&bottomScreen, 1, 9, 30, 30);
	iprintf("  |       |        |       |");
	consoleSetWindow(&bottomScreen, 1, 10, 30, 30);
	iprintf("  |       |        |       |");
	consoleSetWindow(&bottomScreen, 1, 11, 30, 30);
	iprintf("  |       |        |       |");
	consoleSetWindow(&bottomScreen, 1, 12, 30, 30);
	iprintf("  ---------        ---------");


	consoleSetWindow(&bottomScreen, 1, 17, 30, 30);
	iprintf("------------------------------");
	consoleSetWindow(&bottomScreen, 1, 20, 30, 30);
	iprintf("      RETURN TO THE GAME");


	while(1)
	{
		touchRead(&touch);
		scanKeys();
		int keys = keysHeld();
		if (keys & KEY_TOUCH)
		{
			if (touch.px > 16 && touch.py < 32)
			{
				switch (choice)
				{
					case 0:
						consoleSetWindow(&bottomScreen, 1, 8, 30, 30);
						iprintf("  |   X   |        |       |");
						choice = 1;
						break;
					case 1:
						consoleSetWindow(&bottomScreen, 1, 8, 30, 30);
						iprintf("  |       |        |       |");
						choice = 0;
						break;
					case 2:
						consoleSetWindow(&bottomScreen, 1, 8, 30, 30);
						iprintf("  |   X   |        |   X   |");
						choice = 3;
						break;
					case 3:
						consoleSetWindow(&bottomScreen, 1, 8, 30, 30);
						iprintf("  |       |        |   X   |");
						choice = 2;
						break;
				}
			}
			else if (touch.px < 32 && touch.py < 32)
			{
				switch(choice)
				{
					case 0:
						consoleSetWindow(&bottomScreen, 1, 8, 30, 30);
						iprintf("  |       |        |   X   |");
						choice = 2;
						break;
					case 1:
						consoleSetWindow(&bottomScreen, 1, 8, 30, 30);
						iprintf("  |   X   |        |   X   |");
						choice = 3;
						break;
					case 2:
						consoleSetWindow(&bottomScreen, 1, 8, 30, 30);
						iprintf("  |       |        |       |");
						choice = 0;
						break;
					case 3:
						consoleSetWindow(&bottomScreen, 1, 8, 30, 30);
						iprintf("  |   X   |        |       |");
						choice = 1;
						break;
				}
			}
			else if ((touch.px > 0 && touch.py > 148) || keys & KEY_SELECT || keys & KEY_START)
			{
				oamClear(&oamMain, 0, 0);

				// Draw the dotted line again, since it got cleared
				for(int i=7, f=4; i != 19; i++, f+=16)
				{
					oamSet(&oamMain, i, 123, f, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
				}

				break;
			}
		}
	}

	return choice;
}
