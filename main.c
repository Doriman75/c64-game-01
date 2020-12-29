#include <stdio.h>
#include <stdlib.h>
#include <cbm.h>
#include <c64.h>
#include <peekpoke.h>
#include "const.h"
#include "scr.h"
#include "joy.h"
#include "sprite.h"


#include "sprite0.h"

#include "level000_screen.h"
#include "level000_color.h"
#include "charset.h"

#define SPEED 10
#define EMPTY 32

unsigned char frame,mirror=0,move=0,collision=0,fuel=40;
unsigned x,y, feet, head,left,right;
unsigned char i;

unsigned address()
{
	return SCR_SCREEN_MEMORY + (x>>3) + (40*((3+y)>>3));
}

unsigned _feet()
{
	unsigned a;
	char result;
	a = address() + 80;
	result = PEEK(a);
	for(i=1; i <=2;i++) if(PEEK(a+i)>result) result = PEEK(a+i);
	return result;
}

unsigned _head()
{
	unsigned a;
	char result;
	a = address();
	result = PEEK(a);
	for(i=1; i <=2;i++)	if(PEEK(a+i)>result) result = PEEK(a+i);
	return result;
}

unsigned _right()
{
	unsigned a;
	char result;
	a = address()+3;
	result = PEEK(a);
	for(i=0;i<40*2;i+=40) if(PEEK(a+i)>result) result = PEEK(a+i);
	return result;
}

unsigned _left()
{
	unsigned a;
	char result;
	a = address()-1;
	result = PEEK(a);
	for(i=0;i<40*2;i+=40) if(PEEK(a+i)>result) result = PEEK(a+i);
	return result;
}

char f()
{
	unsigned char f1=1,f2=1,k,f;
	f=(feet==EMPTY)?0:1;
	k = mirror+(f<<1)+(move<<2);
	//asm ("jsr $E566"); printf("k: %3d",k);
	switch(k)
	{
		case 2: f1=1; f2=1; break;
		case 3: f1=6; f2=6; break;
		case 6: f1=2; f2=3; break;
		case 7: f1=4; f2=5; break;
		case 0: f1=f2=1; break;
		case 4: f1=7; f2=8; break;
		case 5: f1=9; f2=10; break;
		case 1: f1=f2=6; break;
	}

	return (frame % SPEED < SPEED/2?f1:f2)-1;
}

void draw_fuel()
{
	for(i=0; i < fuel; i++) POKE(SCR_COLOR_MEMORY+i+1000-40, YELLOW);
	for(i=fuel; i < 40; i++) POKE(SCR_COLOR_MEMORY+i+1000-40, RED);
}

void main(void) {
	char joy;
	x = 48;
	y = EMPTY;

	scr_clear();
	
	scr_background(BLACK);
	scr_border(BLACK);
	scr_load(level000_screen,level000_color,charset); 
	scr_multicolor(ON, WHITE, LIGHTGREEN);
	
	sprite_init();
	sprite_double_x(0,OFF);
	sprite_double_y(0,OFF);
	sprite_color(0, DARKGREY,WHITE, LIGHTGREY);
	sprite_define(0, sprite0, f());	
	sprite_on(0);
	sprite_setX(0,x);
	sprite_setY(0,y);

	while(1)
	{
		feet = _feet();
		head = _head();
		left = _left();
		right = _right();
		if(feet == EMPTY) y++;
		move = 0;
		joy = joystick();
		//if(!(joy & _JOY_DOWN)) { y++; move=1; }
		if(!(joy & _JOY_RIGHT) && right==EMPTY) { x+=2; mirror = 0; move=1;};
		if(!(joy & _JOY_FIRE) && head==EMPTY && fuel > 0) { y-=2; move=1; if(frame == SPEED) { fuel--; draw_fuel(); } }
		if(!(joy & _JOY_LEFT) && left==EMPTY) { x-=2; mirror = 1; move=1;};
		
		sprite_setX(0,x);
		sprite_setY(0,y);		
		sprite_define(0, sprite0, f());	

		frame++;
		waitvsync();		
	}	
}

