typedef struct 
{
	u16* sprite_gfx_mem[12];

}Paddle;

typedef struct
{
	u16* sprite_gfx_mem[12];

}Bullet;

typedef struct
{
	u16* sprite_gfx_mem[2];

}Box;

Paddle paddle = {};
Bullet bullet = {};
Box box = {};

void initPaddle(Paddle *sprite, u8* gfx)
{
	for(int i = 0; i < 12; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}

void initBullet(Bullet *sprite, u8* gfx)
{
	for(int i = 0; i < 12; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}

void initBox(Box *sprite, u8* gfx)
{
	for(int i = 0; i < 2; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}