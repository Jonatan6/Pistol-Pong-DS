#include <nds.h>
#include <stdio.h>
#include "sprites.h"
#include "title.h"

int main(void) 
{
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	initPaddle(&paddle, (u8*)paddleTiles);
	initBullet(&bullet, (u8*)bulletTiles);

	dmaCopy(paddlePal, SPRITE_PALETTE, 512);

	bool at_title = true;
	int difficulty = 0;

	bool bulletlactivate = false;
	bool bulletractivate = false;

	bool lturn = rand() % 2;

	int paddlely = 80;
	int paddlery = 80;

	int ballx = 123;
	int bally = 92;
	int ballspeed = -1;

	int bulletlx = 0;
	int bulletrx = 225;	
	int bulletly = 0;
	int bulletry = 0;

	int pingi = 0;
	int pongi = 0;
	int ping = 0;
	int pong = 0;
	bool pings = false;
	bool pongs = false;

	int sadlife = 0;

	bool ldead = false;
	bool rdead = false;
	int deathcount = 0;
	bool animationdone = false;

	void reset()
	{
		bullet.state = 0;
		paddle.state = 0;

		bullet.anim_frame = 0;
		paddle.anim_frame = 0;

		at_title = true;
		difficulty = 0;

		bulletlactivate = false;
		bulletractivate = false;

		lturn = rand() % 2;

		ballx = 123;
		bally = 92;
		ballspeed = -1;

		bulletlx = 0;
		bulletrx = 225;	
		bulletly = 0;
		bulletry = 0;

		paddlely = 80;
		paddlery = 80;

		pingi = 0;
		pongi = 0;
		ping = 0;
		pong = 0;
		pings = false;
		pongs = false;

		ldead = false;
		rdead = false;
		deathcount = 0;
		animationdone = false;

		soundKill(pong);
		soundKill(ping);
		soundKill(sadlife);
	}

	soundEnable(); 

	while(1) 
	{
		if (deathcount == 0)
		{
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
				ballspeed = ballspeed * - 1;
				pong = soundPlayPSG(1, 2400, 64, 64);
				pongs = true;
			}

			if ((ballx == 8 && bally > paddlely - 12 && bally < paddlely + 34) || (ballx == 228 && bally > paddlery - 12 && bally < paddlery + 34))
			{
				lturn = !lturn;
				ballspeed = rand() % 2 + 1;
				ping = soundPlayPSG(1, 4400, 64, 64);
				pings = true;
			}

			if (ballx == -16 || ballx == 256)
			{
				reset();
			}

			if (bulletlx < 256 && bulletlactivate)
			{
				bulletlx = bulletlx + 2;
			}
			else
			{
				bulletlx = 0;
				bulletlactivate = false;
				bulletly = paddlely;
			}

			if (bulletrx > -16 && bulletractivate)
			{
				bulletrx = bulletrx - 2;
			}
			else
			{
				bulletrx = 230;
				bulletractivate = false;
				bulletry = paddlery;
			}

			if (bulletrx == 0 && bulletry > paddlely - 16 && bulletry < paddlely + 20)
			{
				ldead = true;
			}

			if (bulletlx == 230 && bulletly > paddlery - 16 && bulletly < paddlery + 20)
			{
				rdead = true;
			}

			scanKeys();
			int keys = keysHeld();

			if (keys & KEY_UP)
			{
				if (paddlely >= 1)
				{
					paddlely = paddlely - 2;
				}

				if (bulletly >= 1 && !bulletlactivate)
				{
					bulletly--;
				}
			}

			if (keys & KEY_RIGHT)
			{
				bulletlactivate = true;
			}

			if (keys & KEY_DOWN)
			{
				if (paddlely <= 158)
				{
					paddlely = paddlely + 2;
				}

				if (bulletly <= 158 && !bulletlactivate)
				{
					bulletly++;
				}
			}

			if (difficulty % 10 == 0)
			{
				if (keys & KEY_X)
				{
					if (paddlery >= 1)
					{
						paddlery = paddlery - 2;
					}
					if (bulletly >= 1 && !bulletractivate)
					{
						bulletry++;
					}
				}

				if (keys & KEY_Y)
				{
					bulletractivate = true;
				}

				if (keys & KEY_B)
				{
					if (paddlery <= 158)
					{
						paddlery = paddlery + 2;
					}

					if (bulletry <= 158 && !bulletractivate)
					{
						bulletry++;
					}
				}
			}
			else if (difficulty % 10 == 1)
			{
				if (bally > paddlery)
				{
					if (paddlery <= 158)
					{
						paddlery = paddlery + (1 + rand() % 2);
					}
				}
				else
				{
					paddlery = paddlery - (1 + rand() % 2);
				}
			}
			else if (difficulty % 10 == 2)
			{
				if (bally > paddlery)
				{
					if (paddlery <= 158)
					{
						paddlery = paddlery + 2;
					}
				}
				else
				{
					paddlery = paddlery - 2;
				}

				if (rand() % 360 == 0)
				{
					bulletractivate = true;
				}
			}
			else if (difficulty % 10 == 3)
			{

				if (bally > paddlery)
				{
					if (paddlery <= 158)
					{
						paddlery = paddlery + 2;
					}
				}
				else
				{
					paddlery = paddlery - 2;
				}
					bulletractivate = true;
			}
		}

		if (deathcount == 5)
		{
			bullet.anim_frame++;
		}
		else if (deathcount == 10)
		{
			bullet.anim_frame++;
		}
		else if (deathcount == 15)
		{
			bullet.anim_frame--;
		}
		else if (deathcount == 20)
		{
			bullet.anim_frame--;
		}
		else if (deathcount == 25)
		{
			animationdone = true;
		}

		animatePaddle(&paddle);
		animateBullet(&bullet);

		oamSet(&oamMain, 0, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, ldead, false, false, false);
		oamSet(&oamMain, 1, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, rdead, true, false, false);

		oamSet(&oamMain, 2, bulletlx, bulletly, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, !bulletlactivate || ldead || rdead, false, false, false);
		oamSet(&oamMain, 3, bulletrx, bulletry, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, !bulletractivate || ldead || rdead, true, false, false);

		oamSet(&oamMain, 4, ballx, bally, 0, 0, SpriteSize_16x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, at_title, false, false, false);

		oamSet(&oamMain, 5, 123, 4, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 6, 123, 20, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 7, 123, 36, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 8, 123, 52, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 9, 123, 68, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 10, 123, 84, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 11, 123, 100, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 12, 123, 116, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 13, 123, 132, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 14, 123, 148, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 15, 123, 164, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 16, 123, 180, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 17, 123, 196, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);

		oamSet(&oamMain, 18, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, !ldead || animationdone, false, false, false);
		oamSet(&oamMain, 19, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, !rdead || animationdone, true, false, false);

		oamUpdate(&oamMain); // Write the changes to the top screen

		if (pongi == 10)
		{
			soundKill(pong);
			pongi = 0;
			pongs = false;
		}
		else if (pongs)
		{
			pongi++;
		}

		if (pingi == 10)
		{
			soundKill(ping);
			pingi = 0;
			pings = false;
		}
		else if (pings)
		{
			pingi++;
		}

		if (at_title)
		{
			difficulty = title_screen();
			at_title = false;
		}

		if (difficulty > 9)
		{
			paddle.anim_frame = 1;
		}

		if ((rdead && difficulty % 10 == 0) || ldead)
		{
			bullet.state = 3;

			if (deathcount > 9)
			{
				soundKill(sadlife);
				sadlife = soundPlayPSG(1, -1 * deathcount * 100 + 10000, 64, 64);
			}

			if (deathcount == 100) 
			{
				reset();
			}
			else 
			{
				deathcount++;
			}
		}
		else if (rdead)
		{
			bullet.state = 3;

			if (deathcount == 10)
			{
				soundKill(sadlife);
				sadlife = soundPlayPSG(1, 2637, 64, 64);
			}
			if (deathcount == 40)
			{
				soundKill(sadlife);
				sadlife = soundPlayPSG(1, 3136, 64, 64);
			}
			if (deathcount == 70)
			{
				soundKill(sadlife);
				sadlife = soundPlayPSG(1, 4186, 64, 64);
			}
			if (deathcount == 100) 
			{
				reset();
			}
			else 
			{
				deathcount++;
			}
		}


		swiWaitForVBlank(); // Wait until the next frame
	}

	return 0;
}
