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

#include "cube.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

cube *cube_new ( int x, int y, float r, float g, float b )
{
	cube *new_cube = malloc ( sizeof ( cube ) );
	new_cube->posx = x;
	new_cube->posy = y;
	new_cube->color_R = r;
	new_cube->color_G = g;
	new_cube->color_B = b;
	return new_cube;
}


void cube_draw ( cube* c , int x, int y )
{
	glColor3f ( c->color_R, c->color_G, c->color_B );
	glRecti ( x*CUBE_SIZE+1, y*CUBE_SIZE+1, (x+1)*CUBE_SIZE-1, (y+1)*CUBE_SIZE-1 );
}
