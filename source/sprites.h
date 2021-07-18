extern const unsigned int paddleTiles[3072];
extern const unsigned short paddlePal[256];
extern const unsigned int bulletTiles[3072];
extern const unsigned short bulletPal[256];

typedef struct 
{
	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Paddle;

typedef struct
{
	u16* sprite_gfx_mem[12];
	int gfx_frame;

	int state;
	int anim_frame;

}Bullet;

Paddle paddle = {};
Bullet bullet = {};

void animatePaddle(Paddle *sprite)
{
	int frame = sprite->anim_frame + sprite->state * 3;
	u8* offset = sprite->frame_gfx + frame * 32*32;
	dmaCopy(offset, sprite->sprite_gfx_mem, 32*32);
}

void initPaddle(Paddle *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	sprite->frame_gfx = (u8*)gfx;
}

void animateBullet(Bullet *sprite)
{
	sprite->gfx_frame = sprite->anim_frame + sprite->state;
}

void initBullet(Bullet *sprite, u8* gfx)
{
	for(int i = 0; i < 12; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}
