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

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "piece.h"

#define WIN_WIDTH 600			/* Window Width */
#define WIN_HEIGHT 800			/* Window Height */
#define WIN_POS_X 100			/* Window Position X */
#define WIN_POS_Y 100			/* Window Position Y */
#define WIN_TITLE "Andrew's Tetris"		/* Window's Title */

#define BG_COLOR_R 1.0
#define BG_COLOR_G 1.0
#define BG_COLOR_B 1.0
#define BG_COLOR_A 0.0

#define GRID_COLOR_R 0.8
#define GRID_COLOR_G 0.8
#define GRID_COLOR_B 0.8

enum _level
{
	level01 = 10,
	level02 = 9,
	level03 = 8,
	level04 = 7,
	level05 = 6,
	level06 = 5,
	level07 = 4,
	level08 = 3,
	level09 = 2,
	level10 = 1
};

typedef enum _level level;

level game_level;
int number_of_lines;

#define GRID_HEIGHT 20
#define GRID_WIDTH 10

piece* in_air;
piece* next_piece;
int animation_running;
int score;
cube* well [10][20];
int game_paused;
int game_over;
#endif
