#include <nds.h>
#include <maxmod9.h>
#include <stdio.h>
#include <time.h>
#include <nds/input.h>
#include <nds/touch.h>

// Grit headers
#include "tiles.h"

// Maxmod headers
#include "soundbank.h"
#include "soundbank_bin.h"

#include "sprites.h"

#define VERTICAL_LINE 6
#define HORIZONTAL_LINE 7
#define DIAGONAL_LINE 8

#define SETTINGSX 40
#define SETTINGSY 40

#define FRAMES_BEFORE_SPEEDUP 2880
#define FRAMES_BEFORE_MYSTERYBOX 500

int title_screen()
{
	int difficulty = 0;

	vramSetBankC(VRAM_C_SUB_BG);

	PrintConsole bottomScreen;
	consoleInit(&bottomScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);

	touchPosition touch;
	touchRead(&touch);

	consoleSelect(&bottomScreen);

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

		// Wait one frame
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
				
				// Wait one frame
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

		// Wait one frames
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
	oamSet(&oamMain, 0, SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 1, SETTINGSX, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 2, SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 3, SETTINGSX - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 4, SETTINGSX - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 5, SETTINGSX - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// P
	oamSet(&oamMain, 6, 24*1+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 7, 24*1+SETTINGSX, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 8, 24*1+SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 9, 24*1+SETTINGSX - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 10, 24*1+SETTINGSX - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// T
	oamSet(&oamMain, 11, 24*2+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 12, 24*2+SETTINGSX - 14, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 13, 24*2+SETTINGSX - 14, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// I
	oamSet(&oamMain, 14, 24*3+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 15, 24*3+SETTINGSX, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 16, 24*3+SETTINGSX - 14, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 17, 24*3+SETTINGSX - 14, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// O
	oamSet(&oamMain, 18, 24*4+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 19, 24*4+SETTINGSX, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 20, 24*4+SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 21, 24*4+SETTINGSX - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 22, 24*4+SETTINGSX - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 23, 24*4+SETTINGSX - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	// N
	oamSet(&oamMain, 24, 24*5+SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 25, 24*5+SETTINGSX - 22, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 26, 24*5+SETTINGSX - 6, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 27, 24*5+SETTINGSX - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 28, 24*5+SETTINGSX+2, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[DIAGONAL_LINE], -1, false, false, true, false, false);
	// S
	oamSet(&oamMain, 29, 24*6+SETTINGSX, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 30, 24*6+SETTINGSX, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 31, 24*6+SETTINGSX, SETTINGSY + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 32, 24*6+SETTINGSX - 22, SETTINGSY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
	oamSet(&oamMain, 33, 24*6+SETTINGSX - 6, SETTINGSY + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);

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
				oamSet(&oamMain, i, 123, f, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[0], -1, false, false, false, false, false);
			}

			break;
		}

		swiWaitForVBlank();
	}

	return choice;
}

// Prints out the score in big fancy numbers
void seven_segment_draw(int index, int x, int y, int number)
{
	oamClear(&oamMain, index, index + 6);

	switch(number)
	{
		case 0:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 1:
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 2:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;
		case 3:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 4:
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 5:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 6:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 7:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 8:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;

		case 9:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[VERTICAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[HORIZONTAL_LINE], -1, false, false, true, false, false);
			break;
		default:
			seven_segment_draw(index, x, y, (number - (number % 10)) / 10);
	}
}

int main(void) 
{
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	initTiles(&tiles, (u8*)tilesTiles);

	dmaCopy(tilesPal, SPRITE_PALETTE, sizeof(tilesPal));

	// Seed the rng with the current time
	srand(time(0));

	// Current key(s) being pressed
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
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoadEffect(SFX_BOX_SUMMON);
	mmLoadEffect(SFX_BOOM);
	mmLoadEffect(SFX_PING);
	mmLoadEffect(SFX_PONG);
	mmLoadEffect(SFX_BALLOUT);

	mm_sound_effect sfx_boxsummon =
	{
		{SFX_BOX_SUMMON},	// id
		(int)(1.0f * (1<<10)),	// rate
		0,			// handle
		255,			// volume
		128,			// panning
	};

	mm_sound_effect sfx_boom =
	{
		{SFX_BOOM},		// id
		(int)(1.0f * (1<<10)),	// rate
		0,			// handle
		255,			// volume
		128,			// panning
	};

	mm_sound_effect sfx_ping =
	{
		{SFX_PING},		// id
		(int)(1.0f * (1<<10)),	// rate
		0,			// handle
		255,			// volume
		128,			// panning
	};

	mm_sound_effect sfx_pong =
	{
		{SFX_PONG},		// id
		(int)(1.0f * (1<<10)),	// rate
		0,			// handle
		255,			// volume
		128,			// panning
	};

	mm_sound_effect sfx_ballout =
	{
		{SFX_BALLOUT},		// id
		(int)(1.0f * (1<<10)),	// rate
		0,			// handle
		255,			// volume
		128,			// panning
	};

	// Frame of the explosion
	int explosion_frame = 0;

	bool ldead = false;
	bool rdead = false;
	int lscore = 0;
	int rscore = 0;

	bool ballout = false;

	// Megacorp. Change name later
	int megacorp = 0;
	int gigacorpx = 0;
	int gigacorpy = 0;

	// Was L+R were pressed at the title?
	bool secretdiscovered = false;

	// The time (increments every frame)
	int t = 0;
	// The true time (increments every frame, but doesn't get reset)
	int tt = 0;

	float vx = (float)(rand() % 2 * 2 - 1);
	float vy = (float)(rand() % 2 * 2 - 1);

	// Start position of the ball
	int x0 = ballx;
	int y0 = bally;

	int settings_choices = 0;

	void reset()
	{
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

		ldead = false;
		rdead = false;

		explosion_frame = 0;

		ballout = false;

		megacorp = 0;
		gigacorpx = 0;
		gigacorpy = 0;

		// Kill all the sound effects
		mmStop();

		t = 0;
		tt = 0;
		vx = (float)(rand() % 2 * 2 - 1);
		vy = (float)(rand() % 2 * 2 - 1);
		x0 = ballx;
		y0 = bally;
	}

	soundEnable(); 

	// This is the dotted line in the middle of the field... Yes, I am loading each and every line as a seperate sprite
	for(int i=7, f=4; i != 19; i++, f+=16)
	{
		oamSet(&oamMain, i, 123, f, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[0], -1, false, false, false, false, false);
	}

	// Draw the score of both playes
	seven_segment_draw(20, 90, 10, 0);
	seven_segment_draw(36, 140, 10, 0);

	while (true) 
	{
		t++;
		tt++;

		ballx = (tt < FRAMES_BEFORE_SPEEDUP) ? (x0 + vx * t) : (x0 + vx * t * tt / FRAMES_BEFORE_SPEEDUP);
		bally = (tt < FRAMES_BEFORE_SPEEDUP) ? (y0 + vy * t) : (y0 + vy * t * tt / FRAMES_BEFORE_SPEEDUP);

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

			mmEffectEx(&sfx_pong);
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

			mmEffectEx(&sfx_ping);
		}

		if (ballx < -16)
		{
			rscore++;
			ballout = true;
		}
		else if (ballx > 256)
		{
			lscore++;
			ballout = true;
		}

		// Check if the bullet belonging to player 1 is out of bounds
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

		// Check if the bullet belonging to player 2 is out of bounds
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

		// Check if player 1 has been shot
		if (bulletrx == 0 && bulletry > paddlely - 16 && bulletry < paddlely + 20)
		{
			ldead = true;
		}

		// Check if player 2 has been shot
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
		oamSet(&oamMain, 0, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[secretdiscovered], -1, false, ldead, false, false, false);
		oamSet(&oamMain, 1, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[secretdiscovered], -1, false, rdead, true, false, false);

		// The bullets
		oamSet(&oamMain, 2, bulletlx, bulletly, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[2], -1, false, rdead || ldead || !bulletlactivate, false, false, false);
		oamSet(&oamMain, 3, bulletrx, bulletry, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[2], -1, false, rdead || ldead || !bulletractivate, true, false, false);

		// The ball
		oamSet(&oamMain, 6, ballx, bally, 0, 0, SpriteSize_16x8, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[0], -1, false, at_title, false, false, false);

		// Switch statement to check settings
		switch (settings_choices)
		{
			// Mystery boxes
			case 1:
				if (megacorp < 1)
				{
					megacorp = rand() % FRAMES_BEFORE_MYSTERYBOX + FRAMES_BEFORE_MYSTERYBOX/2 + tt;
					gigacorpx = rand() % (256 - 128) + 64;
					gigacorpy = rand() % (128 - 64) + 32;
				}
				else if (megacorp <= tt)
				{
					// Rotate the box 0.5° every frame
					oamRotateScale(&oamMain, 0, degreesToAngle(tt/2), intToFixed(1, 8), intToFixed(1, 8));

					oamSet(&oamMain, 52, gigacorpx, gigacorpy, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[10], 0, true, false, false, false, false);
					oamSet(&oamMain, 51, gigacorpx+16, gigacorpy+16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[11], -1, false, false, false, false, false);

					if (megacorp == tt)
					{
						mmEffectEx(&sfx_boxsummon);
					}
					// L gets item
					else if (bulletlx > gigacorpx-16 && bulletlx < gigacorpx+16 && bulletly > gigacorpy - 16 && bulletly < gigacorpy + 16)
					{
						megacorp = 0;
						oamClear(&oamMain, 51, 52);

						bulletlx = 225;
						bulletlactivate = false;
					}
					// R gets item
					else if (bulletrx > gigacorpx-16 && bulletrx < gigacorpx+16 && bulletry > gigacorpy - 16 && bulletry < gigacorpy + 16)
					{
						megacorp = 0;
						oamClear(&oamMain, 51, 52);

						bulletrx = 0;
						bulletractivate = false;
					}
				}

				break;
			// Magic shperes
			case 2:
				// Rotate the spheres 1° every frame
				oamRotateScale(&oamMain, 0, degreesToAngle(tt), intToFixed(1, 8), intToFixed(1, 8));

				oamSet(&oamMain, 51, 120, 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[9], 0, true, false, false, false, false);
				oamSet(&oamMain, 52, 120, 120, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[9], 0, true, false, false, false, false);
				break;
			// Both boxes and shperes
			case 3:
				oamRotateScale(&oamMain, 0, degreesToAngle(tt), intToFixed(1, 8), intToFixed(1, 8));

				oamSet(&oamMain, 51, 120, 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[9], 0, true, false, false, false, false);
				oamSet(&oamMain, 52, 120, 120, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[9], 0, true, false, false, false, false);
				break;
		}

		for (int i = 0; ballout && i < 100; i++, swiWaitForVBlank())
		{
			if (i == 0)
			{
				mmEffectEx(&sfx_ballout);
			}
		}

		for (int i = 0; i < 100 && (ldead || rdead); i++, swiWaitForVBlank())
		{
			switch(i)
			{
				case 5:
					mmEffectEx(&sfx_boom);
					explosion_frame++;
					break;
				case 10:
					explosion_frame++;
					break;
				case 15:
				case 20:
				case 25:
					explosion_frame--;
					break;
			}

			if (ldead)
			{
				oamSet(&oamMain, 4, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[explosion_frame+3], -1, false, explosion_frame < 0, false, false, false);
			}

			if (rdead)
			{
				oamSet(&oamMain, 5, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles.sprite_gfx_mem[explosion_frame+3], -1, false, explosion_frame < 0, true, false, false);
			}

			oamUpdate(&oamMain);
		}

		if (ldead || rdead || ballout)
		{
			// If player 1 is dead, increment player 2's score and vice versa
			if (ldead)
			{
				rscore++;
				seven_segment_draw(20, 90 - (lscore > 9 ? 24 : 0), 10, lscore);
			}

			if (rdead)
			{
				lscore++;
				seven_segment_draw(20, 90 - (lscore > 9 ? 24 : 0), 10, lscore);
			}

			if (lscore > 9)
			{
				seven_segment_draw(28, 90, 10, lscore % 10);
			}

			seven_segment_draw(36, 140, 10, rscore);

			if (rscore > 9)
			{
				seven_segment_draw(44, 164, 10, rscore % 10);
			}

			reset();
		}

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

			seven_segment_draw(20, 90, 10, 0);
			seven_segment_draw(36, 140, 10, 0);

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

		// Wait until the next frame
		swiWaitForVBlank();
	}

	return 0;
}