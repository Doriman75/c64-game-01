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

char frame,mirror=0,move=0,collision=0;
unsigned x,y;

unsigned head_position()
{
	return SCR_SCREEN_MEMORY+81+(x>>3)+40*(y>>3);
}

unsigned feet_position()
{
	return SCR_SCREEN_MEMORY+121+(x>>3)+40*(y>>3);
}
char feet()
{
	return PEEK(feet_position());
}
char head()
{
	return PEEK(head_position());
}
char f()
{
	char f1=1,f2=1,k;
	char f;
	f = feet() == 226?1:0;
	k = mirror+(f<<1)+(move<<2);
	/*
	asm ("jsr $E566");
	printf("h: %3d, f: %3d, k: %d",head(),feet(),k);
	*/
	switch(k)
	{
		case 2: f1=8; f2=8; break;
		case 3: f1=11; f2=11; break;
		case 6: f1=8; f2=11; break;
		case 7: f1=11; f2=8; break;
		case 0: f1 = f2 = 1; break;
		case 4: f1=2; f2=3; break;
		case 5: f1=4; f2=5; break;
		case 1: f1=f2=12; break;
	}

	return (frame % SPEED < SPEED/2?f1:f2)-1;
}

void main(void) {
	char joy;
	x = 16;
	y = 106;

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
	
	sprite_define(0, sprite0, f());	
	POKE(feet_position(),160);

	while(1);
	return;
	
	while(1)
	{
		char last_mirror=0, last_move=0, last_collision=0,current_feet=0;
		collision = sprite_background_collision(0);
		current_feet = feet();
		if(!collision || current_feet==32) y++;


		move = 0;
		joy = joystick();
		if(!(joy & _JOY_DOWN) && y<199 && feet()==226 ) y++;
		if(!(joy & _JOY_RIGHT) && x<290 && collision) { x+=2; mirror = 0; move=1;};

		if(!(joy & _JOY_UP) && head()==226) { y--; move=1;}
		if(!(joy & _JOY_LEFT) && x>4 && collision) { x-=2; mirror = 1; move=1;};
		
		sprite_setX(0,x);
		sprite_setY(0,y);
		
		if(last_mirror != mirror || last_move != move || last_collision != collision)
		{
			sprite_define(0, sprite0, f());	
			last_mirror = mirror;
			last_move = move;
			last_collision = collision;
		}
		frame++;
		waitvsync();		
	}
	
}

