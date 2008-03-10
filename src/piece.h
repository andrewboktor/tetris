/*
 * This file is part of Andrew's Tetris
 * 
 * Andrew's Tetris GLUT/OpenGL based Tetris.
 * Copyright (C) 2008  Andrew Mofid Botros Boktor
 * http://andrewboktor.googlecode.com
 * 
 * Andrew's Tetris is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Andrew's Tetris is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GLTetris.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PIECE_H_
#define _PIECE_H_

#include "cube.h"

enum _piece_type
{
	I = 0,
	T = 1,
	Q = 2,
	J = 3,
	L = 4,
	Z = 5,
	S = 6	
};

enum _piece_direction
{
	DIRECTION_U = 0,
	DIRECTION_R = 1,
	DIRECTION_D = 2,
	DIRECTION_L = 3
};
typedef enum _piece_direction piece_direction;

typedef enum _piece_type piece_type;

struct _piece
{
	int posx, posy;
	cube *cubes [4];
	float color_R, color_G, color_B;
	piece_type type;
	piece_direction direction;
};

typedef struct _piece piece;

piece *piece_new ( int x, int y, piece_type type );
void piece_draw ( piece* p );


#endif
