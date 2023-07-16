// Standard headers
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// Devkitpro headers
#include <nds.h>
#include <maxmod9.h>

// Grit headers
#include "tiles.h"
#include "tilessub.h"
#include "bg.h"
#include "bgsub.h"

// Maxmod headers
#include "soundbank.h"
#include "soundbank_bin.h"

#include "sprites.h"

#define VERTICAL_LINE 9
#define HORIZONTAL_LINE 10
#define DIAGONAL_LINE 11

#define FRAMES_BEFORE_SPEEDUP 2880
#define FRAMES_BEFORE_MYSTERYBOX 500

#define BALLXSTART 123
#define BALLYSTART 92

#define PADDLEYSTART 80

#define PLAYER1X 0
#define PLAYER2X 225

// Current key(s) being pressed
int keys = 0;

// The current difficulty (0 is multiplayer, 1 is easy, 2 is normal, and 3 is hard)
int difficulty = 0;

// The settings choices
int settings_choices = 0;

// Becomes true when the left bullet gets fired
bool bulletlactivate = false;
// Becomes true when the right bullet gets fired
bool bulletractivate = false;

// X postions of the paddles
int paddlely = PADDLEYSTART;
int paddlery = PADDLEYSTART;

// Postions of the ball
int ballx = BALLXSTART;
int bally = BALLYSTART;

// Positions of the bullets
int bulletlx = PLAYER1X;
int bulletrx = PLAYER2X;	
int bulletly = 0;
int bulletry = 0;

// Frame of the explosion
int explosion_frame = 0;

// True if player 1 has been shot
bool ldead = false;
// True if player 2 has been shot
bool rdead = false;

// True if ball went out of bounds
bool ballout = false;

// Scores
int lscore = 0;
int rscore = 0;

// Change this stupid name later
int megacorp = 0;
int gigacorpx = 0;
int gigacorpy = 0;

// Was L+R were pressed at the title?
bool secretdiscovered = false;

// The time (increments every frame)
int t = 0;
// The true time (increments every frame, but doesn't get reset)
int tt = 0;

// Velocity of the ball
float vx = 0;
float vy = 0;

// Start position of the ball
int x0 = BALLXSTART;
int y0 = BALLYSTART;

// The mystery boxes effects (0 is deactivated, 1 is activated by player 1, 2 is activated bt player 2)
int mystery_box_effect = 0;
// True if player 2 has shot a mystery box
int r_has_effect = 0;

// The button(s) that's gray
bool gray_button[6] = {false, false, false, false, true, true};

// True if the the game is multiplayer
bool is_multiplayer = false;

// Joe index (self-explanatory)
int joe1 = 0;
int joe2 = -1;
int joe3 = 0;

// 700 frames before speedup
int speed = 0;

void reset()
{
	bulletlactivate = false;
	bulletractivate = false;

	ballx = BALLXSTART;
	bally = BALLYSTART;

	bulletlx = PLAYER1X;
	bulletrx = PLAYER2X;	
	bulletly = 0;
	bulletry = 0;

	paddlely = PADDLEYSTART;
	paddlery = PADDLEYSTART;

	ldead = false;
	rdead = false;

	explosion_frame = 0;

	ballout = false;

	megacorp = 0;
	gigacorpx = 0;
	gigacorpy = 0;

	// Kill all the sound effects
	mmStop();

	t = 0;
	vx = (float)(rand() % 2 * 2 - 1);
	vy = (float)(rand() % 2 * 2 - 1);
	x0 = BALLXSTART;
	y0 = BALLYSTART;
}

void init_everything()
{
	// Set video modes
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);

	// Set vram banks
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankB(VRAM_B_MAIN_SPRITE);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	// Initialize the sprite engine
	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	// Initialize the sprite tiles
	initTiles((u8*)tilesTiles);
	initTilessub((u8*)tilessubTiles);

	// Copy the palette to both the main screen and the sub screen
	dmaCopy(tilesPal, SPRITE_PALETTE, sizeof(tilesPal));
	dmaCopy(tilessubPal, SPRITE_PALETTE_SUB, sizeof(tilessubPal));

	// Initialize maxmod
	mmInitDefaultMem((mm_addr)soundbank_bin);

	// Seed the rng with the current time
	srand(time(0));

	// Set value of vx and vy to either or 1 or -1
	vx = (float)(rand() % 2 * 2 - 1);
	vy = (float)(rand() % 2 * 2 - 1);
}

void draw_options(int active, bool slide)
{
	if (slide)
	{
		for (int i = 0; i <= 234; i+=32)
		{
			// Clear all sprites used
			oamClear(&oamSub, 0, 0);

			// Draw wide planks
			for (int j = 0; j < 32; j++)
			{
				oamSet(&oamSub, 20 + j, -256 + 32 * (j % 8) + i, 4 + j / 8 * 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[!((j + 1) % 8) + ((active == 1 + j / 8) ? 2 : 0)], -1, false, false, false, false, false);
			}

			// Draw text
			for (int j = 0; j < 3; j++)
			{
				// Button titles (3)
				if (!j) oamSet(&oamSub, 8 + j, -256 + 48 + i, j * 40 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[is_multiplayer ? 18 : 17+j*2], -1, false, false, false, false, false);
				if (j)
				{
					oamSet(&oamSub, 9 + j, -256 + 64 + i, j * 40 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[18+j*2-1], -1, false, false, false, false, false);
					oamSet(&oamSub, 12 + j, -256 + 64 + i, j * 40 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[18+j*2], -1, false, false, false, false, false);
				}
			}
			if (!is_multiplayer)
			{
				for (int j = 0; j < 2; j++)
				{
					// First button (2)
					oamSet(&oamSub, 13 + j, -256 + 32 + i + j*32, 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[13+j+joe1*2+((joe1<0) ? 1 : 0)], -1, false, false, false, false, false);

					// After printing 1 time, if joe1 is less than 0 break out of the for loop
					if (joe1 < 0)
					break;
				}
			}
			else
			{
				for (int j = 0; j < 2; j++)
				{
					oamSet(&oamSub, 13 + j, -256 + 32 + i + j*32 - 14, 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[30+j], -1, false, false, false, false, false);
				}
			}
			for (int j = 0; j < 2; j++)
			{
				// Second button (2)
				oamSet(&oamSub, 16 + j, -256 + 32 + i + j*32, 40 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[25+j+joe2], -1, false, false, false, false, false);
			}
			for (int j = 0; j < 1; j++) /*Very usefull for loop*/
			{
				// Third button (1)
				oamSet(&oamSub, 18 + j, -256 + 32 + i + j*32, 80 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[23+joe3], -1, false, false, false, false, false);				
			}

			// Draw small arrows
			for (int j = 0; j < 6; j++)
			{
				oamSet(&oamSub, j, -256 + 64 + (j < 3 ? 120 : 0) + 32 + i, 4 + j % 3 * 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[4 + !(gray_button - j)], -1, false, false, j < 3, false, false);
			}

			oamUpdate(&oamSub);
			swiWaitForVBlank();
		}
	}
	else
	{
		// Clear all sprites used
		oamClear(&oamSub, 0, 0);

		// Draw wide planks
		for (int j = 0; j < 32; j++)
		{
			oamSet(&oamSub, 21 + j, 32 * (j % 8) - 32, 4 + j / 8 * 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[!((j+1)%8) + ((active == 1+j/8) ? 2 : 0)], -1, false, false, false, false, false);
		}

		// Draw text
		for (int j = 0; j < 3; j++)
		{
			// Button titles (5)
			if (!j) oamSet(&oamSub, 8 + j, 16, j * 40 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[is_multiplayer ? 18 : 17+j*2], -1, false, false, false, false, false);
			if (j)
			{
				oamSet(&oamSub, 9 + j, 10+!(j%2)*3, j * 40 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[18+j*2-1], -1, false, false, false, false, false);
				oamSet(&oamSub, 12 + j, 42+!(j%2)*3, j * 40 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[18+j*2], -1, false, false, false, false, false);
			}
		}
		if (!is_multiplayer)
		{
			for (int j = 0; j < 2; j++)
			{
				// First button (2)
				oamSet(&oamSub, 15 + j, 120 + j*32, 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[13+j+joe1*2+((joe1<0) ? 1 : 0)], -1, false, false, false, false, false);

				// After printing 1 time, if joe1 is less than 0 break out of the for loop
				if (joe1 < 0)
				break;
			}
		}
		else
		{
			for (int j = 0; j < 3; j++)
			{
				oamSet(&oamSub, 15 + j, 120 + j*32 - 14, 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[30+j], -1, false, false, false, false, false);
			}
		}
		for (int j = 0; j < 2; j++)
		{
			// Second button (2)
			if (joe2 > 0)
			{
				oamSet(&oamSub, 18 + j, 120 + j*32, 40 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[25+j+joe2], -1, false, false, false, false, false);
			}
			else
			{
				oamSet(&oamSub, 18 + j, 120 + j*32, 40 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[25+j+joe2+1], -1, false, false, false, false, false);
				break;
			}
		}
		for (int j = 0; j < 1; j++) /*Very usefull for loop*/
		{
			// Third button (1)
			oamSet(&oamSub, 20 + j, 120 + j*32, 80 + 12, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[23+joe3], -1, false, false, false, false, false);				
		}

		// Draw small arrows
		for (int j = 0; j < 6; j++)
		{
			oamSet(&oamSub, j, 64 + (j < 3 ? 120 : 0), 4 + j%3*40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[4 + gray_button[j]], -1, false, false, j < 3, false, false);
		}

		oamUpdate(&oamSub);
		swiWaitForVBlank();
	}

	oamUpdate(&oamSub);
}

// This function is very messy, I will fix it later
void draw_buttons(int buttons, int active, int slide)
{

	if (buttons == 4)
	{
		draw_options(active, slide);
	}

	else if (slide == 1)
	{
		for(int i = 0; i <= 234; i+=32)
		{
			// Clear all sprites used
			oamClear(&oamSub, 0, 0);

			for (int j = 0; j < 8; j++)
			{
				oamSet(&oamSub, 6+j, -256+32*j+i, 8, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[j/7+2], -1, false, false, false, false, false);
			}

			for (int j = 0; j < 8; j++)
			{
				oamSet(&oamSub, 14+j, -256+32*j+i, 56, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[j/7], -1, false, false, false, false, false);
			}

			for (int j = 0; j < 3; j++)
			{
				oamSet(&oamSub, j, -256+32*(j+3)+i, 18, 0, 0, SpriteSize_32x16, SpriteColorFormat_256Color, tilessub[j+9], -1, false, false, false, false, false);
			}

			for (int j = 0; j < 3; j++)
			{
				oamSet(&oamSub, j+3, -256+32*(j+3)+i, 66, 0, 0, SpriteSize_32x16, SpriteColorFormat_256Color, tilessub[j+6], -1, false, false, false, false, false);
			}

			oamUpdate(&oamSub);
			swiWaitForVBlank();
		}
	}
	else if (slide == 0)
	{
		for (int j = 0; j < 8; j++)
		{
			oamSet(&oamSub, 6+j, 32*j-32, 8, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[j/7+!(active-1)*2], -1, false, false, false, false, false);
		}

		for (int j = 0; j < 8; j++)
		{
			oamSet(&oamSub, 14+j, 32*j-32, 56, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[j/7+!((active-1)*2-2)*2], -1, false, false, false, false, false);
		}

		oamUpdate(&oamSub);
	}
	else if (slide == 2)
	{
		for(int j = 0; j < 8; j++)
		{
			int i;

			if (j == 0)
			{
				i = 234;
			}
			if (j < 4)
			{
				i+=4;
			}
			else
			{
				i-=4;
			}

			if (active == 1)
			{
				
				for (int j = 0; j < 8; j++)
				{
					oamSet(&oamSub, 6+j, -256+32*j+i, 8, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[j/7+2], -1, false, false, false, false, false);
				}

				for (int j = 0; j < 3; j++)
				{
					oamSet(&oamSub, j, -256+32*(j+3)+i, 18, 0, 0, SpriteSize_32x16, SpriteColorFormat_256Color, tilessub[j+9], -1, false, false, false, false, false);
				}
			}
			else if (active == 2)
			{
				for (int j = 0; j < 8; j++)
				{
					oamSet(&oamSub, 14+j, -256+32*j+i, 56, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tilessub[j/7+2], -1, false, false, false, false, false);
				}

				for (int j = 0; j < 3; j++)
				{
					oamSet(&oamSub, j+3, -256+32*(j+3)+i, 66, 0, 0, SpriteSize_32x16, SpriteColorFormat_256Color, tilessub[j+6], -1, false, false, false, false, false);
				}
			}
			
			oamUpdate(&oamSub);
			swiWaitForVBlank();
		}
	}
}

// Fades in the screen for 32 frames
void fade_in()
{
	for (int i = 0; i < 32; i++)
	{
		setBrightness(3, i / 2 - 16);
		swiWaitForVBlank();
	}
}

// Fades out the screen for 32 frames
void fade_out()
{
	for (int i = 0; i < 32; i++)
	{
		setBrightness(3, -1 * i / 2 - 1);
		swiWaitForVBlank();
	}
}

int title_screen()
{
	int difficulty = 0;
	int active_button = 1;

	// Initiate the main background
	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	dmaCopy(bgBitmap, bgGetGfxPtr(bg3), sizeof(bgBitmap));
	dmaCopy(bgPal, BG_PALETTE, sizeof(bgPal));

	// Initiate the sub background
	int bgsub3 = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	dmaCopy(bgsubBitmap, bgGetGfxPtr(bgsub3), sizeof(bgsubBitmap));
	dmaCopy(bgsubPal, BG_PALETTE_SUB, sizeof(bgsubPal));

	// Sound effect stuff
	mmLoadEffect(SFX_MOVE);
	mmLoadEffect(SFX_CLICK);
	mmLoadEffect(SFX_CLICKB);

	mmLoad(MOD_TITLE_SCREEN);

	mm_sound_effect sfx_move =
	{
		{SFX_MOVE}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	mm_sound_effect sfx_click =
	{
		{SFX_CLICK}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	mm_sound_effect sfx_clickb =
	{
		{SFX_CLICKB}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	// Start playing title screen music
	mmStart(MOD_TITLE_SCREEN, MM_PLAY_LOOP);

	// Set volume to 512 (half)
	mmSetModuleVolume(512);

	// Fade in the screen
	fade_in();

	/*touchPosition touch;
	touchRead(&touch);*/

	singlebreak:

	// This will only be true if multiplayer is turned on
	is_multiplayer = !difficulty;

	// Reset button position
	active_button = 1;

	// Draw buttons (with sliding effect)
	draw_buttons(2, active_button, true);

	while (true)
	{
		// Draw buttons (without sliding effect)
		draw_buttons(2, active_button, false);

		// Stay in while loop until nothing is pressed
		while (keys & KEY_UP || keys & KEY_DOWN || keys & KEY_A)
		{
			keys = keysHeld();
			scanKeys();
			swiWaitForVBlank();
		}

		while (true)
		{
			keys = keysHeld();
			scanKeys();

			if (keys & KEY_UP)
			{
				if (active_button > 1)
				{
					active_button--;
					mmEffectEx(&sfx_move);
				}

				break;
			}
			if (keys & KEY_DOWN)
			{
				if (active_button < 2)
				{
					mmEffectEx(&sfx_move);
					active_button++;
				}

				draw_buttons(2, active_button, false);
				break;
			}
			if (keys & KEY_A)
			{
				mmEffectEx(&sfx_click);
				draw_buttons(2, active_button, 2);

				difficulty = !(active_button-1);

				goto doublebreak;
			}

			swiWaitForVBlank();
		}

		swiWaitForVBlank();
	}

	doublebreak:

	// This will only be true if multiplayer is turned on
	is_multiplayer = !difficulty;

	// Reset button position
	active_button = 1;

	// Draw options (with sliding effect)
	draw_buttons(4, active_button, true);

	while (true)
	{
		// If multiplayer has been choosen, button number 0, and button number 3 become gray
		gray_button[0] = (joe1 == 1) || is_multiplayer;
		gray_button[3] = (joe1 == -1) || is_multiplayer;

		// Redraw options (without sliding effect)
		draw_buttons(4, active_button, false);

		// Stay in while loop until nothing is pressed
		while (keys & KEY_UP || keys & KEY_DOWN || keys & KEY_LEFT || keys & KEY_RIGHT || keys & KEY_A)
		{
			keys = keysHeld();
			scanKeys();
			swiWaitForVBlank();
		}

		while (true)
		{
			keys = keysHeld();
			scanKeys();

			if (keys & KEY_UP)
			{
				if (active_button > 1)
				{
					mmEffectEx(&sfx_move);
					active_button--;
				}
				break;
			}
			if (keys & KEY_DOWN)
			{
				if (active_button < 4)
				{
					mmEffectEx(&sfx_move);
					active_button++;
				}
				break;
			}
			if (keys & KEY_LEFT)
			{
				switch (active_button)
				{
					case 1:
						gray_button[0] = false;
						if (joe1 > -1) joe1--;
						difficulty = joe1+2;
						if (!(joe1 > -1)) gray_button[3] = true;
						break;
					case 2:
						gray_button[1] = false;
						if (joe2 > -1) joe2--;
						speed = joe2+1;
						if (!(joe2 > -1)) gray_button[4] = true;

						break;
					case 3:
						gray_button[2] = false;
						if (joe3 == 1) joe3--;
						settings_choices = 1;
						if (joe3 != 1) gray_button[5] = true;
						break;
				}				
				break;
			}
			if (keys & KEY_RIGHT)
			{
				switch (active_button)
				{
					case 1:
						gray_button[3] = false;
						if (joe1 < 1) joe1++;
						difficulty = joe1+2;
						if (!(joe1 < 1)) gray_button[0] = true;
						break;
					case 2:
						gray_button[4] = false;
						if (joe2 < 1) joe2++;
						speed = joe2+1;
						if (!(joe2 < 1)) gray_button[1] = true;
						break;
					case 3:
						gray_button[5] = false;
						if (joe3 == 0) joe3++;
						settings_choices = joe3;
						if (joe3 != 0) gray_button[2] = true;
						break;
				}
				break;
			}
			if (keys & KEY_A)
			{
				if (active_button == 4)
				{
					mmEffectEx(&sfx_click);
					goto triplebreak;
				}
			}
			if (keys & KEY_B)
			{
				mmEffectEx(&sfx_clickb);
				oamClear(&oamSub, 16, 24);
				oamUpdate(&oamSub);
				goto singlebreak;
			}

			swiWaitForVBlank();
		}

		swiWaitForVBlank();
	}

	triplebreak:

	// Clear all sprites used
	oamClear(&oamSub, 0, 0);
	oamUpdate(&oamSub);

	// Fade out the screen and the music for 32 frames
	for (int i = 0; i < 32; i++)
	{
		setBrightness(3, -1 * i / 2 - 1);
		mmSetModuleVolume(512 - i*16 - 32);

		swiWaitForVBlank();
	}

	// Hide the background
	bgHide(bg3);
	bgHide(bgsub3);

	keys = keysHeld();
	scanKeys();

	// If L+R are being pressed, activate the hidden paddle
	if (keys & KEY_R && keys & KEY_L)
	{
		secretdiscovered = true;
	}

	// Return the difficulty (will be 0 if multiplayer was chosen)
	return difficulty;
}

// Prints out the score in big fancy numbers
void seven_segment_draw(int index, int x, int y, int number)
{
	// If the score is more than one digit, instead print each digit of the score separately
	if (number > 9)
	{
		seven_segment_draw(index, x, y, number / 10);
		seven_segment_draw(index + 7, x + 24, y, number % 10);
		return;
	}

	// 7 bits is all we need for a seven segment display!
	char wtf[10] = {2, 103, 72, 24, 21, 48, 32, 30, 0, 16};
	//	[0] = 2;	00000010
	//	[1] = 103;	01100111
	//	[2] = 72;	01001000
	//	[3] = 24;	00011000
	//	[4] = 21;	00010101
	//	[5] = 48;	00110000
	//	[6] = 32;	00100000
	//	[7] = 30;	00011110
	//	[8] = 0;	00000000
	//	[9] = 16;	00010000

	for (int i = 0; i < 7; i++)
	{
		oamSet(&oamMain, index + i, x - (i > 2)*22 + (i > 4)*16 , y + (i > 2 ? !(i&1)*16 : i*14), 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[(i > 2) ? HORIZONTAL_LINE : VERTICAL_LINE], -1, false, wtf[number] >> i & 1, true, false, false);
	}
}

// Runs various checks to make sure that nothing is out of place
void check_legitimacy()
{
	// Sound effect stuff
	mmLoadEffect(SFX_PING);
	mmLoadEffect(SFX_PONG);

	mm_sound_effect sfx_ping =
	{
		{SFX_PING}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	mm_sound_effect sfx_pong =
	{
		{SFX_PONG}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	if (vx < 0)
	{
		vx = vx - 0.0004;
	}
	else if (vx > 0)
	{
		vx = vx + 0.0004;
	}

	if (vy < 0)
	{
		vx = vx - 0.0004;
	}
	else if (vy > 0)
	{
		vy = vy + 0.0004;
	}

	// Check if the ball hits the wall
	if (bally > 182 || bally < 0)
	{
		vy = -vy;
		x0 = ballx;
		y0 = bally;
		t = 0;

		mmEffectEx(&sfx_pong);
	}

	// Check if the ball hits a player
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

		mmEffectEx(&sfx_ping);
	}

	if (ballx < -16)
	{
		rscore++;
		ballout = true;
	}
	else if (ballx > 256)
	{
		lscore++;
		ballout = true;
	}

	// Check if the bullet belonging to player 1 is not out of bounds
	if (bulletlx < 256 && bulletlactivate)
	{
		bulletlx = bulletlx + 2 + 2 * ((!(mystery_box_effect - 3) * !r_has_effect));
	}
	else
	{
		bulletlx = 0;
		bulletlactivate = false;
		bulletly = paddlely;
	}

	// Check if the bullet belonging to player 2 is not out of bounds
	if (bulletrx > -16 && bulletractivate)
	{
		bulletrx = bulletrx - 2 - 2 * ((!(mystery_box_effect - 3) * r_has_effect));
	}
	else
	{
		bulletrx = 230;
		bulletractivate = false;
		bulletry = paddlery;
	}

	// Check if player 1 has been shot
	if (bulletrx < 4 && bulletry > paddlely - 16 && bulletry < paddlely + 20)
	{
		ldead = true;
	}

	// Check if player 2 has been shot
	if (bulletlx > 226 && bulletly > paddlery - 16 && bulletly < paddlery + 20)
	{
		rdead = true;
	}
}

void check_player_input()
{
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
}

void check_cpu_input()
{
	switch (difficulty)
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
				if (paddlery > PADDLEYSTART)
				{
					paddlery--;
				}
				else if (paddlery < PADDLEYSTART)
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
				if (paddlery > PADDLEYSTART)
				{
					paddlery--;
				}
				else if (paddlery < PADDLEYSTART)
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
				if (paddlery > PADDLEYSTART)
				{
					paddlery--;
				}
				else if (paddlery < PADDLEYSTART)
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
}

void get_mystery_box_effect(bool player1)
{
	mystery_box_effect = rand() % 4 + 1;
	r_has_effect = !player1;

	// Sound effect stuff
	mmLoadEffect(SFX_POWERUP);
	mm_sound_effect sfx_powerup =
	{
		{SFX_POWERUP}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	mmEffectEx(&sfx_powerup);

	switch (mystery_box_effect)
	{
		case 1:
			// Mini Potion
			break;
		case 2:
			// Mega Potion
			break;
		case 3:
			// Recharge gun
			break;
		case 4:
			// Nuke gun
			break;
	}
}

void mystery_boxes(int time)
{
	// Sound effect stuff
	mmLoadEffect(SFX_BOX_SUMMON);
	mm_sound_effect sfx_boxsummon =
	{
		{SFX_BOX_SUMMON}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	if (megacorp < 1)
	{
		megacorp = rand() % FRAMES_BEFORE_MYSTERYBOX + FRAMES_BEFORE_MYSTERYBOX/2 + time;
		gigacorpx = rand() % (256 - 128) + 64;
		gigacorpy = rand() % (128 - 64) + 32;
	}
	else if (megacorp <= time)
	{
		// Rotate the box 0.5° every frame
		oamRotateScale(&oamMain, 0, degreesToAngle(time/2), intToFixed(1, 8), intToFixed(1, 8));

		oamSet(&oamMain, 52, gigacorpx, gigacorpy, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[13], 0, true, false, false, false, false);
		oamSet(&oamMain, 51, gigacorpx+16, gigacorpy+16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[14], -1, false, false, false, false, false);

		if (megacorp == time)
		{
			mmEffectEx(&sfx_boxsummon);
		}
		// L gets item
		else if (bulletlx > gigacorpx - 8 && bulletlx < gigacorpx + 24 && bulletly > gigacorpy - 8 && bulletly < gigacorpy + 24)
		{
			megacorp = 0;
			oamClear(&oamMain, 51, 52);

			bulletlx = PLAYER1X;
			bulletlactivate = false;

			get_mystery_box_effect(true);
		}
		// R gets item
		else if (bulletrx > gigacorpx - 8 && bulletrx < gigacorpx + 24 && bulletry > gigacorpy - 8 && bulletry < gigacorpy + 24)
		{
			megacorp = 0;
			oamClear(&oamMain, 51, 52);

			bulletrx = PLAYER2X;
			bulletractivate = false;

			get_mystery_box_effect(false);
		}
	}
}

void magic_balls(int time)
{
	// Rotate the spheres 1° every frame
	oamRotateScale(&oamMain, 0, degreesToAngle(time), intToFixed(1, 8), intToFixed(1, 8));

	oamSet(&oamMain, 51, 120, 40, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[12], 0, true, false, false, false, false);
	oamSet(&oamMain, 52, 120, 120, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[12], 0, true, false, false, false, false);
}

void ballout_moment()
{
	// Sound effect stuff
	mmLoadEffect(SFX_BALLOUT);
	mm_sound_effect sfx_ballout =
	{
		{SFX_BALLOUT}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	for (int i = 0; ballout && i < 100; i++, swiWaitForVBlank())
	{
		if (i == 0)
		{
			mmEffectEx(&sfx_ballout);
		}
	}
}

void explode_moment()
{
	// Sound effect stuff
	mmLoadEffect(SFX_BOOM);
	mm_sound_effect sfx_boom =
	{
		{SFX_BOOM}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	for (int i = 0; i < 100 && (ldead || rdead); i++, swiWaitForVBlank())
		{
			switch(i)
			{
				case 5:
					mmEffectEx(&sfx_boom);
					explosion_frame++;
					break;
				case 10:
					explosion_frame++;
					break;
				case 15:
				case 20:
				case 25:
					explosion_frame--;
					break;
				default:
					break;
			}

			if (ldead)
			{
				oamSet(&oamMain, 4, PLAYER1X, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[explosion_frame+6], -1, false, explosion_frame < 0, false, false, false);
			}

			if (rdead)
			{
				oamSet(&oamMain, 5, PLAYER2X, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[explosion_frame+6], -1, false, explosion_frame < 0, true, false, false);
			}

			oamUpdate(&oamMain);
		}
}

void countdown()
{
	// Sound effect stuff
	mmLoadEffect(SFX_COUNTDOWN);
	mm_sound_effect sfx_countdown =
	{
		{SFX_COUNTDOWN}, (int)(1.0f * (1<<10)), 0, 255, 128
	};

	for (int i = 0; i < 260; i++, swiWaitForVBlank())
	{
		switch (i)
		{
			case 5:
				mmEffectEx(&sfx_countdown);
				break;
			default:
				break;
		}

		oamUpdate(&oamMain);
	}
}

int paddle_offset(int effect)
{
	switch (effect)
	{
		case 3:
			// Recharge gun
			return 4;
		case 4:
			// Nuke gun
			return 3;
		default:
			return secretdiscovered;
	}
}

int bullet_offset(int effect)
{
	switch (effect)
	{
		case 4:
			// Nuke gun
			return 5;
		default:
			return 2;
		}
}

int main(void) 
{
	// Initialize a bunch of stuff
	init_everything();

	// Enter the title screen
	difficulty = title_screen();

	// Fade in the screen
	fade_in();

	// Draw the dotted line in the middle of the field
	for (int i=7, j=4; i < 19; i++, j+=16)
	{
		oamSet(&oamMain, i, 123, j, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, tiles[0], -1, false, false, false, false, false);
	}

	// Draw the score of both playes
	seven_segment_draw(20, 90, 10, 0);
	seven_segment_draw(34, 140, 10, 0);

	while (1) 
	{
		// Increment both the time and the true time
		++t;
		++tt;

		ballx = (t < FRAMES_BEFORE_SPEEDUP-700*speed) ? (x0 + vx * t) : (x0 + vx * t * t / (FRAMES_BEFORE_SPEEDUP-700*speed));
		bally = (t < FRAMES_BEFORE_SPEEDUP-700*speed) ? (y0 + vy * t) : (y0 + vy * t * t / (FRAMES_BEFORE_SPEEDUP-700*speed));

		// Check for any oddities
		check_legitimacy();

		// Check if player 1 has moved their paddle or fired their pistol
		check_player_input();

		// Check if player 2 has moved their paddle or fired their pistol
		check_cpu_input();

		// Draw the paddles
		oamSet(&oamMain, 0, 0, paddlely, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[paddle_offset(!r_has_effect * mystery_box_effect)], -1, false, ldead, false, false, false);
		oamSet(&oamMain, 1, 225, paddlery, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[paddle_offset(r_has_effect * mystery_box_effect)], -1, false, rdead, true, false, false);

		// Draw the bullets
		oamSet(&oamMain, 2, bulletlx, bulletly, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[bullet_offset(!r_has_effect * mystery_box_effect)], -1, false, rdead || ldead || !bulletlactivate, false, false, false);
		oamSet(&oamMain, 3, bulletrx, bulletry, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, tiles[bullet_offset(r_has_effect * mystery_box_effect)], -1, false, rdead || ldead || !bulletractivate, true, false, false);

		// Spawn the screaming voice on the first frame
		if (tt == 1)
		{
			countdown();
		}

		// Draw the ball
		oamSet(&oamMain, 6, ballx, bally, 0, 0, SpriteSize_16x8, SpriteColorFormat_256Color, tiles[0], -1, false, false, false, false, false);

		// Switch statement to check settings
		switch (settings_choices)
		{
			// Mystery boxes
			case 1:
				mystery_boxes(t);
				break;
			// Magic shperes
			case 2:
				magic_balls(t);
				break;
			// Both boxes and shperes
			case 3:
				mystery_boxes(t);
				magic_balls(t);
				break;
		}

		// When the ball goes out of bounds, play a sound effect and wait 100 frames
		ballout_moment();

		// When a player gets shot, play a sound effect and animate the explosion for 100 frames 
		explode_moment();

		if (ldead || rdead || ballout)
		{
			// If player 1 is dead, increment player 2's score and vice versa
			if (ldead)
			{
				rscore++;
			}
			if (rdead)
			{
				lscore++;
			}

			// Reset everything (almost)
			reset();

			// Draw the score of both playes
			seven_segment_draw(20, 90, 10, lscore);
			seven_segment_draw(34, 140, 10, rscore);

		}

		// Write the changes to both screens
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		// Wait until the next frame
		swiWaitForVBlank();
	}

	return 0;
}
