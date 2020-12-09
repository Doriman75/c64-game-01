	void screen_clear()
	{
		asm("	lda #0");
        asm("	sta $d020");
        asm("	sta $d021");

 	    asm("	lda #2");
		asm("	sta 56576");
		asm("	lda #120");
		asm("	sta 53248+24");

		asm("	lda 53248+17");
		asm("	ora #32");
		asm("	sta 53248+17");

	//LORES
		asm("	lda 53270");
		asm("	ora #16");
		asm("	sta 53270");
	
		asm("	ldx #0");
		asm("SCREEN_LOOP:");
		asm("	lda #$10");
		asm("	sta 23552,x");
		asm("	sta 23552+250,x");
		asm("	sta 23552+500,x");
		asm("	sta 23552+750,x");
		asm("	lda #0");
		asm("	sta 24576,x");
		asm("	sta 24576+250,x");
		asm("	sta 24576+500,x");
		asm("	sta 24576+750,x");
		asm("	sta 24576+1000,x");
		asm("	sta 24576+1250,x");
		asm("	sta 24576+1500,x");
		asm("	sta 24576+1750,x");
		asm("	sta 24576+2000,x");
		asm("	sta 24576+2250,x");
		asm("	sta 24576+2500,x");
		asm("	sta 24576+2750,x");
		asm("	sta 24576+3000,x");
		asm("	sta 24576+3250,x");
		asm("	sta 24576+3500,x");
		asm("	sta 24576+3750,x");
		asm("	sta 24576+4000,x");
		asm("	sta 24576+4250,x");
		asm("	sta 24576+4500,x");
		asm("	sta 24576+4750,x");
		asm("	sta 24576+5000,x");
		asm("	sta 24576+5250,x");
		asm("	sta 24576+5500,x");
		asm("	sta 24576+5750,x");
		asm("	sta 24576+6000,x");
		asm("	sta 24576+6250,x");
		asm("	sta 24576+6500,x");
		asm("	sta 24576+6750,x");
		asm("	sta 24576+7000,x");
		asm("	sta 24576+7250,x");
		asm("	sta 24576+7500,x");
		asm("	sta 24576+7750,x");
		asm("	inx ");
		asm("	cpx #250");
		asm("	bne SCREEN_LOOP");
	}
	
	void screen_plot(unsigned xc,unsigned yc, char on)
	{
		unsigned ra, ba, ad;
		register char i,ma,l;

		ra = yc & 0xf8;
		ra = (ra<<5)+(ra<<3) + (yc & 7);
		ad = 24576 + ra + (xc & 0xfff8);		
		ma = 1;				
		l = 7-(xc & 7);		
		for(i=0;i<l;i++) ma<<= 1;
		if(on==1) POKE(ad,PEEK(ad)| ma); else POKE(ad,PEEK(ad) & (255-ma));
		
	}
	
	
	void screen_print(char x, char y, char* s)
	{
		char i,j;
		unsigned c,offset;
		POKE(56334, PEEK(56334) &254);
		POKE(1, PEEK(1) & 251);
		offset=(40*y+x)<<3;
		for(j=0; s[j] != 0;j++)
		{
			c=s[j]<<3;
			for(i=0;i < 8; i++) POKE(24576+i+(j<<3)+offset,PEEK(55295+i+c));			
		}
		POKE(1, PEEK(1) | 4);
		POKE(56334, PEEK(56334) | 1);
	}
	
	void screen_color(char x, char y, char c)
	{
		POKE(23552+x+y*40, c);
	}
	
	void decompress(char data[], unsigned data_length, unsigned address)
	{
		unsigned i,j,offset;
		offset = 0;
		
		for(i = 0; i < data_length; i+=2)
			for(j = 0;j < data[i+1];j++) 
			{
				POKE(address+offset,data[i]);
				offset++;
			}
	}

	void screen_load_compressed_image(char bitmap_data[], unsigned bitmap_data_length, char screen_ram_data[], unsigned screen_ram_data_length,char screen_color_data[], unsigned screen_color_data_length )
	{
		decompress(bitmap_data, bitmap_data_length, 24576);
		decompress(screen_ram_data, screen_ram_data_length, 23552);
		decompress(screen_color_data, screen_color_data_length, 0xd800);
	}
