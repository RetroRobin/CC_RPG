#pragma once
//Contains functions for building the explorable map
#include <string>
using namespace std;

enum tileType {FAIL, EMP, VINE, SAVE, TREASURE, WATER, TEXT};

class Room
{
public:
	string baseCode;
	string editCode;
	int width;
	int height;
	int entrances[10]{ 0 }; //Stores which room to send you to
	int treasures[5]{ -1 }; //Store positions in the level's treasure array here. Check when creating tile.
public:
	Room();
	Room(int);
	void baseEdit(int, char);
};

class Level
{
public:
	string name;
	int roomNums[20]; //Stores the room spawns
	Room currRoom;
	bool cutsceneTrigger[20]{ false }; //For seeing if cutscenes have been triggered
	int enemySpawn[10];
	int BOSS;
	bool tweasure[15]{ false }; //For seeing if treasures are collected
	string roomChange;
	string boxOpen;
	//Graphics int?
public:
	Level();
	Level(int);
};

class Occupant
{
public:
	int direction; //0 = North, 1 = South, 2 = East, 3 = West
	int location; //Tile number in the Map array
	int type; //0 = NONEXIST, 1 = player, 2 = Hlog, 3 = Vlog, 4 = enemy, 5 = water, 6 = Event, 7 = Transition
	int extra = -1;
	int arrRef = -1;
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


Tile *loadMap(int, bool, int, Level &);
Tile constructMap(Room, Tile[], int);
void minimap(Tile[]); //For debug
void drawTiles(Tile[], string);
void mapDraw(Tile, string);
string mapUpdate(string, int[], int[]);

/*
	TILE CODE FOR MAP STRINGS
	0 (48) = NULL SPACE 
	1 (49) = EMPTY						0
	2 (50) = PLAYER START				1
	3 (51) = ITEM						2
	4 (52) = SWITCH						3
	5 (53) = SAVE						4
	6 (54) = ENEMY						5
	7 (55) = HORIZONTALLY ALIGNED LOG	6
	8 (56) = VERTICALLY ALIGNED LOG		7
	9 (57) = WATER						8
	: (58) = CUTSCENE TRIGGER			9
	; (59) = MAP TRANSITION				10
	< (60) = TEXTBOX					11

	Other tiles, perhaps
	Party Member tile
	Boss tile


	DIRECTIONS FOR MAP TRANSITIONS
	, = NORTH
	- = SOUTH
	. = EAST
	/ = WEST
*/