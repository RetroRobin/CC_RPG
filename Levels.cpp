#include "stdafx.h"
#include "Field.h"
#include "Structs.h"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

/*This file contains all the information for creating levels on a macro stage, and storing specific
  level layouts.
  NOTES FOR LAYOUT BONUSES:
  3 (item) - Item number [EXTRA], chest number [editNum]
  4 (switch) - Effect type [EXTRA]
  6 (enemy) - Enemy spawn type [EXTRA]
  : (cutscene) - Cutscene number [EXTRA], trigger reference [editNum]
  ; (map transition) - Room to load [EXTRA], entrance number [editNum], direction [ , - . / ]
  < (Textbox) - Text number     */



Room::Room()
{
	baseCode = "00000000000000000000000000000000000111111100000000000000000011111110000000000000000001112111000000000";
	baseCode = baseCode + "000000000111111100000000000000000011111110000000000000000000000000000000000"; 
	width = 25;
	height = 20;
	/*   25 x 20
	-------------------------
	---------       ---------
	---------       ---------
	---------   2   ---------
	---------       ---------
	---------       ---------
	-------------------------
	*/
	editCode = baseCode;
}

Room::Room(int num)
{
	switch (num)
	{
	default: //ERROR room, 5x5 square
		baseCode = "00000000000000000000000000000000000111111100000000000000000011111110000000000000000001112111000000000";
		baseCode = baseCode + "000000000111111100000000000000000011111110000000000000000000000000000000000";
		width = 25;
		height = 20;
		break;
	case 0: //Test room 1
	{
		baseCode = "00000000000000000000000000001111110000000111111110001111111000000011111601100;10/11111111111111111111110";
		baseCode = baseCode + "00111111100010001111162110000111111000100011111111000000000000010000000000000000000000001000000000000";
		baseCode = baseCode + "0000001140111111130011000000000000111811211711100000000000011511111119110000000000000000000000000000000";
		width = 25;
		height = 20;
		treasures[0] = 0;
		entrances[0] = 79;
		break;
		/*
		-------------------------			ITEMS: Band-aid (0)
		---      -------        -			SWITCHES: (0) INOPERABLE CURRENTLY
		--       -------     6  -			ENEMY MOBS: ( ) (2)
		-;                      -
		--       --- ---     6  -
		---      --- ---        -
		------------ ------------
		------------ ------------
		------  4       3  ------
		------   8  2  7   ------
		------  5       9  ------
		-------------------------
		*/
	}
	case 1: //Celephais streets 1
	{
		baseCode = "00000000011100001110000111000;20/1110000111000011100001110000111000011100001000000110000011100";
		baseCode = baseCode + "0001100001110000111000011100001110000111000012100001110000111000011100001110000111000013401000000000";
		width = 7;
		height = 50;
		treasures[0] = 0;
		break;
		/*
		-------		   ^
		--   --		--   --    TREASURES
		--   --		--   --      -Smelling Salts
		--   --		--   --
		-;   --		--   --
		--   --		--   --
		--   --		-- 2 --
		--   --		--   --
		--   --		--   --
		--   --		--   --
		-- ----		--   --
		--  ---		--   --
		--   --		-- 3 --
		---  --		-------
		   v
		*/
	}
	//case ?:
	case 99: //Transition test room
	{
		baseCode = "000000000000000000000001111000000000001111111100000000111011011100000011111511111111;00.00011101101110000";
		baseCode = baseCode + "000011111111000000000001111000000000000000000000000";
		height = 10;
		width = 17;
		entrances[0] = 83;
		//CREATE ROOM FOR TRANSITION TEST
		/*	-----------------
			------    -------
			----        -----
			---   -  -   ----
			--     S        >
			---   -  -   ----
			----        -----
			------    -------
			-----------------*/
	}
	}
	editCode = baseCode;
}

void Room::baseEdit(int location, char replace)
{
	this->baseCode[location] = replace;
}

Level::Level()
{
	name = "LOST";
	roomNums[0] = -1;
}

Level::Level(int num)
{
	switch (num)
	{
	default:
	{
		name = "TEST";
		roomNums[0] = 0; roomNums[1] = 99;
		roomChange = "It looks like you are testing scene transitions.";
		boxOpen = "A box with goodies is here.\nWill you open it?";
		break;
	}
	case 0: //Intro city
	{
		name = "CITY";
		for (int i = 0; i < 3; i++)
		{
			roomNums[i] = i + 1; //Rooms 1-3
		}
		//No enemy spawns here, but better put in a placeholder in case
		roomChange = "The darkened roads lead deeper into the city.";
		boxOpen = "Something lies discarded on the ground.\nWill you pick it up?";
		break;
	}
	case 1: //Hollow Forest
	{
		name = "FOREST";
		//Make a For loop to set the room numbers
		//Ditto for the enemy spawns
		BOSS = 4; //Enemy group of boss
		roomChange = "The forest path continues into the darkness.";
		boxOpen = "You see something inside the bushes.\nWill you reach for it?";
		break;
	}
	case 2: //Old Suburbia

	case 3: //Madman's hideout

	case 4: //Hearst High
	{

	}
	}

}