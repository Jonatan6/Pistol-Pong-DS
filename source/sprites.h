#define MAINTILES 18
#define SUBTILES 33

typedef struct 
{
	u16* sprite_gfx_mem[MAINTILES];
}Tiles;

typedef struct 
{
	u16* sprite_gfx_mem[SUBTILES];
}Tilessub;

Tiles tiles = {};
Tilessub tilessub = {};

void initTiles(Tiles *sprite, u8* gfx)
{
	for(int i = 0; i < MAINTILES; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}
void initTilessub(Tilessub *sprite, u8* gfx)
{
	for(int i = 0; i < SUBTILES; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}