#include <pic32mx.h>
#include <stdint.h>
#include "gameHeader.h"
#include "displayData.h"


#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9


#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200



int X = 99;
int Y = -1;
int raknare = 0;
int konstant = 0;


// Kod ur kurs IS1200 template; hello-display-master bl.a

// get input from buttons 
int getbtns(void) {
    return PORTD >> 5 & 0x7;
}


void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}




uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}


// initiate display

void display_init() {
	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
	delay(10);
	DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK;
	delay(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK;
	delay(10);
	DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;
	delay(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK;
	delay(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}



void display_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
		
		for(j = 0; j < 128; j++)
			spi_send_recv(~data[i*128 + j]);
	}
}

void display_string(int line, char *s) {
    int i;
    if(line < 0 || line >= 4)
        return;
    if(!s)
        return;

    for(i = 0; i < 16; i++)
        if(s) {
            textbuffer[line][i] = *s;
            s++;
        } else
            textbuffer[line][i] = ' ';
}


void display_update() {
    int i, j, k;
    int c;
    for(i = 0; i < 4; i++) {
        DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
        spi_send_recv(0x22);
        spi_send_recv(i);

        spi_send_recv(0x0);
        spi_send_recv(0x10);

        DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;

        for(j = 0; j < 16; j++) {
            c = textbuffer[i][j];
            if(c & 0x80)
                continue;

            for(k = 0; k < 8; k++)
                spi_send_recv(font[c*8 + k]);
        }
    }
}



// Egen kod
void drawMoon (const int x, const int y, const int konstant, const int i) {

    if ( x >= 100 && x < 120){
        if (y >= 0 && y < 32 ){

            if( (konstant >= 0 && konstant <5) || (konstant >= 64 && konstant < 69)){
                if(i == 0 || i == 8){
                    uint8_t bit = 0x1 << (y - (y/8 * 8));
                    gameArray[x + (y/8) * 128] &= ~bit;
                }
            }

            if( (konstant >= 10 && konstant < 15) || (konstant >= 58 && konstant < 63)){
                if(i == 1 || i == 7){
                    uint8_t bit = 0x1 << (y - (y/8 * 8));
                    gameArray[x + (y/8) * 128] &= ~bit;
                }
            }

            if ((konstant >= 19 && konstant < 24) || (konstant >= 51 && konstant < 56)){
                if(i == 2 || i == 6){
                    uint8_t bit = 0x1 << (y - (y/8 * 8));
                    gameArray[x + (y/8) * 128] &= ~bit;
                }
            }

            if((konstant >= 28 && konstant < 32) || (konstant >= 36 && konstant < 40) || (konstant >= 44 && konstant < 48) ){
                if(i >= 3 && i <=5){
                    uint8_t bit = 0x1 << (y - (y/8 * 8));
                    gameArray[x + (y/8) * 128] &= ~bit;
                }
            }
        }
    }
}

void animation(){

    if(raknare < 13 || raknare >= 24){
        X++;
        Y++;
    }

    if(raknare >=13 && raknare < 24){
        X--;
        Y++;
    }

    int i,j;
    int nyY = Y;
    int nyX = X;


    for (i = 0; i < 9; i++){
        for (j = 0; j < 8; j++){
            drawMoon(X, Y, konstant, i);
            Y--;
            konstant++;
        }
        Y = nyY;
        X++;
    }

    raknare++;
    konstant = 0;
    X = nyX;

    if (raknare ==  38){
        raknare = 0;
        X = 99;
        Y = -1;
    }
}


//kod ur kurs IS1200 från labb 3
#define ITOA_BUFSIZ 1
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";
  
  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
}

void game_intro(){


    display_string(0,"      STACK!");
    display_string(1,"    PRESS BTN:");
    display_string(2," 2. NEW GAME");
    display_string(3," 3. HIGH SCORE");
   	display_update();	

    int btn = getbtns();
    if ((btn & 1)){
        GameState = 1;
        lvl = 1;
  
    }
    
     if ((btn & 2)){
        GameState = 2;
        
    }

}


void high_score() {

	
	display_string(0, "FIRST:              ");
	display_string(1, itoaconv(HIGH1));
	display_string(2, "SECOND:             ");
	display_string(3, itoaconv(HIGH2));
	display_update();
	delay(10000000);
	GameState = 0;
}
