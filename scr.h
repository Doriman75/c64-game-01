#include "const.h"
#define SCR_SCREEN_MEMORY 0x0400
#define SCR_COLOR_MEMORY 0xD800
#define SCR_BACKGROUND_REGISTER 0xD021
#define SCR_COLOR01_REGISTER 0xD022
#define SCR_COLOR10_REGISTER 0xD023
#define SCR_BORDER_REGISTER 0xD020
#define SCR_ROM_REGISTER 0xDC0E
#define SCR_MULTICOLOR_REGISTER 0xD016
#define SCR_CHARSET_REGISTER 0xD018
#define SCR_CHAR_ROM_MEMORY 0xd000
#define SCR_CHAR_RAM_MEMORY 0x3000

void scr_clear()
{
	asm ("jsr $E544");
}

void scr_load(char* screen, char* color, char* cs)
{
	POKE(SCR_CHARSET_REGISTER,PEEK(SCR_CHARSET_REGISTER) & 240 | 12); // CHAR SET RAM AT $3000
	POKE (SCR_ROM_REGISTER, PEEK(SCR_ROM_REGISTER) & 254);
	POKE (1, PEEK(1) & 251);
	expand(cs, SCR_CHAR_RAM_MEMORY, 2048);
	POKE (1, PEEK(1) | 4);
	POKE (SCR_ROM_REGISTER, PEEK(SCR_ROM_REGISTER) | 1);	
	expand(color,SCR_COLOR_MEMORY,1000);
	expand(screen,SCR_SCREEN_MEMORY,1000);
}

void scr_multicolor(char mode, char color01, char color10)
{
	char v = PEEK(SCR_MULTICOLOR_REGISTER);
	v = mode == ON ? v|=16: v &= 239;
	POKE(SCR_MULTICOLOR_REGISTER,v); 
	POKE(SCR_COLOR01_REGISTER,color01);
	POKE(SCR_COLOR10_REGISTER,color10);
}

void scr_color(char x, char y, char color)
{
	POKE(SCR_COLOR_MEMORY+x+y*40,color);	
}

void scr_background(char color)
{
	POKE(SCR_BACKGROUND_REGISTER,color);
}

void scr_border(char color)
{
	POKE(SCR_BORDER_REGISTER,color);
}

void scr_print(char x, char y, char* s, char color)
{
	char i;
	for(i=0; s[i] !=0; i++)
	{
		POKE(SCR_SCREEN_MEMORY+x+y*40+i,s[i]);
		POKE(SCR_COLOR_MEMORY+x+y*40+i,color);
	}
}