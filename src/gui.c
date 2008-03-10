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

#include "gui.h"
#include "global.h"
#include "piece.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

void display_func ();
void keyboard_func ( unsigned char key, int x, int y );
void special_key_func ( int key, int x, int y );
void drop_in_air_piece (int value);
void check_bottom_boundary ();
void looper ();
void grid_draw ();
void add_in_air_to_well ();
void well_init ();
void well_draw ();
void check_and_remove_line ();
void animate ( int j );
void delay ( int i );
float min ( float x, float y);
int time_interval;
void in_air_new ();
void text_draw ();

char score_s [10];
char level_s [2];

void text_draw ()
{
	glColor3f ( 0, 0, 0 );
	glRasterPos2i ( 420, 50 );
	glutBitmapString ( GLUT_BITMAP_HELVETICA_18, "NEXT_PIECE" );
	
	glRasterPos2i ( 420, 220 );
	glutBitmapString ( GLUT_BITMAP_HELVETICA_18, "SCORE:" );
	
	sprintf ( score_s, "%d", score );
	glRasterPos2i ( 460, 250 );
	glutBitmapString ( GLUT_BITMAP_HELVETICA_18, score_s );
	
	
	glRasterPos2i ( 420, 300 );
	glutBitmapString ( GLUT_BITMAP_HELVETICA_18, "LEVEL:" );
	
	sprintf ( level_s, "%d", 11-game_level );
	glRasterPos2i ( 460, 330 );
	glutBitmapString ( GLUT_BITMAP_HELVETICA_18, level_s);
	
	glRasterPos2i ( 420, 400 );
	glutBitmapString ( GLUT_BITMAP_HELVETICA_18, "To Pause, Press \'p\'" );
	
	glRasterPos2i ( 420, 430 );
	glutBitmapString ( GLUT_BITMAP_HELVETICA_18, "To Restart, Press \'n\'" );
}

void in_air_new ()
{
	in_air = next_piece;
	in_air->posx = 3;
	in_air->posy = -2;
	next_piece = piece_new ( 12, 2, rand ()%7 );
}


float min ( float x, float y)
{
	if ( x>y ) return y;
	else return x;
}

void window_init ( int argc, char** argv )
{
	glutInit ( &argc, argv );
	glutInitDisplayMode ( GLUT_DOUBLE );
	glutInitWindowSize ( WIN_WIDTH, WIN_HEIGHT );
	glutInitWindowPosition ( WIN_POS_X, WIN_POS_Y );
	glutCreateWindow ( WIN_TITLE );
	
	glutDisplayFunc ( display_func );
	glutKeyboardFunc ( keyboard_func );
	glutSpecialFunc ( special_key_func );
}

void gl_init ()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor ( BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	gluOrtho2D ( 0, WIN_WIDTH, WIN_HEIGHT, 0 );	
}

void game_init ()
{
	game_over = 0;
	well_init ();
	time_interval = level01*100;
	game_level = level01;
	number_of_lines = 0;
	animation_running = 0;
	score = 0;
	game_paused = 0;
	next_piece = piece_new ( 12, 3, rand ()%7 );
	in_air_new ();
}

void game_start ()
{
	looper ();
}

void display_func ()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	grid_draw ();
	well_draw ();
	text_draw ();
	piece_draw ( in_air );
	piece_draw ( next_piece );
	if ( game_paused )
	{
		glEnable (GL_BLEND);
		glColor4f (1.0, 1.0, 1.0, 0.75);
		glRecti(0, 0, 400, 800);
		glColor3f(0, 0, 0);
		glRasterPos2i(170, 400);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Pause");
	}
	if ( game_over )
	{
		glEnable (GL_BLEND);
		glColor4f (1.0, 1.0, 1.0, 0.75);
		glRecti(0, 0, 400, 800);
		glColor3f(0, 0, 0);
		glRasterPos2i ( 150, 300 );
		glutBitmapString ( GLUT_BITMAP_HELVETICA_18, "GAME_OVER" );
	}
	
	glutSwapBuffers ();
}

void looper ()
{
	if ( !game_over && !game_paused)
	glutTimerFunc ( time_interval, drop_in_air_piece, 1 );
}

void drop_in_air_piece (int value)
{
	check_bottom_boundary ();
	check_and_remove_line ();
	in_air->posy++;
	
	glutPostRedisplay ();
	looper ();
}

void grid_draw ()
{
	glColor3f ( GRID_COLOR_R, GRID_COLOR_G, GRID_COLOR_B );
	
	
	int i=0;
	while ( i<GRID_WIDTH+1 )
	{
		glBegin ( GL_LINE_LOOP );
		glVertex2i ( i*CUBE_SIZE, 0*CUBE_SIZE );
		glVertex2i ( i*CUBE_SIZE, GRID_HEIGHT*CUBE_SIZE );
		glEnd ();
		i++;
	}
	i=0;
	while ( i<GRID_HEIGHT )
	{
		glBegin ( GL_LINE_LOOP );
		glVertex2i ( 0*CUBE_SIZE, i*CUBE_SIZE );
		glVertex2i ( GRID_WIDTH*CUBE_SIZE, i*CUBE_SIZE );
		glEnd ();
		i++;
	}
	
	
}

void keyboard_func ( unsigned char key, int x, int y )
{
	if ( key == 'p' )
	{
		game_paused = ~game_paused;
		if ( !game_paused ) drop_in_air_piece (1);
	}
	else if ( key == 'n' )
	{
		if ( game_paused || game_over)
		{
			game_init ();
			game_start ();
		}
		else game_init ();
	}
}

void special_key_func ( int key, int x, int y )
{
	if ( key == GLUT_KEY_DOWN )
	{
		if ( !animation_running && !game_over && ! game_paused)
		{
			check_bottom_boundary ();
			check_and_remove_line ();
			in_air->posy++;
			glutPostRedisplay ();
		}
	}
	else if ( key == GLUT_KEY_RIGHT )
	{
		if ( check_right_boundary () )
		{
			in_air->posx++;
			glutPostRedisplay ();
		}
	}
	else if ( key == GLUT_KEY_LEFT )
	{
		if ( check_left_boundary () )
		{
			in_air->posx--;
			glutPostRedisplay ();
		}
	}
	else if ( key == GLUT_KEY_UP )
	{
		piece_rotate ( in_air );
		glutPostRedisplay ();
	}
}

void check_bottom_boundary ()
{
	int i=0, j=0, k=0, x=0, y=0, cant_drop=0;
	while ( k<4 )
	{
		i=0, j=0, x=0, y=0;
		if ( in_air->cubes[k]->posy+in_air->posy >=GRID_HEIGHT-1 )
		{
			cant_drop = 1;
			break;
		}
		
		x = (in_air->cubes[k]->posx)+(in_air->posx);
		y = (in_air->cubes[k]->posy)+(in_air->posy);
		
		i=0; j=0;
		while ( i<GRID_WIDTH )
		{
			j=0;
			while ( j<GRID_HEIGHT )
			{
				if ( well[i][j]!=NULL)
				if ( x == i && y == j-1 )
				{
					cant_drop = 1;
					break;
				}
				j++;
			}
			i++;
		}
		k++;
		
	}
	if ( cant_drop )
	add_in_air_to_well ();
}

int check_right_boundary ()
{
	int i=0, j=0, k=0, x=0, y=0, can_move=1;
	while ( k<4 )
	{
		i=0, j=0, x=0, y=0;
		if ( in_air->cubes[k]->posx+in_air->posx >=9 )
		{
			can_move = 0;
			break;
		}
		
		x = (in_air->cubes[k]->posx)+(in_air->posx);
		y = (in_air->cubes[k]->posy)+(in_air->posy);
		
		i=0; j=0;
		while ( i<GRID_WIDTH )
		{
			j=0;
			while ( j<GRID_HEIGHT )
			{
				if ( well[i][j]!=NULL)
				if ( x == i-1 && y == j )
				{
					can_move = 0;
					break;
				}
				j++;
			}
			i++;
		}
		k++;
		
	}
	return can_move;
}

int check_left_boundary ()
{
	int i=0, j=0, k=0, x=0, y=0, can_move=1;
	while ( k<4 )
	{
		i=0, j=0, x=0, y=0;
		if ( in_air->cubes[k]->posx+in_air->posx <=0 )
		{
			can_move = 0;
			break;
		}
		
		x = (in_air->cubes[k]->posx)+(in_air->posx);
		y = (in_air->cubes[k]->posy)+(in_air->posy);
		i=0; j=0;
		while ( i<GRID_WIDTH )
		{
			j=0;
			while ( j<GRID_HEIGHT )
			{
				if ( well[i][j]!=NULL)
				if ( x == i+1 && y == j )
				{
					can_move = 0;
					break;
				}
				j++;
			}
			i++;
		}
		k++;
		
	}
	return can_move;
}

void well_init ()
{
	int i=0, j=0;
	while ( i<GRID_WIDTH )
	{
		j=0;
		while ( j<GRID_HEIGHT )
		{
			well[i][j]=NULL;
			j++;
		}
		i++;
	}
}

void well_draw ()
{
	int i=0, j=0;
	while ( i<GRID_WIDTH )
	{
		j=0;
		while ( j<GRID_HEIGHT )
		{
			if ( well[i][j]!=NULL)
			cube_draw ( well[i][j], i, j );
			j++;
		}
		i++;
	}
}

void add_in_air_to_well ()
{
	int i=0, x=0, y=0;
	while ( i<4 )
	{
		x = in_air->posx+in_air->cubes[i]->posx;
		y = in_air->posy+in_air->cubes[i]->posy;
		in_air->cubes[i]->posx = 0;
		in_air->cubes[i]->posy = 0;
		well [ x ][ y ] = in_air->cubes[i];
		
		if ( y <=0 ) game_over = 1;
		i++;
	}
	time_interval = game_level * 100;
	in_air_new ();
}

void check_and_remove_line ()
{
	animation_running=1;
	int i=0, j=GRID_HEIGHT, line_count = 0, line_flag = 0;
	while ( j>=0 )
	{
		i=0;
		line_flag=1;
		while ( i<GRID_WIDTH )
		{
			if ( line_flag && well [i][j]!=NULL);
			else line_flag = 0;
			if ( line_count )
			{
				well [i][j+line_count] = well [i][j];
			}
			i++;
		}
		if ( line_flag )
		{
			
			animate (j);
			animate (j);
			animate (j);
			line_count++;
		}
		j--;
	}
	number_of_lines += line_count;
	switch ( line_count )
	{
		case 4: score+=40;		/* it is intended to remove the break to provide an exponential score */
		case 3: score+=30;
		case 2: score+=20;
		case 1: score+=10;
	}
	if ( number_of_lines >=10 ) 
	{
		number_of_lines-=10;
		game_level--;
		time_interval = game_level * 100;
	}
	animation_running=0;
}

void animate ( int j )
{
	animation_running = 1;
	float color[10][3];// = float[10][3];
	int i = 0;
	while ( i<GRID_WIDTH && well[i][j]!=NULL )
	{
		color[i][0] = well[i][j]->color_R;
		color[i][1] = well[i][j]->color_G;
		color[i][2] = well[i][j]->color_B;
		well[i][j]->color_R = min(1,color[i][0] + 0.5);
		well[i][j]->color_G = min(1,color[i][1] + 0.5);
		well[i][j]->color_B = min(1,color[i][2] + 0.5);
		i++;
	}
	glutPostRedisplay ();
	display_func ();
	delay ( 29999999 );
	
	i=0;
	while ( i<GRID_WIDTH && well[i][j]!=NULL )
	{
		well[i][j]->color_R = color[i][0];
		well[i][j]->color_G = color[i][1];
		well[i][j]->color_B = color[i][2];
		i++;
	}
	glutPostRedisplay ();
	display_func ();
	delay ( 29999999 );
	
	animation_running = 0;
}

void delay ( int n )
{
	glutPostRedisplay ();
	int i=0;
	while ( i<n )
	{
		i++;
	}
}
