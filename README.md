[![C/C++ CI](https://github.com/JohnChristianCastillo/TurboHiker/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/JohnChristianCastillo/TurboHiker/actions/workflows/c-cpp.yml)
# TURBO HIKER 
## How to run:
To build the game, simply run the build script `build.sh`  
To build and run the game,simply run the run script `run.sh`

## How to play:
_(optional)_ 
 - select the background with the **LEFT** and **RIGHT** arrow keys   
 - select the main character's skin with the **UP** and **DOWN** arrow keys 

Press **ENTER** to start the game

## Controls:
**UP** arrow key to accelerate  
**LEFT** arrow key to move left  
**RIGHT** arrow key to move right  
**S** key to scream and cause panic towards every entity on the screen  
**E** consume `summon entity` power up  

## Rules:
The goal is to reach the finish line first without causing any trouble towards the other `ENEMY ENTITIES` in the game.  
Crashing into enemy entities slows your player down and deducts points.   
Screaming causes enemies to panic and make them manouver randomly(either left or right). If the enemy panics too much it throws them off the map and leads to more points being deducted from you. 

## ENTITIES:
Entities can be classified into two categories: **ENEMY** and **POWERUP**
**ENEMY** entities can then be further split into three categories:
 - `Left to right entity`: This is an entity that hinders players by moving left and right
 - `Static entity`: This is an entity that just stays still 
 - `AI entity`: This entity races with your character towards the finish line
 
 **POWERUP** entities can be split into FOUR categories:
  interacting(colliding) with any of these entities can either grant you a passive or an active power up
  - `Invincibility star entity`(passive): Turns the player invulnerable for a short duration
  - `Speed boost entity`(passive): Accelerates that player for a short duration
  - `Laser beam entity`(passive): Fires a short distance laser for a short duration
  - `Nuke entity`(passive): Wipes all enemy entities (excluding the AI and your character) off the screen
  - `Summon entity`(active): Summons a static hiker behind your character.
 
 
