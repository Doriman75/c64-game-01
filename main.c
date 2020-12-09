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

unsigned char frame,mirror=0,move=0,collision=0,last_move=0,last_mirror=0;
unsigned x,y;


unsigned feet()
{
	unsigned address = SCR_SCREEN_MEMORY;
	char result,i;
	address += x>>3;
	address += 40*((3+y)>>3);
	address += 80;
	result = PEEK(address);
	for(i=1; i <=2;i++)
		if(PEEK(address+i)>result) result = PEEK(address+i);
	return result;
}

unsigned head()
{
	unsigned address = SCR_SCREEN_MEMORY;
	char result,i;
	address += x>>3;
	address += 40*((y-2)>>3);
	address += 0;
	result = PEEK(address);
	for(i=1; i <=2;i++)
		if(PEEK(address+i)>result) result = PEEK(address+i);
	return result;
}

unsigned right()
{
	unsigned address = SCR_SCREEN_MEMORY;
	char result,i;
	address += x>>3;
	address += 40*((3+y)>>3);
	address += 2;
	result = PEEK(address);
	for(i=0;i<40*2;i+=40)
		if(PEEK(address+i)>result) result = PEEK(address+i);
	return result;
}

unsigned left()
{
	unsigned address = SCR_SCREEN_MEMORY;
	char result,i;
	address += x>>3;
	address += 40*((3+y)>>3);
	address += 0;
	result = PEEK(address);
	for(i=0;i<40*2;i+=40)
		if(PEEK(address+i)>result) result = PEEK(address+i);
	return result;
}

char f()
{
	unsigned char f1=1,f2=1,k,f;
	f=feet()==32?0:1;
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

void main(void) {
	char joy;
	x = 48;
	y = 32;

	scr_clear();
	
	scr_multicolor(ON);
	scr_background(BLACK);
	scr_border(BLACK);
	scr_load(level000_screen,level000_color,charset); 
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
		if(feet()==32) y++;
		right();
		move = 0;
		joy = joystick();
		//if(!(joy & _JOY_DOWN)) { y++; move=1; }
		if(!(joy & _JOY_RIGHT) && right()==32) { x+=2; mirror = 0; move=1;};
		if(!(joy & _JOY_UP) && head()==32) { y-=2; move=1;}
		if(!(joy & _JOY_LEFT) && left()==32) { x-=2; mirror = 1; move=1;};
		
		sprite_setX(0,x);
		sprite_setY(0,y);
		
		sprite_define(0, sprite0, f());	
		if(last_mirror != mirror || last_move != move)
		{
			last_mirror = mirror;
			last_move = move;
		}
		frame++;
		waitvsync();		
	}	
}

