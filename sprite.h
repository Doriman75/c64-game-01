#include "const.h"
#define _SPRITE_VIC 0xD000

void sprite_init()
{
	register char i;
	for(i = 0; i < 8; i++) POKE(SCR_SCREEN_MEMORY+1016+i,12288/64+i);	
}

void sprite_define(char sprite_number, char *definition, char frame)
{
	unsigned address;
	char bit = 1<<sprite_number;
	address = PEEK(SCR_SCREEN_MEMORY+1016+sprite_number)<<6;
	expand(definition+(frame<<6)-frame, address ,64);
	POKE(_SPRITE_VIC+0x1c, PEEK(_SPRITE_VIC+0x1c) | bit);
}

void sprite_color(char sprite_number,char first_color, char second_color, char sprite_color)
{
	POKE(_SPRITE_VIC+39+sprite_number,sprite_color);
	POKE(_SPRITE_VIC+0x25,first_color);
	POKE(_SPRITE_VIC+0x26,second_color);
}

void _sprite_bit(char sprite_number,char on, unsigned address)
{
	char bit = 1<<sprite_number;
	char v = PEEK(address);
	v = on ? v | bit: v & (255-bit);
	POKE(address, v);
}

void sprite_double_x(char sprite_number,char on)
{
	_sprite_bit(sprite_number, on, _SPRITE_VIC+29);
}

void sprite_double_y(char sprite_number,char on)
{
	_sprite_bit(sprite_number, on, _SPRITE_VIC+23);
}

void sprite_setX(char sprite_number, unsigned x)
{
	POKE(_SPRITE_VIC+0+sprite_number * 2,24+x);
	_sprite_bit(sprite_number, x>255-24, _SPRITE_VIC+16);
}

unsigned sprite_getX(char sprite_number)
{
	unsigned result;
	result = PEEK(_SPRITE_VIC+0+sprite_number*2)-24;
	if(PEEK(_SPRITE_VIC+16) & (1<<sprite_number) != 0) result+=255;
	return result;
}

void sprite_setY(char sprite_number, unsigned y)
{
	POKE(_SPRITE_VIC+1+sprite_number*2,50+y);
}

unsigned sprite_getY(char sprite_number)
{
	return PEEK(_SPRITE_VIC+1+sprite_number*2)-50;
}

void sprite_on(char sprite_number)
{
	_sprite_bit(sprite_number, ON, _SPRITE_VIC+21);
}

void sprite_off(char sprite_number)
{
	_sprite_bit(sprite_number, OFF, _SPRITE_VIC+21);
}

char sprite_collision(char sprites)
{
	return (PEEK(_SPRITE_VIC+0x1e) & sprites) ? ON: OFF;
}

char sprite_background_collision(char sprite_number)
{
	return (PEEK(_SPRITE_VIC+0x1f) & (1<<sprite_number)) ? ON: OFF;
}

