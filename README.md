# Introduction

This game has been made by four students from CITM Terrassa. It is a tribute to Art Of Fighting original game, whitch is a martial art game created by Capcom in 1987.

The general plot happens in Southtown, a city in which Ryo and Robert, two karate students, have to save Ryo's sister, Yuri, who has been kidnapped by a misterious fighter.

# Installation

To install the game, it's only necessary to download the latest release: https://github.com/marcpt98/Fight-club/releases

When the installation is finished, it's time to click on the .exe file and enjoy the game.

# Controls (keyboard)

## Player 1

- A: Move left.

- D: Move right.

- W: Jump.

- S: Crouch.

- T: Punch.

- R: Kick.

- S+T: Crouch Punch.

- S+R: Crouch Kick.

- F: Special attack (Hadouken).

- F4: Insta Kill.

## Player 2

- J: Move left.

- L: Move right.

- I: Jump.

- K: Crouch.

- O: Punch.

- P: Kick.

- K+O: Crouch Punch.

- K+P: Crouch Kick.

- U: Special attack (Hadouken).

- F8: Insta kill.

## Other controls

- F3: Show collisions on screen with colours.

- F5: God mode (players without collisions).

- SPACE: Change scene.

- ESC: Exit game.

 # Controls (Gamepad):
    
- Joystick right(Player 1): Move forward.
- Joystick left(Player 1): Move backward.
- Joystick left(Player 2): Move forward.
- Joystick right(Player 2): Move backward.
- Joystick up: Jump.
- Joystick down: Crouch.
- X: Punch.
- Y: Kick.
- Joystick down + X: Punch crouch.
- Joystick down + Y: Kick crouch.
- Joystick up + X: Jump punch.
- Joystick up + Y: Jump Kick.
- Joystick left (Player 1, when other player is attacking): Protect.
- Joystick right (Player 2, when other player is attacking): Protect.
- START: Pass scene.</br>
- BACK: Exit game.</br>

# Changes for each version

## 0.0.5

Image movement from left to ride, with no music and SFX.

## 0.0.8-0.09

Stencil with scene 1 background and player Ryo implementation. Basic movements added.

## 0.2

Addition of 2 first background levels. Music from each level implemented.

## 0.3

SFX from moves implemented. Hadouken implemented.

## 0.35

Collisions added to both players and to hadouken.

## 0.5
Added new character spritesheet and background
Implemented gamepad state machine
Added some SFX from moves and 
solving esc bug

## 0.65

Added basic movements with gamepad. Only SFX from moves.
Pivot for animations added.

## 1.0
All SFX added.
King spritesheed 1 and 2 reimplemented.
All animations implemented.
Character selection added.
King vs king added.
Round system implemented.
Combos implemented.
Block animation implemented.
All UI system added, with health bars, stamine and scoreboard working.
Scene win implemented with score working, and it changes depending on the winner.
Crashing between rounds bug solved.

# Links

Github link: https://github.com/marcpt98/Fight-club.

## Students involved:

Marc Palma: https://github.com/marcpt98

Pol De La Torre: https://github.com/polf780

Macià Dalmau: https://github.com/maciadalmau

Pol Camacho: https://github.com/polcamacho
 
# Licenses and libraries

## Libraries

Library for SDL 2.0: http://www.libsdl.org/

Library for SDL_Image: http://www.libsdl.org/projects/SDL_image/

Library for SDL_Mixer: http://www.libsdl.org/projects/SDL_mixer/

## License

This library is distributed under the terms of the zlib license:
http://www.zlib.net/zlib_license.html

zlib.h -- interface of the 'zlib' general purpose compression library
  version 1.2.11, January 15th, 2017

  Copyright (C) 1995-2017 Jean-loup Gailly and Mark Adler

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Jean-loup Gailly        Mark Adler
  jloup@gzip.org          madler@alumni.caltech.edu

Note: For technical problems, we were unable to implement machine states for player 2. Also, it's missing kick and punch when the player is jumping.
