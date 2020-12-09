#ifndef ON
	#define ON 1
#endif

#ifndef OFF
	#define OFF 0
#endif


#ifndef BLACK
	#define BLACK	0	
#endif

#ifndef WHITE
	#define WHITE	1	
#endif

#ifndef RED
	#define RED		2
#endif

#ifndef CYAN
	#define CYAN	3	
#endif

#ifndef VIOLET
	#define VIOLET  4
#endif

#ifndef GREEN
	#define GREEN	5	
#endif

#ifndef BLUE
	#define BLUE	6	
#endif

#ifndef YELLOW
	#define YELLOW	7	
#endif

#ifndef ORANGE
	#define ORANGE	8	
#endif

#ifndef BROWN
	#define BROWN	9	
#endif

#ifndef LIGHTRED
	#define LIGHTRED 10
#endif

#ifndef DARKGREY
	#define DARKGREY 11
#endif

#ifndef GREY
	#define GREY 	12
#endif

#ifndef LIGHTGREEN
	#define LIGHTGREEN 13
#endif

#ifndef LIGHTBLUE
	#define LIGHTBLUE 14
#endif

#ifndef LIGHTGREY
	#define LIGHTGREY 15
#endif

#ifndef _DECOMPRESS
	#define _DECOMPRESS
	void expand(char data[],unsigned address,unsigned length)
	{
		register unsigned i;
		for(i = 0; i < length; i++)	POKE(address+i,data[i]);
	}
	

#endif