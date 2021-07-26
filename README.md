# Pistol Pong DS
![screenshot](https://i.imgur.com/a2jxjvi.png)

Pistol Pong DS is a game for the Nintendo DS, 
based on the classic game pong, but it has a twist, **there's guns**!

The game has two game modes, Singleplayer and Multiplayer. 
In Singleplayer you play against a CPU opponent, meanwhile in Multiplayer you play against another 
player (sharing the DS).

**Singleplayer works like this:**

* Control your paddle by pressing up and down on the dpad, and fire your gun by pressing right on the dpad
* If a player gets shot or misses the ball, the opposing player gains one point

**Multiplayer works like this:**

* Player 1 control their paddle by pressing up and down on the dpad, and fires their gun by pressing right on the dpad
* Player 2 control their paddle by pressing `X` to go up and `B` to go down, and fires their gun by pressing `Y`
* If a player gets shot or misses the ball, the opposing player gains one point

## Compiling
To compile this program you need DevkitPro with DevkitArm, libnds, maxmod, and grit.

When you have that installed, follow these steps:

1. Clone this repository with git, GitHub CLI, or any other tool.
2. Type `cd Pistol-Pong-DS`
3. Type `make`

*note that you need to have mingw installed if you want to compile on Windows*

## License

### Source code
All of Pistol Pong DS's source code is distributed under the GNU General Public License, 
more information can be found in the LICENSE document or online [here](https://www.gnu.org/licenses/gpl-3.0.en.html).

### Graphics and sound effects
All of the graphics (and most of the sound effects) were created by me and are therefore licensed under the aforementioned license, the GPL.
Some of the sound effects were not created by me and because of that I can't control how they're licensed.
The sound effects in question  can be found inside the `music` folder, titled:
* box_summon.wav
* powerup.wav

These have been found on [freesound.org](https://freesound.org/),
and are licensed under [CC0](https://creativecommons.org/publicdomain/zero/1.0/).
This license is less restrictive than the GPL, so fear not, you can still copy and distribute these sound effects if you wish.