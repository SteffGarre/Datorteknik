#include <stdint.h>
#include "gameHeader.h"




uint8_t blockx = 0;
short blocky = 32;
uint8_t blockb = 6;
uint8_t blockh = 20;

short comparator;
float Speed;
uint8_t C,D,c;
float hcp = 1.0;
uint8_t counter = 0;
uint8_t lifeCounter = 3;

uint8_t valid = 0;
uint8_t gameArray [512];
int score = 0;
int lvl = 1;
int k = 1;

int HIGH1 = 0;
int HIGH2 = 0;
int valid1 = 0;





void drawPixel(const int x, const int y, const int dontPrint, const int i) {

    if (( x >= 0 && x < 128) && (y >= 0 && y < 32)) {
        

            if ( (i > 0) && (i < 5) && ((dontPrint % 5) == 0)){
                
            	// delvis inspirerad av projekt Pong skriven av Vidar Söderqvist
                uint8_t bit = 0x1 << (y - (y/8 * 8));
                gameArray[x + (y/8) * 128] &= ~bit;
            }

            else if ( (i == 0) || (i == 5)) {
                int8_t bit = 0x1 << (y - (y/8 * 8));
                gameArray[x + (y/8) * 128] &= ~bit;
            }

        }
    
}


void drawBlock(int x, int y, int b, int h){

    int i,j;

    int yj = y;
    int dontPrint = 0;

    for (i = 0; i < b; i++){
        for (j = 0; j <= h; j++){
            drawPixel(x, y, dontPrint, i);
            y++;
            dontPrint++;

            switch (lifeCounter) {
                case 3:
                    if(dontPrint == 21 && blockx < 31)
                         dontPrint = 0;
                    if(dontPrint == 16 && blockx >= 31 && blockx < 67)
                        dontPrint = 0;
                    if(dontPrint == 11 && blockx >= 67 && blockx < 100 )
                        dontPrint = 0;
                break;

                case 2:
                    if(dontPrint == 16 && blockx < 67)
                         dontPrint = 0;
                    if(dontPrint == 11 && blockx >= 67 && blockx < 100)
                        dontPrint = 0;
                break;

                case 1:
                    if(dontPrint == 11 && blockx < 100)
                    dontPrint = 0;
                break;
        }
    }
        y = yj;
        x++;
    }
}



void gameRunning () {
	
	int btn = getbtns();
	if (blocky >= 0 && blocky <= (31 - blockh)) {
		if (btn == 4 ){

				check_allignment();
				delay(1000000);
				player_score();
				blockx += 6;
				blocky = 32;
				counter = 0;
				render_background (); 
		}
	}
        move_block();
       
}

void player_score() {
	switch(blockh) {

		case 20:
		score += 1*k;
		break;

		case 15:
		score += 2*k;
		break;

		case 10:
		score += 3*k;
		break;
	}
}

void move_block(){

	if (lifeCounter == 3) {
		
		if (blockx < 31) {
		C = 52;
		D = 106; 
		Speed = 230000*hcp; }

		if (blockx >= 31 && blockx < 67) {
		C = 47;
		D = 96;
		blockh = 15;
		Speed = 200000*hcp; }
 
	
		if (blockx >= 67 && blockx < 100) {
		C = 41;
		D = 84;
		blockh = 10;
		Speed = 170000*hcp; }
	}

	if (lifeCounter == 2) {
		

		if (blockx < 67) {
		C = 47;
		D = 96;
		blockh = 15;
		Speed = 200000*hcp; }
 
	
		if (blockx >= 67 && blockx < 100) {
		C = 41;
		D = 84;
		blockh = 10;
		Speed = 170000*hcp; }
	}

	if (lifeCounter == 1) {
 
	
		if (blockx < 100) {
		C = 41;
		D = 84;
		blockh = 10;
		Speed = 170000*hcp; }
	}



	if (lifeCounter == 0){
		GameState = 3;
	}

	if (lifeCounter > 0) {
    
    if (counter <= C){
        render_background();
        drawBlock(blockx, blocky, blockb, blockh);
        display_image (0, gameArray);
        delay(Speed);
        blocky--;

    }

    if (counter > C){
        render_background();
        drawBlock(blockx, blocky, blockb, blockh);
        display_image (0, gameArray);
        delay(Speed);
        blocky++;
    }
    }

    counter++;
    if(counter == D){
     	counter = 0;
        }
    if (blockx > 100 && lifeCounter > 0)
		nextlvl();
}

void check_allignment() {

	if (!valid){
		valid = 1;
		comparator = blocky;
		c = blocky +1;

	}


	if (blocky == (comparator -1))
		blocky += 1;

	if (blocky == (comparator +1))
		blocky -= 1;

	if (comparator < 0 || comparator > (31 - blockh) || blocky != comparator) {
		lifeCounter--;

		delay(100000);
		render_background();
		switch(lifeCounter) {

		case 2:
		drawBlock(blockx, c, blockb, 15);
		break;

		case 1:
		drawBlock(blockx, c , blockb, 10); 
		break; }
	}
	else {
		render_background();
		drawBlock(blockx, c, blockb, blockh);
	
	}
	

}

void printlife() {
	
	int i;
	
	switch(lifeCounter) {

		case 3: 
		for (i = 120; i < 128; i++) {
		gameArray[i] = 182; }
		break;
	

		case 2: 
		for (i = 120; i < 128; i++) {
		gameArray[i] = 246; }
		break;
	

		case 1: 
		for (i = 120; i < 128; i++) {
		gameArray[i] = 254; }
		break;

		default:
		for (i = 120; i < 128; i++) {
		gameArray[i] = 182; }
		break;
	}
	

}


void printstacker() {

int i,o,p;
int s = 0;

for(i = 248; i < 256; i++) {
	gameArray[i] = stacker[s];
	s++; }



for(o = 376; o < 384 ; o++) {
	gameArray[o] = stacker[s];
	s++; }


for(p = 504; p < 512 ; p++) {
	gameArray[p] = stacker[s];
	s++; }

}




void nextlvl () {

	
   	lvl = lvl + 1;
	lifeCounter = 3;
	counter = 0;
	blockx = 0;
	blockh = 20;
	hcp = hcp - 0.1;
	k += 1;
	delay(1000);
	render_background1();
	display_image (0, gameArray);
	display_string(0, "            ");
	display_string(1, "LEVEL:         ");
	display_string(2, "            ");
	display_string(3, itoaconv(lvl));
	display_string(4, "            ");
	display_update();
    delay(20000000);



}


void render_background() 
{
	int i = blockx;

	while (i < 128) {
		gameArray[i] = 255;
		i++;
	} 
	i += blockx;
	while (i < 128*2) {
		gameArray[i] = 255;
		i++;
	} 
	i += blockx;
	while (i < 128*3) {
		gameArray[i] = 255;
		i++;
	} 
	i += blockx;
	while (i < 128*4) {
		gameArray[i] = 255;
		i++;
	}
	animation(); 
	
	if (GameState != 3) {
		printlife();
	}
	
	printstacker();

}

//Clearar display vid game_lost
void render_background1()
{
	
	int i = 0;

	for(i = 0; i < 512; i++){ 
		gameArray[i] = 255; }

}



void game_lost(){
	
	lifeCounter = 3;
	valid = 0;
	counter = 0;
	blockx = 0;
	blockh = 20;
	blocky = 32;
	blockb = 6;
	render_background1();
	display_image (0, gameArray);
	delay(1000000);
	display_string(0, "YOUR SCORE:    ");
	display_string(1, "            ");
	display_string(2, itoaconv(score));
	display_string(3, "            ");

	display_update();	
	scorelist();
    delay(25000000);

    score = 0;
    lvl = 0;
    GameState = 0;
    

 	
}

void scorelist() {

	valid1 = 1;
	

	if (score > HIGH1 && valid1 == 1) {
		HIGH2 = HIGH1;
		HIGH1 = score; 
		valid1 = 0;

	}

	if (score > HIGH2 && valid1 == 1) {
		HIGH2 = score;
		valid1 = 0;

	}
}
