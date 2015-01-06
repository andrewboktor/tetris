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
#include "piece.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
piece *piece_new ( int x, int y, piece_type type )
{
	piece *new_piece = malloc ( sizeof ( piece ) );
	
	new_piece->posx = x;
	new_piece->posy = y;
	
	new_piece->type = type;
	new_piece->direction = DIRECTION_U;
	switch ( type )
	{
		case I:	new_piece->cubes[0] = cube_new ( -1, 0, 1.0, 0.0, 0.0 );
				new_piece->cubes[1] = cube_new ( 0, 0, 1.0, 0.0, 0.0 );
				new_piece->cubes[2] = cube_new ( 1, 0, 1.0, 0.0, 0.0 );
				new_piece->cubes[3] = cube_new ( 2, 0, 1.0, 0.0, 0.0 );
				break;
				
		case T:	new_piece->cubes[0] = cube_new ( -1, 0, 0.5, 0.5, 0.5 );
				new_piece->cubes[1] = cube_new ( 0, 0, 0.5, 0.5, 0.5 );
				new_piece->cubes[2] = cube_new ( 1, 0, 0.5, 0.5, 0.5 );
				new_piece->cubes[3] = cube_new ( 0, 1, 0.5, 0.5, 0.5 );
				break;
				
		case Q:	new_piece->cubes[0] = cube_new ( 0, 0, 0.0, 1.0, 1.0 );
				new_piece->cubes[1] = cube_new ( 1, 0, 0.0, 1.0, 1.0 );
				new_piece->cubes[2] = cube_new ( 0, 1, 0.0, 1.0, 1.0 );
				new_piece->cubes[3] = cube_new ( 1, 1, 0.0, 1.0, 1.0 );
				break;
				
		case L:	new_piece->cubes[0] = cube_new ( 1, 0, 1.0, 1.0, 0.0 );
				new_piece->cubes[1] = cube_new ( -1, 1, 1.0, 1.0, 0.0 );
				new_piece->cubes[2] = cube_new ( 0, 1, 1.0, 1.0, 0.0 );
				new_piece->cubes[3] = cube_new ( 1, 1, 1.0, 1.0, 0.0 );
				break;
		
		case J:	new_piece->cubes[0] = cube_new ( -1, 0, 1.0, 0.0, 1.0 );
				new_piece->cubes[1] = cube_new ( -1, 1, 1.0, 0.0, 1.0 );
				new_piece->cubes[2] = cube_new ( 0, 1, 1.0, 0.0, 1.0 );
				new_piece->cubes[3] = cube_new ( 1, 1, 1.0, 0.0, 1.0 );
				break;
				
		case Z:	new_piece->cubes[0] = cube_new ( -1, 0, 0.0, 0.0, 1.0 );
				new_piece->cubes[1] = cube_new ( 0, 0, 0.0, 0.0, 1.0 );
				new_piece->cubes[2] = cube_new ( 0, 1, 0.0, 0.0, 1.0 );
				new_piece->cubes[3] = cube_new ( 1, 1, 0.0, 0.0, 1.0 );
				break;		
		
		case S:	new_piece->cubes[0] = cube_new ( 0, 0, 0.0, 1.0, 0.0 );
				new_piece->cubes[1] = cube_new ( 1, 0, 0.0, 1.0, 0.0 );
				new_piece->cubes[2] = cube_new ( -1, 1, 0.0, 1.0, 0.0 );
				new_piece->cubes[3] = cube_new ( 0, 1, 0.0, 1.0, 0.0 );
				break;
	}
	
	return new_piece;	
}



void piece_draw ( piece* p )
{
	cube_draw ( p->cubes[0], p->posx+p->cubes[0]->posx, p->posy+p->cubes[0]->posy );
	cube_draw ( p->cubes[1], p->posx+p->cubes[1]->posx, p->posy+p->cubes[1]->posy );
	cube_draw ( p->cubes[2], p->posx+p->cubes[2]->posx, p->posy+p->cubes[2]->posy );
	cube_draw ( p->cubes[3], p->posx+p->cubes[3]->posx, p->posy+p->cubes[3]->posy );
}


void piece_rotate ( piece* p)
{
	/*
	int temp=0, i=0;
	if ( p->direction == DIRECTION_U || p->direction == DIRECTION_D )
	{
		i=0;
		while ( i<4 )
		{
			temp = p->cubes[i]->posx;
			p->cubes[i]->posx = p->cubes[i]->posy;
			p->cubes[i]->posy = temp;
			i++;
		}
	}
	else
	{
		i=0;
		while ( i<4 )
		{
			temp = p->cubes[i]->posx;
			p->cubes[i]->posx = p->cubes[i]->posy;
			p->cubes[i]->posy = -temp;
			i++;
		}
	}
	p->direction++;
	p->direction = p->direction % 4 ;
	* */
	
	int temp = 0, i = 0;
    int rightover=0, leftover=0;
	while ( i<4 )
	{
        //rotate transform
		temp = p->cubes[i]->posx;
		p->cubes[i]->posx = -p->cubes[i]->posy;
		p->cubes[i]->posy = temp;

        //Check if something is gonna poke out the left or right
        int templeftover = -(p->posx + p->cubes[i]->posx);
        if (leftover < templeftover) {
            leftover = templeftover;
        }
        int temprightover = GRID_WIDTH - 1 - (p->posx + p->cubes[i]->posx);
        if (temprightover < rightover) {
            rightover = temprightover;
        }
		i++;
	}
    //If something is gonna poke out, move the piece
    if(leftover || rightover) {
        p->posx+=leftover+rightover;
    }
}

