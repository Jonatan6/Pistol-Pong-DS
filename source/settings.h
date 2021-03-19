int settings()
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
	oamSet(&oamMain, 0, 20+18, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 1, 20+18, 20 + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 2, 20+18 - 22, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 3, 20+18 - 22, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 4, 20+18 - 6, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 5, 20+18 - 6, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// P
	oamSet(&oamMain, 6, 44+18, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 7, 44+18, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 8, 44+18 - 22, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 9, 44+18 - 22, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 10, 44+18 - 6, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// T
	oamSet(&oamMain, 11, 68+18, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 12, 68+18 - 14, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 13, 68+18 - 14, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// I
	oamSet(&oamMain, 14, 92+18, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 15, 92+18, 20 + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 16, 92+18 - 14, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 17, 92+18 - 14, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// O
	oamSet(&oamMain, 18, 116+18, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 19, 116+18, 20 + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 20, 116+18 - 22, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 21, 116+18 - 22, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 22, 116+18 - 6, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 23, 116+18 - 6, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	// N
	oamSet(&oamMain, 24, 140+18 - 22, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 25, 140+18 - 22, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 26, 140+18 - 6, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 27, 140+18 - 6, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 28, 140+18+2, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[8], -1, false, false, true, false, false);
	// S
	oamSet(&oamMain, 29, 164+18, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 30, 164+18, 20 + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 31, 164+18, 20 + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
	oamSet(&oamMain, 32, 164+18 - 22, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
	oamSet(&oamMain, 33, 164+18 - 6, 20 + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);

	oamUpdate(&oamMain);

	consoleSetWindow(&bottomScreen, 1, 17, 30, 30);
	iprintf("------------------------------");
	consoleSetWindow(&bottomScreen, 1, 20, 30, 30);
	iprintf("      RETURN TO THE GAME");


	while(1)
	{
		touchRead(&touch);

		if (touch.px > 0 && touch.py < 48)
		{
			oamClear(&oamMain, 0, 0);
			break;
		}
	}

	return 0;
}
