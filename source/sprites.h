typedef struct 
{
	u16* sprite_gfx_mem[30];
}Tiles;

typedef struct 
{
	u16* sprite_gfx_mem[30];
}Tilessub;

Tiles tiles = {};
Tilessub tilessub = {};

void initTiles(Tiles *sprite, u8* gfx)
{
	for(int i = 0; i < 18; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}
void initTilessub(Tilessub *sprite, u8* gfx)
{
	for(int i = 0; i < 21; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}