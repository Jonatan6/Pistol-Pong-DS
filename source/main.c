#include <nds.h>
#include <stdio.h>
#include "sprites.h"
#include "title.h"

int main(void) 
{
	Man man = {0,0};
	Woman woman = {0,0};

	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	initMan(&man, (u8*)manTiles);
	initWoman(&woman, (u8*)womanTiles);

	dmaCopy(manPal, SPRITE_PALETTE, 512);

	bool at_title = true;
	int difficulty = 0;

	bool bulletlactivate = false;
	bool bulletractivate = false;

	bool lturn = rand() % 2;

	int ballx = 123;
	int bally = 92;
	int ballspeed = -1;

	int bulletlx = 0;
	int bulletrx = 225;	
	int bulletly = 0;
	int bulletry = 0;

	int pingi = 0;
	int pongi = 0;
	int ping = 0;
	int pong = 0;
	bool pings = false;
	bool pongs = false;

	man.y = 80;
	woman.y = 80;

	void reset()
	{
		at_title = true;
		difficulty = 0;

		bulletlactivate = false;
		bulletractivate = false;

		lturn = rand() % 2;

		ballx = 123;
		bally = 92;
		ballspeed = -1;

		bulletlx = 0;
		bulletrx = 225;	
		bulletly = 0;
		bulletry = 0;

		man.y = 80;
		woman.y = 80;
	}

	soundEnable(); 

	while(1) 
	{

		if (lturn)
		{
			ballx++;
			bally = bally + ballspeed;
		}
		else
		{
			ballx--;
			bally = ballspeed * -1 + bally;
		}

		if (bally > 182 || bally < 0)
		{
			ballspeed = ballspeed * - 1;
			pong = soundPlayPSG(1, 2400, 64, 64);
			pongs = true;
		}

		if ((ballx == 8 && bally > man.y - 12 && bally < man.y + 34) || (ballx == 228 && bally > woman.y - 12 && bally < woman.y + 34))
		{
			lturn = !lturn;
			ballspeed = rand() % 2 + 1;
			ping = soundPlayPSG(1, 4400, 64, 64);
			pings = true;
		}

		if (ballx == -16 || ballx == 256)
		{
			reset();
		}

		if (bulletly == woman.y && bulletlx == 225 && bulletlactivate)
		{
			man.y = 10;
			woman.y =10;
		}

		if (bulletlx < 256 && bulletlactivate)
		{
			bulletlx = bulletlx + 2;
		}
		else
		{
			bulletlx = 0;
			bulletlactivate = false;
			bulletly = man.y;
		}

		if (bulletrx > -16 && bulletractivate)
		{
			bulletrx = bulletrx - 2;
		}
		else
		{
			bulletrx = 230;
			bulletractivate = false;
			bulletry = woman.y;
		}

		if (bulletrx == 0 && bulletry > man.y - 16 && bulletry < man.y + 20)
		{
			reset();
		}

		if (bulletlx == 230 && bulletly > woman.y - 16 && bulletly < woman.y + 20)
		{
			reset();
		}

		scanKeys();
		int keys = keysHeld();

		if (keys & KEY_UP)
		{
			if(man.y >= 1) man.y = man.y - 2;
			if(bulletly >= 1 && !bulletlactivate) bulletly--;
		}
		if (keys & KEY_RIGHT)
		{
			bulletlactivate = true;
		}
		if (keys & KEY_DOWN)
		{
			if(man.y <= 158) man.y = man.y + 2;
			if(bulletly <= 158 && !bulletlactivate) bulletly++;
		}

		if (difficulty % 10 == 0)
		{
			if (keys & KEY_X)
			{
				if(woman.y >= 1) woman.y = woman.y - 2;
				if(bulletly >= 1 && !bulletractivate) bulletry++;
			}
			if (keys & KEY_Y)
			{
				bulletractivate = true;
			}
			if (keys & KEY_B)
			{
				if (woman.y <= 158) woman.y = woman.y + 2;
				if (bulletry <= 158 && !bulletractivate) bulletry++;	
			}
		}
		else if (difficulty % 10 == 1)
		{
			if (bally > woman.y)
			{
				if (woman.y <= 158)
				{
					woman.y = woman.y + (1 + rand() % 2);
				}
			}
			else
			{
				woman.y = woman.y - (1 + rand() % 2);
			}
		}
		else if (difficulty % 10 == 2)
		{
			if (bally > woman.y)
			{
				if (woman.y <= 158)
				{
					woman.y = woman.y + 2;
				}
			}
			else
			{
				woman.y = woman.y - 2;
			}
			if (rand() % 360 == 0)
			{
				bulletractivate = true;
			}
		}
		else if (difficulty % 10 == 3)
		{
			if (bally > woman.y)
			{
				if (woman.y <= 158)
				{
					woman.y = woman.y + 2;
				}
			}
			else
			{
				woman.y = woman.y - 2;
			}
				bulletractivate = true;
		}

		animateMan(&man);
		animateWoman(&woman);

		oamSet(&oamMain, 0, 0, man.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);

		oamSet(&oamMain, 1, 225, woman.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, true, false, false);

		oamSet(&oamMain, 2, bulletlx, bulletly, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, woman.sprite_gfx_mem[woman.gfx_frame], -1, false, !bulletlactivate, false, false, false);
		
		oamSet(&oamMain, 3, bulletrx, bulletry, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, woman.sprite_gfx_mem[woman.gfx_frame], -1, false, !bulletractivate, true, false, false);

		oamSet(&oamMain, 4, ballx, bally, 0, 0, SpriteSize_16x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, at_title, false, false, false);

		oamSet(&oamMain, 5, 123, 4, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 6, 123, 20, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 7, 123, 36, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 8, 123, 52, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 9, 123, 68, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 10, 123, 84, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 11, 123, 100, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 12, 123, 116, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 13, 123, 132, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 14, 123, 148, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 15, 123, 164, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 16, 123, 180, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 17, 123, 196, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		
		oamSet(&oamMain, 17, 123, 196, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);

		swiWaitForVBlank();
		oamUpdate(&oamMain); // Write the changes to the top screen

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

		if (at_title)
		{
			difficulty = title_screen();
			at_title = false;
		}

		if (difficulty > 9)
		{
			man.state = woman.state = 3;
		}
	}

	return 0;
}
