#include <nds.h>
#include <stdio.h>
#include <time.h>
#include <nds/input.h>
#include <nds/touch.h>

#include "sprites.h"
#include "title.h"
#include "score.h"
#include "settings.h"

int main(void) 
{
	// Seed the rng with the current time
	srand(time(0));

	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	initPaddle(&paddle, (u8*)paddleTiles);
	initBullet(&bullet, (u8*)bulletTiles);

	dmaCopy(paddlePal, SPRITE_PALETTE, 512);

	// Current key being pressed
	int keys;

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

	// Misc. sound effect stuff
	int pong = 0;
	int ping = 0;
	int pongi = 0;
	int pingi = 0;
	bool pongs = false;
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

	// The time
	int t = 0;

	float vx = (float)(rand() % 2 * 2 - 1);
	float vy = (float)(rand() % 2 * 2 - 1);

	// Start position of the ball
	int x0 = ballx;
	int y0 = bally;

	int settings_choices = 0;

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

		// Kill all the sound effects
		soundKill(pong);
		soundKill(ping);
		soundKill(sadlife);
		soundKill(ballout);

		t = 0;
		vx = (float)(rand() % 2 * 2 - 1);
		vy = (float)(rand() % 2 * 2 - 1);
		x0 = ballx;
		y0 = bally;

		settings_choices = 0;
		}

	soundEnable(); 

	// This is the dotted line in the middle of the field... Yes, I am loading each and every line as a seperate sprite
	for(int i=7, f=4; i != 19; i++, f+=16)
	{
		oamSet(&oamMain, i, 123, f, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, false, false, false, false);
	}

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

			if (vx < 0) vx = vx - 0.0004;
			if (vx > 0) vx = vx + 0.0004;

			if (vy < 0) vx = vx - 0.0004;
			if (vy > 0) vy = vy + 0.0004;

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
			keys = keysHeld();

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

			switch(difficulty % 10)
			{
				case 0:
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
					break;
				case 1:
					if (vx < 0)
					{
						if (paddlery > 80)
						{
							paddlery--;
						}
						else if (paddlery < 80)
						{
							paddlery++;
						}
					}
					else if (bally > paddlery + 16 && paddlery < 159)
					{
						paddlery = paddlery + (1 + rand() % 2);
					}
					else if (bally < paddlery + 16 && paddlery > 0)
					{
						paddlery = paddlery - (1 + rand() % 2);
					}
					break;
				case 2:
					if (vx < 0)
					{
						if (paddlery > 80)
						{
							paddlery--;
						}
						else if (paddlery < 80)
						{
							paddlery++;
						}
					}
					else if (bally > paddlery + 16 && paddlery < 159)
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
					break;
				case 3:
					if (vx < 0)
					{
						if (paddlery > 80)
						{
							paddlery--;
						}
						else if (paddlery < 80)
						{
							paddlery++;
						}
					}
					else if (bally > paddlery + 16 && paddlery < 159)
					{
						paddlery = paddlery + 2;
					}
					else if (bally < paddlery + 16 && paddlery > 0)
					{
						paddlery = paddlery - 2;
					}
					bulletractivate = true;
					break;
			}

			// The paddles
			oamSet(&oamMain, 0, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, ldead, false, false, false);
			oamSet(&oamMain, 1, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, rdead, true, false, false);

			// The bullets
			oamSet(&oamMain, 2, bulletlx, bulletly, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, rdead || ldead || !bulletlactivate, false, false, false);
			oamSet(&oamMain, 3, bulletrx, bulletry, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[bullet.gfx_frame], -1, false, rdead || ldead || !bulletractivate, true, false, false);

			// The ball
			oamSet(&oamMain, 6, ballx, bally, 0, 0, SpriteSize_16x8, SpriteColorFormat_256Color, paddle.sprite_gfx_mem, -1, false, at_title, false, false, false);

			// Switch statement to check settings
			switch (settings_choices)
			{
				case 1:
					// Magic shperes
					oamRotateScale(&oamMain, 51, degreesToAngle(10), intToFixed(1, 8), intToFixed(1, 8));
					oamRotateScale(&oamMain, 52, degreesToAngle(25), intToFixed(1, 8), intToFixed(1, 8));
					oamSet(&oamMain, 51, 122, 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[9], -1, false, false, false, false, false);
					oamSet(&oamMain, 52, 122, 120, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[9], -1, false, false, false, false, false);
					break;
				case 2:
					// Mystery boxes
					break;
				case 3:
					// Both boxes and shperes
					oamSet(&oamMain, 51, 122, 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[9], -1, false, false, false, false, false);
					oamSet(&oamMain, 52, 122, 120, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, bullet.sprite_gfx_mem[9], -1, false, false, false, false, false);
					break;
			}
		}

		else if (deathcount % 5 == 0)
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

		// Animates the explosion every 5th frame until 25 frames have passed
		switch(deathcount)
		{
			case 5:
			case 10:
				bullet.anim_frame++;
				break;
			case 15:
			case 20:
				bullet.anim_frame--;
				break;
			case 25:
				animationdone = true;
				break;
			default:
				break;
		}

		animatePaddle(&paddle);
		animateBullet(&bullet);

		scanKeys();
		keys = keysHeld();

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

		if (keys & KEY_SELECT || keys & KEY_START)
		{
			settings_choices = settings(settings_choices);

			// Stay in loop until nothing is touched and no key is pressed
			while(keys & KEY_TOUCH || keys & KEY_START || keys & KEY_SELECT || keys & KEY_LEFT || keys & KEY_RIGHT)
			{
				scanKeys();
				keys = keysHeld();
			}
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

		// If L+R were pressed at the title, activate the hidden paddle
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

		// Wait until the next frame
		swiWaitForVBlank();
	}

	return 0;
}