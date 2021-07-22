#include <nds.h>
#include <stdio.h>
#include <time.h>
#include <nds/input.h>
#include <nds/touch.h>

#include "sprites.h"

#define VERTICAL_LINE 6
#define HORIZONTAL_LINE 7
#define DIAGONAL_LINE 8

#define SETTINGSX 40
#define SETTINGSY 40

int title_screen()
{
	int difficulty = 0;

	vramSetBankC(VRAM_C_SUB_BG);

	PrintConsole bottomScreen;
	consoleInit(&bottomScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);

	touchPosition touch;
	touchRead(&touch);

	consoleSelect(&bottomScreen);
	//oamSet(&oamMain, 120, 20, 20, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, paddle.sprite_gfx_mem[3], -1, false, false, false, false, false);

	// Make text fall from the sky
	for (int i = 0; i < 18; i++)
	{
		consoleClear();

		consoleSetWindow(&bottomScreen, 1, i, 30, 30);
		iprintf("       VS OTHER PLAYER");
		consoleSetWindow(&bottomScreen, 1, i-6, 30, 30);
		iprintf("------------------------------");
		consoleSetWindow(&bottomScreen, 1, i-12, 30, 30);
		iprintf("         VS COMPUTER");

		// Wait two frames
		swiWaitForVBlank();
		swiWaitForVBlank();
	}

	while (touch.px > 0 && touch.py > 0)
	{
		touchRead(&touch);
	}

	while (1)
	{
		touchRead(&touch);

		if (touch.px > 0 && touch.py < 97)
		{
			// Make text fall from the sky
			for (int i = 0; i < 19; i++)
			{
				consoleClear();

				consoleSetWindow(&bottomScreen, 1, i, 30, 30);
				iprintf("             HARD");
				consoleSetWindow(&bottomScreen, 1, i-3, 30, 30);
				iprintf("------------------------------");
				consoleSetWindow(&bottomScreen, 1, i-6, 30, 30);
				iprintf("            MEDIUM");
				consoleSetWindow(&bottomScreen, 1, i-9, 30, 30);
				iprintf("------------------------------");
				consoleSetWindow(&bottomScreen, 1, i-12, 30, 30);
				iprintf("             EASY");
				
				// Wait two frames
				swiWaitForVBlank();
				swiWaitForVBlank();
			}

			while (touch.px > 0 && touch.py > 0)
			{
				touchRead(&touch);
			}

			while (1)
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

	// Make text fall from the sky
	for (int i = 0; i < 18; i++)
	{
		consoleClear();

		consoleSetWindow(&bottomScreen, 1, i, 30, 30);
		iprintf("------------------------------");
		consoleSetWindow(&bottomScreen, 1, i-6, 30, 30);
		iprintf("      RETURN TO THE MENU");
		consoleSetWindow(&bottomScreen, 1, i-12, 30, 30);
		iprintf("------------------------------");

		// Wait two frames
		swiWaitForVBlank();
		swiWaitForVBlank();
	}

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

int settings(int choice)
{
	// Clear the top screen
	oamClear(&oamMain, 0, 0);

	vramSetBankC(VRAM_C_SUB_BG);

	PrintConsole bottomScreen;
	consoleInit(&bottomScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);

	touchPosition touch;
	touchRead(&touch);

	// Draw the word "OPTIONS" on the top screen

	// O
	oamSet(&oamMain, 0, SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 1, SETTINGSX, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 2, SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 3, SETTINGSX - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 4, SETTINGSX - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 5, SETTINGSX - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// P
	oamSet(&oamMain, 6, 24*1+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 7, 24*1+SETTINGSX, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 8, 24*1+SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 9, 24*1+SETTINGSX - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 10, 24*1+SETTINGSX - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// T
	oamSet(&oamMain, 11, 24*2+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 12, 24*2+SETTINGSX - 14, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 13, 24*2+SETTINGSX - 14, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// I
	oamSet(&oamMain, 14, 24*3+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 15, 24*3+SETTINGSX, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 16, 24*3+SETTINGSX - 14, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 17, 24*3+SETTINGSX - 14, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// O
	oamSet(&oamMain, 18, 24*4+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 19, 24*4+SETTINGSX, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 20, 24*4+SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 21, 24*4+SETTINGSX - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 22, 24*4+SETTINGSX - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 23, 24*4+SETTINGSX - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// N
	oamSet(&oamMain, 24, 24*5+SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 25, 24*5+SETTINGSX - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 26, 24*5+SETTINGSX - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 27, 24*5+SETTINGSX - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 28, 24*5+SETTINGSX+2, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[DIAGONAL_LINE], -1, false, false, true, false, false);
	// S
	oamSet(&oamMain, 29, 24*6+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 30, 24*6+SETTINGSX, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 31, 24*6+SETTINGSX, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 32, 24*6+SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 33, 24*6+SETTINGSX - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);

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

	while (1)
	{
		int keys;

		// Stay in loop until nothing is touched and no key is pressed
		while (keys & KEY_TOUCH || keys & KEY_START || keys & KEY_SELECT || keys & KEY_LEFT || keys & KEY_RIGHT)
		{
			scanKeys();
			keys = keysHeld();
		}

		// Stay in loop until something is touched or a key is pressed
		while (!(keys & KEY_TOUCH || keys & KEY_START || keys & KEY_SELECT || keys & KEY_LEFT || keys & KEY_RIGHT))
		{
			touchRead(&touch);
			scanKeys();
			keys = keysHeld();
		}

		if ((touch.px > 16 && touch.py < 32 && keys & KEY_TOUCH) || keys & KEY_LEFT)
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
		else if ((touch.px < 32 && touch.py < 32 && keys & KEY_TOUCH) || keys & KEY_RIGHT)
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
		else if ((touch.px > 0 && touch.py > 148 && keys & KEY_TOUCH) || keys & KEY_SELECT || keys & KEY_START)
		{
			oamClear(&oamMain, 0, 0);

			// Draw the dotted line again, since it got cleared
			for(int i=7, f=4; i != 19; i++, f+=16)
			{
				oamSet(&oamMain, i, 123, f, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem[0], -1, false, false, false, false, false);
			}

			break;
		}

		swiWaitForVBlank();
	}

	return choice;
}

// Prints out the score in big fancy numbers
void drawscore(int index, int x, int y, int number)
{
	oamClear(&oamMain, index, index + 6);

	letmeusecontinueffs:
	switch(number)
	{
		case 0:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 1:
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 2:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;
		case 3:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 4:
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 5:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 6:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 7:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 8:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 9:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;
		default:
			number = (number - (number % 10)) / 10;
			goto letmeusecontinueffs;
	}
}

int main(void) 
{
	// Seed the rng with the current time
	srand(time(0));

	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	initPaddle(&paddle, (u8*)paddleTiles);
	initBullet(&bullet, (u8*)bulletTiles);

	dmaCopy(paddlePal, SPRITE_PALETTE, 512);

	// Current key being pressed
	int keys = 0;

	bool title_ready = false;
	bool at_title = true;

	int difficulty = 0;

	bool bulletlactivate = false;
	bool bulletractivate = false;

	// Postion of the paddles
	int paddlely = 80;
	int paddlery = 80;

	// Postion of the balls
	int ballx = 123;
	int bally = 92;

	// Position of the bullets
	int bulletlx = 0;
	int bulletrx = 225;	
	int bulletly = 0;
	int bulletry = 0;

	// Misc. sound effect stuff
	int pong = 0;
	int ping = 0;
	int pongi = 0;
	int pingi = 0;
	bool pongs = false;
	bool pings = false;

	int sadlife = 0;
	int ballout = 0;

	bool ldead = false;
	bool rdead = false;
	int lscore = 0;
	int rscore = 0;
	bool animationdone = false;

	int deathcount = 0;
	int stalcount = 0;

	// Was L+R were pressed at the title?
	bool secretdiscovered = false;

	// The time (increments every frame)
	int t = 0;

	float vx = (float)(rand() % 2 * 2 - 1);
	float vy = (float)(rand() % 2 * 2 - 1);

	// Start position of the ball
	int x0 = ballx;
	int y0 = bally;

	int settings_choices = 0;

	void reset()
	{
		bullet.state = 0;
		paddle.state = 0;

		bullet.anim_frame = 0;
		paddle.anim_frame = 0;

		bulletlactivate = false;
		bulletractivate = false;

		ballx = 123;
		bally = 92;

		bulletlx = 0;
		bulletrx = 225;	
		bulletly = 0;
		bulletry = 0;

		paddlely = 80;
		paddlery = 80;

		pongi = 0;
		pong = 0;
		pongs = false;

		pingi = 0;
		ping = 0;
		pings = false;

		ldead = false;
		rdead = false;
		animationdone = false;

		deathcount = 0;
		stalcount = 0;

		// Kill all the sound effects
		soundKill(pong);
		soundKill(ping);
		soundKill(sadlife);
		soundKill(ballout);

		t = 0;
		vx = (float)(rand() % 2 * 2 - 1);
		vy = (float)(rand() % 2 * 2 - 1);
		x0 = ballx;
		y0 = bally;

		settings_choices = 0;
	}

	soundEnable(); 

	// This is the dotted line in the middle of the field... Yes, I am loading each and every line as a seperate sprite
	for(int i=7, f=4; i != 19; i++, f+=16)
	{
		oamSet(&oamMain, i, 123, f, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem[0], -1, false, false, false, false, false);
	}

	// Draw the score of both playes
	drawscore(20, 90, 10, 0);
	drawscore(36, 140, 10, 0);

	while (1) 
	{
		if (deathcount == 0 && stalcount == 0)
		{	
			t++;

			ballx = x0 + vx * t;
			bally = y0 + vy * t;

			if (vx < 0) vx = vx - 0.0004;
			if (vx > 0) vx = vx + 0.0004;

			if (vy < 0) vx = vx - 0.0004;
			if (vy > 0) vy = vy + 0.0004;

			if (bally > 182 || bally < 0)
			{
				vy = -vy;
				x0 = ballx;
				y0 = bally;
				t = 0;

				pong = soundPlayPSG(1, 2400, 64, 64);
				pongs = true;
			}

			if (((ballx < 9 && ballx > 0 && bally > paddlely - 12 && bally < paddlely + 34) || (ballx > 228 && ballx < 237 && bally > paddlery - 12 && bally < paddlery + 34)) && t > 5)
			{
				if (ballx < 9)
				{
					vy = vy + ((float)bally - (float)paddlely) / 32;
					vx = -(vx);
				}
				else
				{
					vy = -vy + ((float)bally - (float)paddlery) / 32;
					vx = -(vx);
				}

				x0 = ballx;
				y0 = bally;
				t = 0;

				ping = soundPlayPSG(1, 4400, 64, 64);
				pings = true;
			}

			if (ballx < -16)
			{
				rscore++;
				stalcount = 1;
				ballout = soundPlayPSG(1, 1000, 64, 64);
			}
			if (ballx > 256)
			{
				lscore++;
				stalcount = 1;
				ballout = soundPlayPSG(1, 1000, 64, 64);
			}
			if (bulletlx < 256 && bulletlactivate)
			{
				bulletlx = bulletlx + 2;
			}
			else
			{
				bulletlx = 0;
				bulletlactivate = false;
				bulletly = paddlely;
			}

			if (bulletrx > -16 && bulletractivate)
			{
				bulletrx = bulletrx - 2;
			}
			else
			{
				bulletrx = 230;
				bulletractivate = false;
				bulletry = paddlery;
			}

			if (bulletrx == 0 && bulletry > paddlely - 16 && bulletry < paddlely + 20)
			{
				ldead = true;
			}

			if (bulletlx == 230 && bulletly > paddlery - 16 && bulletly < paddlery + 20)
			{
				rdead = true;
			}

			scanKeys();
			keys = keysHeld();

			if (keys & KEY_UP)
			{
				if (paddlely > 0)
				{
					paddlely = paddlely - 2;
				}

				if (bulletly > 0 && !bulletlactivate)
				{
					bulletly--;
				}
			}

			if (keys & KEY_RIGHT)
			{
				bulletlactivate = true;
			}

			if (keys & KEY_DOWN)
			{
				if (paddlely < 159)
				{
					paddlely = paddlely + 2;
				}

				if (bulletly < 159 && !bulletlactivate)
				{
					bulletly++;
				}
			}

			switch(difficulty % 10)
			{
				case 0:
					if (keys & KEY_X)
					{
						if (paddlery > 0)
						{
							paddlery = paddlery - 2;
						}
						if (bulletly >= 1 && !bulletractivate)
						{
							bulletry++;
						}
					}

					if (keys & KEY_Y)
					{
						bulletractivate = true;
					}

					if (keys & KEY_B)
					{
						if (paddlery < 159)
						{
							paddlery = paddlery + 2;
						}

						if (bulletry < 159 && !bulletractivate)
						{
							bulletry++;
						}
					}
					break;
				case 1:
					if (vx < 0)
					{
						if (paddlery > 80)
						{
							paddlery--;
						}
						else if (paddlery < 80)
						{
							paddlery++;
						}
					}
					else if (bally > paddlery + 16 && paddlery < 159)
					{
						paddlery = paddlery + (1 + rand() % 2);
					}
					else if (bally < paddlery + 16 && paddlery > 0)
					{
						paddlery = paddlery - (1 + rand() % 2);
					}
					break;
				case 2:
					if (vx < 0)
					{
						if (paddlery > 80)
						{
							paddlery--;
						}
						else if (paddlery < 80)
						{
							paddlery++;
						}
					}
					else if (bally > paddlery + 16 && paddlery < 159)
					{
						paddlery = paddlery + 2;
					}
					else if (bally < paddlery + 16 && paddlery > 0)
					{
						paddlery = paddlery - 2;
					}

					if (rand() % 360 == 0)
					{
						bulletractivate = true;
					}
					break;
				case 3:
					if (vx < 0)
					{
						if (paddlery > 80)
						{
							paddlery--;
						}
						else if (paddlery < 80)
						{
							paddlery++;
						}
					}
					else if (bally > paddlery + 16 && paddlery < 159)
					{
						paddlery = paddlery + 2;
					}
					else if (bally < paddlery + 16 && paddlery > 0)
					{
						paddlery = paddlery - 2;
					}
					bulletractivate = true;
					break;
			}

			// The paddles
			oamSet(&oamMain, 0, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, paddle.sprite_gfx_mem[secretdiscovered], -1, false, ldead, false, false, false);
			oamSet(&oamMain, 1, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, paddle.sprite_gfx_mem[secretdiscovered], -1, false, rdead, true, false, false);

			// The bullets
			oamSet(&oamMain, 2, bulletlx, bulletly, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, rdead || ldead || !bulletlactivate, false, false, false);
			oamSet(&oamMain, 3, bulletrx, bulletry, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, rdead || ldead || !bulletractivate, true, false, false);

			// The ball
			oamSet(&oamMain, 6, ballx, bally, 0, 0, SpriteSize_16x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem[0], -1, false, at_title, false, false, false);

			// Switch statement to check settings
			switch (settings_choices)
			{
				case 1:
					// Magic shperes
					oamRotateScale(&oamMain, 51, degreesToAngle(10), intToFixed(1, 8), intToFixed(1, 8));
					oamRotateScale(&oamMain, 52, degreesToAngle(25), intToFixed(1, 8), intToFixed(1, 8));
					oamSet(&oamMain, 51, 122, 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[9], -1, false, false, false, false, false);
					oamSet(&oamMain, 52, 122, 120, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[9], -1, false, false, false, false, false);
					break;
				case 2:
					// Mystery boxes
					break;
				case 3:
					// Both boxes and shperes
					oamSet(&oamMain, 51, 122, 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[9], -1, false, false, false, false, false);
					oamSet(&oamMain, 52, 122, 120, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[9], -1, false, false, false, false, false);
					break;
			}
		}

		else if (deathcount % 5 == 0)
		{
			// The explosion
			if (ldead)
			{
				oamSet(&oamMain, 4, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, animationdone, false, false, false);
			}

			if (rdead)
			{
				oamSet(&oamMain, 5, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, animationdone, true, false, false);
			}
		}

		if (deathcount == 100 || stalcount == 100)
		{
			// If player 1 is dead, increment player 2's score and vice versa
			if (ldead)
			{
				rscore++;
			}

			if (rdead)
			{
				lscore++;
			}

			// Update the scores
			drawscore(20, 90 - (lscore > 9 ? 24 : 0), 10, lscore);

			if (lscore > 9)
			{
				drawscore(28, 90, 10, lscore % 10);
			}

			drawscore(36, 140, 10, rscore);

			if (rscore > 9)
			{
				drawscore(44, 164, 10, rscore % 10);
			}

			reset();
		}

		if (stalcount != 0)
		{
			stalcount++;

			if (stalcount == 20)
			{
				soundKill(ballout);
			}
		}

		// Animates the explosion every 5th frame until 25 frames have passed
		switch(deathcount)
		{
			case 5:
			case 10:
				bullet.anim_frame++;
				break;
			case 15:
			case 20:
				bullet.anim_frame--;
				break;
			case 25:
				animationdone = true;
				break;
			default:
				break;
		}

		animatePaddle(&paddle);
		animateBullet(&bullet);

		scanKeys();
		keys = keysHeld();

		if (!(keys & KEY_TOUCH) && !at_title)
		{
			title_ready = true;
		}
		else if (title_ready)
		{
			title_ready = false;
			at_title = true;

			lscore = 0;
			rscore = 0;

			drawscore(20, 90, 10, 0);
			drawscore(36, 140, 10, 0);

			reset();
		}

		if (keys & KEY_SELECT || keys & KEY_START)
		{
			settings_choices = settings(settings_choices);

			// Stay in loop until nothing is touched and no key is pressed
			while (keys & KEY_TOUCH || keys & KEY_START || keys & KEY_SELECT || keys & KEY_LEFT || keys & KEY_RIGHT)
			{
				scanKeys();
				keys = keysHeld();
			}
		}

		// If the pong sound has played for 10 frames, kill it and reset the frame counter
		if (pongi == 10)
		{
			soundKill(pong);
			pongi = 0;
			pongs = false;
		}
		else if (pongs)
		{
			pongi++;
		}

		// If the ping sound has played for 10 frames, kill it and reset the frame counter
		if (pingi == 10)
		{
			soundKill(ping);
			pingi = 0;
			pings = false;
		}
		else if (pings)
		{
			pingi++;
		}

		// Write the changes to the top screen
		oamUpdate(&oamMain);

		if (at_title)
		{
			difficulty = title_screen();
			at_title = false;
		}

		// If L+R were pressed at the title, activate the hidden paddle
		if (difficulty > 9)
		{
			secretdiscovered = true;
		}

		if (rdead || ldead)
		{
			bullet.state = 3;

			if (deathcount > 9)
			{
				soundKill(sadlife);
				sadlife = soundPlayPSG(1, -1 * deathcount * 100 + 10000, 64, 64);
			}

			deathcount++;
		}

		// Wait until the next frame
		swiWaitForVBlank();
	}

	return 0;
}