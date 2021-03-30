// header for functions

#include <stdint.h>



//functions from display.c

void display_init(void);
void delay(int);
void display_image(int, const uint8_t*);
void display_string(int, char*);
void game_intro();
int getbtns(void);
void animation(void);
void drawMoon (int, int, int, int);

// functions from gameFunctions.c

void drawPixel(int, int, int, int);
void drawBlock(int, int, int, int);
void render_background(void);
void render_background1(void);
void move_block (void);
void gameRunning(void);

void display_update(void);
void nextlvl (void);
void check_allignment(void);
void printlife(void);
void player_score(void);
void displayDigit(int, int, int);
void gameover(void);
void displayString(int, int, char*);
void scorelist(void);
void printstacker(void);
void game_lost();
char * itoaconv( int);
 
extern int lvl;
extern int k;
extern int score;
extern uint8_t blockx;
extern short blocky;
extern uint8_t blockb;
extern uint8_t blockh;
extern uint8_t counter;
extern uint8_t j;
extern uint8_t GameState;
extern float Speed;
extern uint8_t C,D;
extern short comparator;
extern float hcp;
extern uint8_t lifeCounter;
extern uint8_t gameArray [512];
extern uint8_t stacker[24];
extern int HIGH1;
extern int HIGH2;
extern int valid1;