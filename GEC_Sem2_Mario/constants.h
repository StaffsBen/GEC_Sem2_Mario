#pragma once
#ifndef _CONSTANTS_H
#define _CONSTANTS_H

//Screen dimensions
#define SCREEN_WIDTH 512 //512 //600
#define SCREEN_HEIGHT 412 //416 //671

//LevelMap dimensions
#define MAP_HEIGHT 13
#define MAP_WIDTH 16

//tile dimensions
#define TILE_HEIGHT 32
#define TILE_WIDTH 32

//player movement speed
#define MOVEMENTSPEED 100.0f

//gravity value
#define GRAVITYVALUE 260.0F

//jump force values
#define JUMP_FORCE_DECREMENT 400.0f
#define INITIAL_JUMP_FORCE 600.0f

//Koopa values
#define INJURED_TIME 2.5f
#define KOOPA_SPEED 96.0f
#define NEW_KOOPA_TIMER 5.5f
#define MAX_KOOPA_NUM 5

//Coin values
#define ANIMATION_DELAY 0.1f

//screen shake value
#define SHAKE_DURATION 0.25f

//sprite sheet vars
#define MARIO_SPRITE_POS_X 7
#define MARIO_SPRITE_POS_Y 1206
#define MARIOLUIGI_SPRITE_DIV_WIDTH 28
#define MARIOLUIGI_SPRITE_DIV_HEIGHT 32
#define LUIGI_SPRITE_POS_X 9
#define LUIGI_SPRITE_POS_Y 1278
#define KOOPA_SPRITE_POS_X 15
#define KOOPA_SPRITE_POS_Y 665
#define KOOPA_SPRITE_DIV_WIDTH 28
#define KOOPA_SPRITE_DIV_HEIGHT 43
#define KOOPA_SPRITE_DRAW_ADJUST 5
#define CENTRAL_X_POSITION_ADJUST 27
#define FOOT_POSITION_ADJUST 32
#define COLLISIONBOX_WIDTH_ADJUST 28
#define COLLISIONBOX_HEIGHT_ADJUST 32

//vars
//double _imageAngle;

#endif _CONSTANTS_H