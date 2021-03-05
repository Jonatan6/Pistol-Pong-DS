typedef struct 
{
	int x;
	int y;

	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Man;

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
