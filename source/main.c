#include <nds.h>
#include <stdio.h>
#include "sprites.h"
#include "title.h"
#include "score.h"

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

	bool title_ready = false;
	bool at_title = true;
	int difficulty = 0;

	bool bulletlactivate = false;
	bool bulletractivate = false;

	int paddlely = 80;
	int paddlery = 80;

	int ballx = 123;
	int bally = 92;

	int bulletlx = 0;
	int bulletrx = 225;	
	int bulletly = 0;
	int bulletry = 0;

	int pongi = 0;
	int pong = 0;
	bool pongs = false;
	int pingi = 0;
	int ping = 0;
	bool pings = false;

	int sadlife = 0;
	int ballout = 0;

	bool ldead = false;
	bool rdead = false;
	int lscore = 0;
	int rscore = 0;
	bool animationdone = false;

	int deathcount = 0;
	int stalcount = 0;

	int t = 0; // time
	float vx = (float)(rand() % 2 * 2 - 1);
	float vy = (float)(rand() % 2 * 2 - 1);

	// ball start position
	int x0 = ballx;
	int y0 = bally;

	void reset()
	{
		bullet.state = 0;
		paddle.state = 0;

		bullet.anim_frame = 0;
		paddle.anim_frame = 0;

		bulletlactivate = false;
		bulletractivate = false;

		ballx = 123;
		bally = 92;

		bulletlx = 0;
		bulletrx = 225;	
		bulletly = 0;
		bulletry = 0;

		paddlely = 80;
		paddlery = 80;

		pongi = 0;
		pong = 0;
		pongs = false;

		pingi = 0;
		ping = 0;
		pings = false;

		ldead = false;
		rdead = false;
		animationdone = false;

		deathcount = 0;
		stalcount = 0;

		soundKill(pong);
		soundKill(ping);
		soundKill(sadlife);
		soundKill(ballout);

		t = 0;
		vx = (float)(rand() % 2 * 2 - 1);;
		vy = (float)(rand() % 2 * 2 - 1);;
		x0 = ballx;
		y0 = bally;
	}

	soundEnable(); 

	// This is the dotted line in the middle of the field... Yes, I am loading each and every line as a seperate sprite
	oamSet(&oamMain, 7, 123, 4, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 8, 123, 20, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 9, 123, 36, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 10, 123, 52, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 11, 123, 68, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 12, 123, 84, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 13, 123, 100, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 14, 123, 116, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 15, 123, 132, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 16, 123, 148, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 17, 123, 164, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 18, 123, 180, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	oamSet(&oamMain, 19, 123, 196, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);

	// Draw the scores of both playes
	drawscore(20, 90, 10, 0);
	drawscore(36, 140, 10, 0);

	while(1) 
	{
		if (deathcount == 0 && stalcount == 0)
		{	
			t++;
			ballx = x0 + vx * t;
			bally = y0 + vy * t;

			if (bally > 182 || bally < 0)
			{
				vy = -vy;
				x0 = ballx;
				y0 = bally;
				t = 0;

				pong = soundPlayPSG(1, 2400, 64, 64);
				pongs = true;
			}

			if (((ballx < 9 && ballx > 0 && bally > paddlely - 12 && bally < paddlely + 34) || (ballx > 228 && ballx < 237 && bally > paddlery - 12 && bally < paddlery + 34)) && t > 5)
			{
				if (ballx < 9)
				{
					vy = vy + ((float)bally - (float)paddlely) / 32;
					vx = -(vx);
				}
				else
				{
					vy = -vy + ((float)bally - (float)paddlery) / 32;
					vx = -(vx);
				}

				x0 = ballx;
				y0 = bally;
				t = 0;

				ping = soundPlayPSG(1, 4400, 64, 64);
				pings = true;
			}

			if (ballx < -16)
			{
				rscore++;
				stalcount = 1;
				ballout = soundPlayPSG(1, 1000, 64, 64);
			}
			if (ballx > 256)
			{
				lscore++;
				stalcount = 1;
				ballout = soundPlayPSG(1, 1000, 64, 64);
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
				if (paddlely > 0)
				{
					paddlely = paddlely - 2;
				}

				if (bulletly > 0 && !bulletlactivate)
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
				if (paddlely < 159)
				{
					paddlely = paddlely + 2;
				}

				if (bulletly < 159 && !bulletlactivate)
				{
					bulletly++;
				}
			}

			if (difficulty % 10 == 0)
			{
				if (keys & KEY_X)
				{
					if (paddlery > 0)
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
					if (paddlery < 159)
					{
						paddlery = paddlery + 2;
					}

					if (bulletry < 159 && !bulletractivate)
					{
						bulletry++;
					}
				}
			}
			else if (difficulty % 10 == 1)
			{
				if (bally > paddlery + 16 && paddlery < 159)
				{
					paddlery = paddlery + (1 + rand() % 2);
				}
				else if (bally < paddlery + 16 && paddlery > 0)
				{
					paddlery = paddlery - (1 + rand() % 2);
				}
			}
			else if (difficulty % 10 == 2)
			{

				if (bally > paddlery + 16 && paddlery < 159)
				{
					paddlery = paddlery + 2;
				}
				else if (bally < paddlery + 16 && paddlery > 0)
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

				if (bally > paddlery + 16 && paddlery < 159)
				{
						paddlery = paddlery + 2;
				}
				else if (bally < paddlery + 16 && paddlery > 0)
				{
					paddlery = paddlery - 2;
				}
					bulletractivate = true;
			}

			// The paddles
			oamSet(&oamMain, 0, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, ldead, false, false, false);
			oamSet(&oamMain, 1, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, rdead, true, false, false);

			// The bullets
			oamSet(&oamMain, 2, bulletlx, bulletly, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, rdead || ldead, false, false, false);
			oamSet(&oamMain, 3, bulletrx, bulletry, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, rdead || ldead, true, false, false);

			// The ball
			oamSet(&oamMain, 6, ballx, bally, 0, 0, SpriteSize_16x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, at_title, false, false, false);
		}

		if (deathcount % 5 == 0 && deathcount != 0)
		{
			// The explosion
			if (ldead)
			{
				oamSet(&oamMain, 4, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, animationdone, false, false, false);
			}

			if (rdead)
			{
				oamSet(&oamMain, 5, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, animationdone, true, false, false);
			}
		}

		if (deathcount == 100 || stalcount == 100)
		{
			if (ldead)
			{
				rscore++;
			}

			if (rdead)
			{
				lscore++;
			}

			// The scores
			drawscore(20, 90 - (lscore > 9 ? 24 : 0), 10, lscore);

			if (lscore > 9)
			{
				drawscore(28, 90, 10, lscore % 10);
			}

			drawscore(36, 140, 10, rscore);

			if (rscore > 9)
			{
				drawscore(44, 164, 10, rscore % 10);
			}

			reset();
		}

		if (stalcount != 0)
		{
			stalcount++;

			if (stalcount == 20)
			{
				soundKill(ballout);
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

		scanKeys();
		int keys = keysHeld();

		if (!(keys & KEY_TOUCH) && !at_title)
		{
			title_ready = true;
		}
		else if (title_ready)
		{
			title_ready = false;
			at_title = true;

			lscore = 0;
			rscore = 0;

			drawscore(20, 90, 10, 0);
			drawscore(36, 140, 10, 0);

			reset();
		}

		// Write the changes to the top screen
		oamUpdate(&oamMain);

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

		if (rdead || ldead)
		{
			bullet.state = 3;

			if (deathcount > 9)
			{
				soundKill(sadlife);
				sadlife = soundPlayPSG(1, -1 * deathcount * 100 + 10000, 64, 64);
			}

			deathcount++;
		}

		swiWaitForVBlank(); // Wait until the next frame
	}

	return 0;
}
