#include <nds.h>
#include <stdio.h>
#include <man.h>
#include <woman.h>

// The pistol (man) sprite
typedef struct 
{
	int x;
	int y;

	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Man;

// The bullet (woman) sprite
typedef struct
{
	int x;
	int y;

	u16* sprite_gfx_mem[12];
	int gfx_frame;

	int state;
	int anim_frame;

}Woman;

enum SpriteState {W_UP = 0, W_RIGHT = 1, W_DOWN = 2, W_LEFT = 3};

void animateMan(Man *sprite)
{
	int frame = sprite->anim_frame + sprite->state;

	u8* offset = sprite->frame_gfx + frame * 32*32;

	dmaCopy(offset, sprite->sprite_gfx_mem, 32*32);
}

void initMan(Man *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

void animateWoman(Woman *sprite)
{
	sprite->gfx_frame = sprite->anim_frame + sprite->state;
}

void initWoman(Woman *sprite, u8* gfx)
{
	int i;

	for(i = 0; i < 12; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}
//---------------------------------------------------------------------
int main(void) 
//---------------------------------------------------------------------
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
		
		bool bulletlactivate = false;
		bool bulletractivate = false;
	
		int bulletlx = 0;
		int bulletrx = 225;	
		int bulletly = 0;
		int bulletry = 0;
		
		man.y = 50;
		woman.y = 50;

	while(1) 
	{

		if (bulletly == woman.y && bulletlx == 225 && bulletlactivate)
		{
			man.y = 10;
			woman.y =10;
		}

		if (bulletlx < 230 && bulletlactivate)
		  bulletlx = bulletlx + 2;
		else {
		  bulletlx = 0;
		  bulletlactivate = false;
		  bulletly = man.y;
		}

		if (bulletrx > -16 && bulletractivate)
		  bulletrx = bulletrx - 2;
		else {
		  bulletrx = 230;
		  bulletractivate = false;
		  bulletry = woman.y;
		}

		scanKeys();

		int keys = keysHeld();

			if(keys & KEY_UP)
			{
				if(man.y >= 1) man.y--;
				if(bulletly >= 1 && !bulletlactivate) bulletly--;
			}
			if(keys & KEY_RIGHT)
			{
				bulletlactivate = true;
			}
			if(keys & KEY_DOWN)
			{
				if(man.y <= 158) man.y++;
				if(bulletly <= 158 && !bulletlactivate) bulletly++;
			}

			if(keys & KEY_X)
			{
				if(woman.y >= 1) woman.y--;
				if(bulletly >= 1 && !bulletractivate) bulletry++;

			}
			if(keys & KEY_Y)
			{
				bulletractivate = true;
			}
			if(keys & KEY_B)
			{
				if(woman.y <= 158) woman.y++;
				if(bulletry <= 158 && !bulletractivate) bulletry++;	
		}

		animateMan(&man);
		animateWoman(&woman);

		oamSet(&oamMain, 0, 1, man.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
			man.sprite_gfx_mem, -1, false, false, false, false, false);
		
		oamSet(&oamMain, 1, 225, woman.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
			man.sprite_gfx_mem, -1, false, false, true, false, false);

		oamSet(&oamMain, 2, bulletlx, bulletly, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
			woman.sprite_gfx_mem[woman.gfx_frame], -1, false, !bulletlactivate, false, false, false);
		
		oamSet(&oamMain, 3, bulletrx, bulletry, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
			woman.sprite_gfx_mem[woman.gfx_frame], -1, false, !bulletractivate, true, false, false);

		oamSet(&oamMain, 4, 127, 75, 0, 0, SpriteSize_16x8, SpriteColorFormat_256Color, 
			man.sprite_gfx_mem, -1, false, false, false, false, false);

		oamSet(&oamMain, 5, 127, 0, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 6, 127, 16, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 7, 127, 32, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 8, 127, 48, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 9, 127, 64, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 10, 127, 80, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 11, 127, 96, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 12, 127, 112, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 13, 127, 128, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 14, 127, 144, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 15, 127, 160, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 16, 127, 176, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 17, 127, 192, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, man.sprite_gfx_mem, -1, false, false, false, false, false);

		swiWaitForVBlank();

		oamUpdate(&oamMain); // Write the changes to the top screen
		oamUpdate(&oamSub); // Write the changes to the bottom screen
	}

	return 0;
}
