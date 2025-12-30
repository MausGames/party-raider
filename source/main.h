//////////////////////////////////////////////////////////////////////////////////
//*----------------------------------------------------------------------------*//
//| Party Raider v1.0.0 (https://www.maus-games.at)                            |//
//*----------------------------------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics                                        |//
//|                                                                            |//
//| This software is provided 'as-is', without any express or implied          |//
//| warranty. In no event will the authors be held liable for any damages      |//
//| arising from the use of this software.                                     |//
//|                                                                            |//
//| Permission is granted to anyone to use this software for any purpose,      |//
//| including commercial applications, and to alter it and redistribute it     |//
//| freely, subject to the following restrictions:                             |//
//|                                                                            |//
//| 1. The origin of this software must not be misrepresented; you must not    |//
//|    claim that you wrote the original software. If you use this software    |//
//|    in a product, an acknowledgment in the product documentation would be   |//
//|    appreciated but is not required.                                        |//
//|                                                                            |//
//| 2. Altered source versions must be plainly marked as such, and must not be |//
//|    misrepresented as being the original software.                          |//
//|                                                                            |//
//| 3. This notice may not be removed or altered from any source distribution. |//
//*----------------------------------------------------------------------------*//
//////////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_MAIN_H_
#define _PAR_GUARD_MAIN_H_

// TODO 3: implement instancing: beverages, players, field


// ****************************************************************
// engine headers
#include "Core.h"


// ****************************************************************
// general definitions
#define PLAYERS             (2u)

#define PLAYER_HEALTH       (10)
#define PLAYER_SPEED        (18.0f * 0.3f)
#define PLAYER_ACCELERATION (200.0f)
#define PLAYER_BRAKE        (coreVector2(16.0f,8.6f))
#define PLAYER_SHOOT_POWER  (150.0f)
#define PLAYER_SHOOT_RATE   (7.0f)
#define PLAYER_CONTROL_NONE (0xFFu)

#define GAME_LEVELS         (6u)
#define GAME_WAIT           (1.0f)
#define GAME_COUNTDOWN      (3.0f)
#define GAME_TIME           (50.0f)
#define GAME_DELAY          (2.0f)

#define FIELD_SIZE          (coreVector2(76.0f,70.0f))
#define FIELD_SPACE         (coreVector2(90.0f,90.0f))
#define FIELD_THICK         (1.0f)
#define FIELD_DEPTH         (10.0f)
#define FIELD_GROUNDS       (8u)

#define COLOR_PLAYER_1      (COLOR_GREEN)
#define COLOR_PLAYER_2      (COLOR_YELLOW)

#define CAMERA_POSITION     (coreVector3(0.0f, 0.0f, 110.0f))
#define CAMERA_DIRECTION    (coreVector3(0.0f, 0.0f,  -1.0f))
#define CAMERA_ORIENTATION  (coreVector3(0.0f, 1.0f,   0.0f))

enum eType : coreInt32
{
    TYPE_PLAYER = 1,
    TYPE_GROUND,
    TYPE_BULLET
};


// ****************************************************************
// game headers
#include "Field.h"
#include "Player.h"
#include "Bullet.h"
#include "Interface.h"
#include "Game.h"


// ****************************************************************
// global variables
extern CField* const g_pField;
extern CGame*  const g_pGame;


#endif // _PAR_GUARD_MAIN_H_