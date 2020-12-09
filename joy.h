#define _JOY_UP		0b00000001
#define _JOY_DOWN 	0b00000010
#define _JOY_LEFT 	0b00000100
#define _JOY_RIGHT 	0b00001000
#define _JOY_FIRE 	0b00010000

char joystick()
{
	return PEEK(0xdc00);
}