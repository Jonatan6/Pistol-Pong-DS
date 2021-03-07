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
	dmaCopy(womanPal, SPRITE_PALETTE_SUB, 512);

	bool at_title = true;

	bool bulletlactivate = false;
	bool bulletractivate = false;

	bool lturn = true;

	int ballx = 123;
	int bally = 92;
	int ballspeed = -1;

	int bulletlx = 0;
	int bulletrx = 225;	
	int bulletly = 0;
	int bulletry = 0;
		
	man.y = 50;
	woman.y = 50;

	while(1) 
	{

		if (at_title)
		{
			title_screen();
			at_title = false;
		}

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
			ballspeed = ballspeed * -1;
		}


		if ((ballx == 8 && bally > man.y - 12 && bally < man.y + 34) || (ballx == 228 && bally > woman.y - 12 && bally < woman.y + 34))
		{
			lturn = !lturn;
			ballspeed = rand() % 2 + 1;
		}

		if (bulletly == woman.y && bulletlx == 225 && bulletlactivate)
		{
			man.y = 10;
			woman.y =10;
		}

		if (bulletlx < 230 && bulletlactivate)
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

		scanKeys();
		int keys = keysHeld();

		if(keys & KEY_UP)
		{
			if(man.y >= 1) man.y = man.y - 2;
			if(bulletly >= 1 && !bulletlactivate) bulletly--;
		}
		if(keys & KEY_RIGHT)
		{
			bulletlactivate = true;
		}
		if(keys & KEY_DOWN)
		{
			if(man.y <= 158) man.y = man.y + 2;
			if(bulletly <= 158 && !bulletlactivate) bulletly++;
		}

		if(keys & KEY_X)
		{
			if(woman.y >= 1) woman.y = woman.y - 2;
			if(bulletly >= 1 && !bulletractivate) bulletry++;
		}
		if(keys & KEY_Y)
		{
			bulletractivate = true;
		}
		if(keys & KEY_B)
		{
			if(woman.y <= 158) woman.y = woman.y + 2;
			if(bulletry <= 158 && !bulletractivate) bulletry++;	
		}

		animateMan(&man);
		animateWoman(&woman);

		oamSet(&oamMain, 0, 0, man.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		
		oamSet(&oamMain, 1, 225, woman.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, true, false, false);

		oamSet(&oamMain, 2, bulletlx, bulletly, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, woman.sprite_gfx_mem[woman.gfx_frame], -1, false, !bulletlactivate, false, false, false);
		
		oamSet(&oamMain, 3, bulletrx, bulletry, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, woman.sprite_gfx_mem[woman.gfx_frame], -1, false, !bulletractivate, true, false, false);

		oamSet(&oamMain, 4, ballx, bally, 0, 0, SpriteSize_16x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);

		oamSet(&oamMain, 5, 127, 4, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 6, 127, 20, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 7, 127, 36, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 8, 127, 52, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 9, 127, 68, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 10, 127, 84, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 11, 127, 100, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 12, 127, 116, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 13, 127, 132, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 14, 127, 148, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 15, 127, 164, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 16, 127, 180, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 17, 127, 196, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);

		swiWaitForVBlank();

		oamUpdate(&oamMain); // Write the changes to the top screen
		//oamUpdate(&oamSub); // Write the changes to the bottom screen
	}

	return 0;
}
