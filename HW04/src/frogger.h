#include <stdlib.h>
#include "gbaLib.h"
#include "text.h"

//Status Bar
#define STATUSCOLOR DARKERGREENINDEX
#define STATUSWIDTH 240
#define STATUSHEIGHT 16

// Median, Road, and River Constants
#define MEDIAN1START 80
#define MEDIAN2START 144
#define MEDIANHEIGHT 16
#define MEDIANWIDTH 240
#define MEDIANCOLOR GRAYINDEX

#define RIVERSTART 16
#define RIVERHEIGHT 64
#define RIVERWIDTH 240
#define RIVERCOLOR BLUEINDEX

#define ROADSTART 96
#define ROADHEIGHT 48
#define ROADWIDTH 240
#define ROADCOLOR BLACKINDEX

#define NUMCARS 9
#define NUMLOGS 10
#define NUMPADS 4
#define LOGCOLOR BROWNINDEX

#define OBJECTSPEED 1

//FROG Constants
#define FROGSTARTROW 147
#define FROGSTARTCOL 115
#define FROGSIZE 10
#define FROGJUMP 16
#define FROGCOLOR GREENINDEX
#define ALIVE 1
#define DEAD 0

//CAR Constants
#define CARSTARTROW 98
#define CARSTARTCOL 20
#define CARHEIGHT 12
#define CARWIDTH 30
#define CARGAP 80
#define LANEGAP 16

//LOG Constants
#define LOGSTARTROW 34
#define LOGSTARTCOL 20
#define LOGHEIGHT 12
#define LOGWIDTH 30
#define LOGGAP1 77
#define LOGGAP2 60
#define LOGGAP3 80

//Palette Colors
u16 colors[] = {BLACK, WHITE, RED, GREEN, BLUE, MAGENTA, CYAN, YELLOW, LTGRAY,
				DARKGREEN, BROWN, GRAY, DARKERGREEN};

enum {BLACKINDEX, WHITEINDEX, REDINDEX, GREENINDEX, BLUEINDEX,
       MAGENTAINDEX, CYANINDEX, YELLOWINDEX, LTGRAYINDEX,
	   DARKGREENINDEX, BROWNINDEX, GRAYINDEX, DARKERGREENINDEX};

//Game States
typedef enum { TITLE, PLAYING, WIN, LOSE} STATE;


//Object Structures
typedef struct
{
	int row;
	int col;
	int oldrow;
	int oldcol;
	int oldoldrow;
	int oldoldcol;
	int width;
	int height;
	int speed;
	int cindex;
	int lane;
}CAR;

typedef struct
{
	int row;
	int col;
	int oldrow;
	int oldcol;
	int oldoldrow;
	int oldoldcol;
	int width;
	int height;
	int speed;
	int lane;
}LOG;

typedef struct
{
	int occupied;
}PAD;

typedef struct
{
	int row;
	int col;
	int oldrow;
	int oldcol;
	int oldoldrow;
	int oldoldcol;
	int size;
	int speed;
	int jump;
	int cindex;
	int lives;
	int status;
	int up;
	int left;
	int down;
	int right;
	int carCollide;
	int waterCollide;
	int logCollide;
	int padCount;
	int padCollide;
}FROG;

CAR cars[NUMCARS];
LOG logs[NUMLOGS];
PAD pads[NUMPADS];

FROG froggy[1];

STATE gameState;

