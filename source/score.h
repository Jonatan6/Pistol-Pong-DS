// Prints out the score in big fancy numbers
void drawscore(int index, int x, int y, int number)
{
	oamClear(&oamMain, index, index + 6);

	switch(number)
	{
		case 0:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;

		case 1:
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;

		case 2:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;
		case 3:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;

		case 4:
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;

		case 5:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;

		case 6:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;

		case 7:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;

		case 8:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 4, x - 22, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;

		case 9:
			oamSet(&oamMain, index + 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 1, x, y + 14, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 2, x, y + 28, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[6], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 3, x - 22, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 5, x - 6, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			oamSet(&oamMain, index + 6, x - 6, y + 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[7], -1, false, false, true, false, false);
			break;
		case >9:
			number = (number - (number % 10)) / 10;
			break;
	}
}
