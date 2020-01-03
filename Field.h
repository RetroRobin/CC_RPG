#pragma once
//Contains functions for building the explorable map
#include <string>
using namespace std;

enum tileType {FAIL, EMP, VINE, SAVE, TREASURE, WATER, TEXT};

class Occupant
{
public:
	int direction; //0 = North, 1 = South, 2 = East, 3 = West
	int location; //Tile number in the Map array
	int type; //0 = NONEXIST, 1 = player, 2 = Hlog, 3 = Vlog, 4 = enemy, 5 = water, 6 = Event, 7 = Transition
	int extra = -1;
public:
	Occupant();
	Occupant(int, int, int);
};

class Tile
{
public:
	Tile * adjacent[4]{ NULL, NULL, NULL, NULL }; //0 = North, 1 = South, 2 = East, 3 = West
	tileType type;
	bool occupied = false;
	Occupant tenant;
	int location; //Tile number in Map array, for debugging
	int tierV; //From top to bottom: 0, 1, 2, 3(CENTER), 4, 5, 6
	int tierH; //From left to right: 0, 1, 2, 3, 4(CENTER), 5, 6, 7, 8
	int extra; //Determines items in chests or what a vine does
	int editNum = -1; //For map updating. -1 means the tile is uneditable
public:
	Tile();
	Tile(int, int, int); //Type of tile, extra content, location of tile
	int sight(int);
	string printOut(int);
};


Tile *loadMap(int, bool, int, int[], int[]);
Tile constructMap(string, Tile[], int);
string mapGeneration(int);
void minimap(Tile[]); //For debug
void drawTiles(Tile[]);
void mapDraw(Tile);
string mapUpdate(string, int[], int[]);

/*
	TILE CODE FOR MAP STRINGS
	0 (48) = NULL SPACE 
	1 (49) = EMPTY 
	2 (50) = PLAYER START
	3 (51) = ITEM
	4 (52) = SWITCH
	5 (53) = SAVE
	6 (54) = ENEMY
	7 (55) = HORIZONTALLY ALIGNED LOG
	8 (56) = VERTICALLY ALIGNED LOG
	9 (57) = WATER
	: (58) = CUTSCENE TRIGGER
	; (59) = MAP TRANSITION
	< (60) = TEXTBOX

	Other tiles, perhaps
	Party Member tile
	Boss tile


	DIRECTIONS FOR MAP TRANSITIONS
	, = NORTH
	- = SOUTH
	. = EAST
	/ = WEST
*/