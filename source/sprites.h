typedef struct 
{
	u16* sprite_gfx_mem[12];

}Tiles;

Tiles tiles = {};

void initTiles(Tiles *sprite, u8* gfx)
{
	for(int i = 0; i < 12; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}