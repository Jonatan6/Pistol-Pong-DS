#define MAINTILES 18
#define SUBTILES 33

u16* tiles[MAINTILES];
u16* tilessub[SUBTILES];

void initTiles(u8* gfx)
{
	for(int i = 0; i < MAINTILES; i++)
	{
		tiles[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, tiles[i], 32*32);
		gfx += 32*32;
	}
}
void initTilessub(u8* gfx)
{
	for(int i = 0; i < SUBTILES; i++)
	{
		tilessub[i] = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, tilessub[i], 32*32);
		gfx += 32*32;
	}
}