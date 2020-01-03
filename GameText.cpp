#include "stdafx.h"
#include "GameState.h"
#include <iostream>
using namespace std;

//This document contains ASCII animation print-outs

//The default window size is 30 lines long

void startupAnim() //38 frames
{
	float animTime = (.05);
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 1 (empty)
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                         |\n"
		<< "    |\n                                         |\n    |\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 2
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                        | \n"
		<< "     |\n                                        | \n    _|\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 3
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                       | .\n"
		<< "      |\n                                       |  \n    __|\n\n\n \n \n \n"
		<< "    \\\n \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 4
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                      | . \n"
		<< "       |\n                                      |  \\\n    ___|\n\n\n \n \n"
		<< "                                         |\n"
		<< "     \\\n                                         |\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 5
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                     | . |\n"
		<< "    |   |\n                                     |  \\ \n    |___|\n\n\n"
		<< "                                         _\n \n                                        |_\n"
		<< "      \\\n                                        | \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 6
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                    | . | \n"
		<< "     |   |\n                                    |  \\  \n     |___|\n\n\n"
		<< "                                        __\n \n                                       |__\n"
		<< "    |  \\\n                                       |  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 7
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                   | . |  \n"
		<< "      |   |\n                                   |  \\   \n      |___|\n\n\n"
		<< "                                       ___\n \n                                      |__/\n"
		<< "     |  \\\n                                      |   \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 8
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                  | . |   \n"
		<< "    \\  |   |\n                                  |  \\   |\n       |___|\n\n\n"
		<< "                                      ___ \n \n                                     |__/ \n"
		<< "      |  \\\n                                     |   \\\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 9
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                 | . |   _\n"
		<< "     \\  |   |\n                                 |  \\   | \n        |___|\n\n\n"
		<< "                                     ___  \n    o\n                                    |__/  \n"
		<< "    |  |  \\\n                                    |   \\ \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 10
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                                | . |   __\n"
		<< "      \\  |   |\n                                |  \\   |  \n         |___|\n\n\n"
		<< "                                    ___   \n     o\n                                   |__/   \n"
		<< "     |  |  \\\n                                   |   \\  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 11
	cout << "\n\n\n\n\n\n\n\n\n\n\n \n                               | . |   ___\n"
		<< "    |  \\  |   |\n                               |  \\   |   \n    |     |___|\n\n\n"
		<< "                                   ___    \n      o\n                                  |__/   |\n"
		<< "      |  |  \\\n                                  |   \\  |\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 12
	cout << "\n\n\n\n\n\n\n\n\n\n\n  \n                              | . |   ___ \n"
		<< "    ~|  \\  |   |\n                              |  \\   |    \n     |     |___|\n\n\n"
		<< "                                  ___     \n       o\n                                 |__/   | \n"
		<< "    |  |  |  \\\n                                 |   \\  |_\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 13
	cout << "\n\n\n\n\n\n\n\n\n\n\n  \n                             | . |   ___  \n"
		<< "     ~|  \\  |   |\n                             |  \\   |     \n      |     |___|\n\n\n"
		<< "                                 ___      \n        o\n                                |__/   |  \n"
		<< "     |  |  |  \\\n                                |   \\  |__\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 14
	cout << "\n\n\n\n\n\n\n\n\n\n\n   \n                            | . |   ___   \n"
		<< "      ~|  \\  |   |\n                            |  \\   |      \n       |     |___|\n\n\n"
		<< "                                ___       \n         o\n                               |__/   |   \n"
		<< "    . |  |  |  \\\n                               |   \\  |___\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 15
	cout << "\n\n\n\n\n\n\n\n\n\n\n   \n                           | . |   ___   \\\n"
		<< "       ~|  \\  |   |\n                           |  \\   |       \n        |     |___|\n\n\n"
		<< "                               ___        \n          o\n                              |__/   |   |\n"
		<< "     . |  |  |  \\\n                              |   \\  |___|\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 16
	cout << "\n\n\n\n\n\n\n\n\n\n\n    \n                          | . |   ___   \\_\n"
		<< "        ~|  \\  |   |\n                          |  \\   |        \n    _    |     |___|\n\n\n"
		<< "                              ___         \n    |      o\n                             |__/   |   | \n"
		<< "    | . |  |  |  \\\n                             |   \\  |___| \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 17
	cout << "\n\n\n\n\n\n\n\n\n\n\n    |\n                         | . |   ___   \\_|\n"
		<< "    |    ~|  \\  |   |\n                         |  \\   |        |\n    |_    |     |___|\n\n\n"
		<< "                             ___         -\n     |      o\n                            |__/   |   |  \n"
		<< "     | . |  |  |  \\\n                            |   \\  |___|  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 18
	cout << "\n\n\n\n\n\n\n\n\n\n\n     |\n                        | . |   ___   \\_|_\n"
		<< "     |    ~|  \\  |   |\n                        |  \\   |        | \n    _|_    |     |___|\n\n\n"
		<< "                            ___         -|\n      |      o\n                           |__/   |   |  |\n"
		<< "      | . |  |  |  \\\n                           |   \\  |___|  |\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 19
	cout << "\n\n\n\n\n\n\n\n\n\n\n      |\n                      | . |   ___   \\_|_/\n"
		<< "      |    ~|  \\  |   |\n                       |  \\   |        |  \n     _|_    |     |___|\n\n\n"
		<< "                           ___         -|\n       |      o\n                          |__/   |   |  |_\n"
		<< "    |  | . |  |  |  \\\n                          |   \\  |___|  |_\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 20
	cout << "\n\n\n\n\n\n\n\n\n\n\n       |\n                       | . |   ___   \\_|_/ \n"
		<< "       |    ~|  \\  |   |\n                      |  \\   |        |   \n      _|_    |     |___|\n\n\n"
		<< "                          ___         -|\n    _   |      o\n                         |__/   |   |  |__\n"
		<< "     |  | . |  |  |  \\\n                         |   \\  |___|  |__\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 21
	cout << "\n\n\n\n\n\n\n\n\n\n\n        |\n                       | . |   ___   \\_|_/  \n"
		<< "        |    ~|  \\  |   |\n                     |  \\   |        |    \n       _|_    |     |___|\n\n\n"
		<< "                         ___         -|\n    __   |      o\n                        |__/   |   |  |___\n"
		<< "    ' |  | . |  |  |  \\\n                        |   \\  |___|  |___\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 22
	cout << "\n\n\n\n\n\n\n\n\n\n\n         |\n                      | . |   ___   \\_|_/   \n"
		<< "    |    |    ~|  \\  |   |\n                    |  \\   |        |     \n        _|_    |     |___|\n\n\n"
		<< "                        ___         -|\n    ___   |      o\n                       |__/   |   |  |___ \n"
		<< "     ' |  | . |  |  |  \\\n                       |   \\  |___|  |___|\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 23
	cout << "\n\n\n\n\n\n\n\n\n\n\n          |\n                     | . |   ___   \\_|_/    \n"
		<< "    _|    |    ~|  \\  |   |\n                   |  \\   |        |     |\n    _    _|_    |     |___|\n\n\n"
		<< "                       ___         -|\n     ___   |      o\n                      |__/   |   |  |___  \n"
		<< "    | ' |  | . |  |  |  \\\n                      |   \\  |___|  |___| \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 24
	cout << "\n\n\n\n\n\n\n\n\n\n\n           |\n                    | . |   ___   \\_|_/    _\n"
		<< "    __|    |    ~|  \\  |   |\n                  |  \\   |        |     | \n    __    _|_    |     |___|\n\n\n"
		<< "                      ___         -|\n      ___   |      o\n                     |__/   |   |  |___   \n"
		<< "     | ' |  | . |  |  |  \\\n                     |   \\  |___|  |___|  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 25
	cout << "\n\n\n\n\n\n\n\n\n\n\n            |\n                   | . |   ___   \\_|_/    __\n"
		<< "    ___|    |    ~|  \\  |   |\n                 |  \\   |        |     |  \n    ___    _|_    |     |___|\n\n\n"
		<< "                     ___         -|\n       ___   |      o\n                    |__/   |   |  |___    \n"
		<< "      | ' |  | . |  |  |  \\\n                    |   \\  |___|  |___|  |\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 26
	cout << "\n\n\n\n\n\n\n\n\n\n\n             |\n                  | . |   ___   \\_|_/    __ \n"
		<< "    |___|    |    ~|  \\  |   |\n                |  \\   |        |     |   \n    |___    _|_    |     |___|\n\n\n"
		<< "                    ___         -|\n    |   ___   |      o\n                   |__/   |   |  |___     \n"
		<< "       | ' |  | . |  |  |  \\\n                   |   \\  |___|  |___|  | \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 27
	cout << "\n\n\n\n\n\n\n\n\n\n\n              |\n                 | . |   ___   \\_|_/    __  \n"
		<< "     |___|    |    ~|  \\  |   |\n               |  \\   |        |     |    \n     |___    _|_    |     |___|\n\n\n"
		<< "                   ___         -|\n     |   ___   |      o\n                  |__/   |   |  |___     -\n"
		<< "    \\   | ' |  | . |  |  |  \\\n                  |   \\  |___|  |___|  |  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 28
	cout << "\n\n\n\n\n\n\n\n\n\n\n               |\n                | . |   ___   \\_|_/    __   \n"
		<< "      |___|    |    ~|  \\  |   |\n              |  \\   |        |     |     \n      |___    _|_    |     |___|\n\n\n"
		<< "                  ___         -|\n    . |   ___   |      o\n                 |__/   |   |  |___     -|\n"
		<< "     \\   | ' |  | . |  |  |  \\\n                 |   \\  |___|  |___|  |  |\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 29
	cout << "\n\n\n\n\n\n\n\n\n\n\n                |\n               | . |   ___   \\_|_/    __    \n"
		<< "       |___|    |    ~|  \\  |   |\n             |  \\   |        |     |     |\n    \\  |___    _|_    |     |___|\n\n\n"
		<< "                 ___         -|\n     . |   ___   |      o\n                |__/   |   |  |___     -|_\n"
		<< "      \\   | ' |  | . |  |  |  \\\n                |   \\  |___|  |___|  |  | \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 30
	cout << "\n\n\n\n\n\n\n\n\n\n\n    _            |\n              | . |   ___   \\_|_/    __    _\n"
		<< "    /   |___|    |    ~|  \\  |   |\n            |  \\   |        |     |     | \n     \\  |___    _|_    |     |___|\n\n\n"
		<< "                ___         -|\n    | . |   ___   |      o\n               |__/   |   |  |___     -|__\n"
		<< "    |  \\   | ' |  | . |  |  |  \\\n               |   \\  |___|  |___|  |  |  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 31
	cout << "\n\n\n\n\n\n\n\n\n\n\n    __            |\n             | . |   ___   \\_|_/    __    __\n"
		<< "    _/   |___|    |    ~|  \\  |   |\n           |  \\   |        |     |     | '\n      \\  |___    _|_    |     |___|\n\n\n"
		<< "               ___         -|\n     | . |   ___   |      o\n              |__/   |   |  |___     -|__ \n"
		<< "     |  \\   | ' |  | . |  |  |  \\\n              |   \\  |___|  |___|  |  |  |\n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 32
	cout << "\n\n\n\n\n\n\n\n\n\n\n    ___            |\n            | . |   ___   \\_|_/    __    ___\n"
		<< "    __/   |___|    |    ~|  \\  |   |\n          |  \\   |        |     |     | ' \n       \\  |___    _|_    |     |___|\n\n\n"
		<< "              ___         -|\n      | . |   ___   |      o\n             |__/   |   |  |___     -|__  \n"
		<< "      |  \\   | ' |  | . |  |  |  \\\n             |   \\  |___|  |___|  |  |  | \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 33
	cout << "\n\n\n\n\n\n\n\n\n\n\n     ___            |\n           | . |   ___   \\_|_/    __    ___ \n"
		<< "    |__/   |___|    |    ~|  \\  |   |\n         |  \\   |        |     |     | ' |\n    |   \\  |___    _|_    |     |___|\n\n\n"
		<< "             ___         -|\n       | . |   ___   |      o\n            |__/   |   |  |___     -|__   \n"
		<< "       |  \\   | ' |  | . |  |  |  \\\n            |   \\  |___|  |___|  |  |  |  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 34
	cout << "\n\n\n\n\n\n\n\n\n\n\n      ___            |\n          | . |   ___   \\_|_/    __    ___  \n"
		<< "     |__/   |___|    |    ~|  \\  |   |\n        |  \\   |        |     |     | ' | \n     |   \\  |___    _|_    |     |___|\n\n\n"
		<< "            ___         -|\n        | . |   ___   |      o\n           |__/   |   |  |___     -|__    \n"
		<< "        |  \\   | ' |  | . |  |  |  \\\n           |   \\  |___|  |___|  |  |  |  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 35
	cout << "\n\n\n\n\n\n\n\n\n\n\n       ___            |\n         | . |   ___   \\_|_/    __    ___  \n"
		<< "      |__/   |___|    |    ~|  \\  |   |\n       |  \\   |        |     |     | ' | \n      |   \\  |___    _|_    |     |___|\n\n\n"
		<< "           ___         -|\n         | . |   ___   |      o\n          |__/   |   |  |___     -|__    \n"
		<< "         |  \\   | ' |  | . |  |  |  \\\n          |   \\  |___|  |___|  |  |  |  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 36
	cout << "\n\n\n\n\n\n\n\n\n\n\n        ___            |\n        | . |   ___   \\_|_/    __    ___  \n"
		<< "       |__/   |___|    |    ~|  \\  |   |\n      |  \\   |        |     |     | ' | \n       |   \\  |___    _|_    |     |___|\n\n\n"
		<< "          ___         -|\n          | . |   ___   |      o\n         |__/   |   |  |___     -|__    \n"
		<< "          |  \\   | ' |  | . |  |  |  \\\n         |   \\  |___|  |___|  |  |  |  \n\n\n\n\n\n\n\n";
	sleep(animTime); //Frame 37
	cout << "\n\n\n\n\n\n\n\n\n\n\n        ___            |\n       | . |   ___   \\_|_/    __    ___  \n"
		<< "       |__/   |___|    |    ~|  \\  |   |\n       |  \\   |        |     |     | ' | \n       |   \\  |___    _|_    |     |___|\n\n\n"
		<< "         ___         -|\n        | . |   ___   |      o\n        |__/   |   |  |___     -|__    \n"
		<< "        |  \\   | ' |  | . |  |  |  \\\n        |   \\  |___|  |___|  |  |  |  \n\n\n\n\n\n\n\n";
	sleep(2); //Frame 38 (FINAL)
}



void HTP()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n~~------------------------------------~~\n               HOW TO PLAY\n"
		<< "~~------------------------------------~~\n\n\n";
	sleep(3);
	cout << "This game demonstration runs off a simple command system. When prompted...\n"
		<< "Type in the number corresponding to what you want to do!";
	sleep(4);
	cout << "\n\n________________________________\n\n" <<
		"       1 0>  \n\n                     <('v'<) 1\n" <<
		"          2 0>\n                     <('v'<) 2\n\n" <<
		"       3 0>\n________________________________\n\n" <<
		"This is the play field. On the left are the enemies, and on the right are your characters.\n"
		<< "Next to every character is a number. Use this number when you target an enemy or a friend!\n\n"
		<< "When you're ready to continue, press ENTER.";
	cin.get();
	cin.get();
	cout << "\n1: Eric     HP: 30/30   MP: 10   ST: 50\n\n"
		<< "This is your character's stats, important information you should keep track of throughout the fight.\n";
	sleep(3);
	cout << "Let's go over what each of these stats means.\n\n";
	sleep(2);
	cout << "HP stands for Hit Points. \nThis is the amount of damage you can take before your character is defeated.\n"
		<< "But don't worry! You can use items and skills to heal your HP.\n\n";
	sleep(4);
	cout << "MP stands for Magic Points.\nDifferent skills require spending magic points in order to use them.\n"
		<< "When you run out of MP, you can't use those skills anymore, so be careful!\n\n";
	sleep(4);
	cout << "ST stands for Stamina.\nWhenever you attack, use a skill, or do any other action, you spend a bit of your stamina.\n"
		<< "When you run out of stamina, you get tired and have to skip your next turn to rest.\n"
		<< "This makes you vulnerable to enemy attacks for a short time.\n"
		<< "But when you defend or use a Reaction ability, you rest, and can recover your stamina.\n"
		<< "Right now you don't have to worry too much about stamina, as this will be a short battle!\n\n"
		<< "When you're ready to continue, press ENTER.";
	cin.get();
	cout << "\nNext, let's go over all the different commands you can use in battle!";
	sleep(2);
	cout << "\n\n1: Attack\nThis will use your basic attack against an enemy.\n"
		<< "It's pretty self-explanatory. If you're not sure what to do, just attack!\n";
	sleep(4);
	cout << "\n2: Skills\nThis will let you use one of your character's skills.\n"
		<< "If you're not sure what a skill does, check out the Skill descriptions in the Skill menu!\n";
	sleep(4);
	cout << "\n3: Reactions\nThese are abilities that allow you to delay your turn and act during another's turn.\n"
		<< "For more information, check out the Reaction descriptions in the Reactions menu!\n";
	sleep(4);
	cout << "\n4: Items\nThis allows you to use one of the items in your inventory.\n"
		<< "Each item does something different. Check out the Item descriptions in the Items menu!\n";
	sleep(4);
	cout << "\n5: SPECIAL\nEvery party member you can get in this game has a unique command that only they can use.\n"
		<< "Right now, though, those commands haven't been implemented yet, so you can't use them...\n";
	sleep(4);
	cout << "\n6: Defend\nThis command lets you defend yourself against enemy attacks!\n"
		<< "While defending, you take half as much damage and recover some of your stamina!\n";
	sleep(4);
	cout << "\nWhen you're ready to continue, press ENTER.";
	cin.get();
	cout << "\nEvery attack has a different element type, characters it can target, and way of delivering an attack!\n"
		<< "This important information is conveyed through a shorthand next to every skill.";
	sleep(4);
	cout << "\n\nHere are the different elements in the game, and their symbols!";
	sleep(3);
	cout << "\n\nSLASH  ]=>       FORCE  =O3             FIRE  \\^/\n"
		<< "ICE  [']         ELECTRICITY  }#{       WIND  ~&~\n"
		<< "SONIC  cC(       LIFE  -<3              NECROTIC  X_X       ELDRICH  (@)";
	sleep(5);
	cout << "\n\nEvery enemy in the game has different weaknesses and resistances to the different damage types.\n"
		<< "LIFE skills will always heal the target, unless they are an undead creature.\n"
		<< "Nothing in the game can resist ELDRICH abilities, but nothing is weak to them either.";
	sleep(3);
	cout << "\n\nWhen you're ready to continue, press ENTER.";
	cin.get();
	cout << "\n\nHere are the different Target symbols in the game.\n"
		<< "These symbols show who you can target with a given attack!";
	sleep(3);
	cout << "\n\nSINGLE TARGET     0\nThis move will target only one enemy.\n\n"
		<< "ADJACENT TARGET  <0>\nThis move will hit the enemies next to the targeted enemy as well.\n\n"
		<< "ALL TARGET       *0*\nThis move will hit all enemy targets on the field.\n\n"
		<< "RANDOM TARGET    *?*\nThis move will choose its targets randomly out of the enemies on the field.\n\n"
		<< "SELF TARGET      >O<\nThis move will only target yourself. You can't target enemies or other party members with it.\n\n"
		<< "FRIENDLY TARGET   O\nThis move will target one of your party members.\n"
		<< "Reaction commands that target friends cannot target your own character.";
	sleep(5);
	cout << "\n\nWhen you're ready to continue, press ENTER.";
	cin.get();
	cout << "\nFinally, here are the different types of attacks you can use. (Separate from the elements)";
	sleep(3);
	cout << "\n\nMELEE        O> 0\nStrikes an enemy at close range";
	cout << "\n\nPROJECTILE   =o 0\nHits the enemy from a distance with an object";
	cout << "\n\nENERGY       ~$ 0\nUses a magical energy to strike the enemy from any direction";
	cout << "\n\nWEAPON       -> 0\nUses the character's weapon attack type. Changes per character";
	cout << "\n\nThat's all you need to know to play this demo!\n" <<
		"Press ENTER to return to the Main Menu!";
	cin.get();
}

void cutscene(int num)
{
	switch (num)
	{
	case 0: //Hollow Woods ASCII intro
	{
		/*What do you see when you dream?
			[INPUT NEEDED]
		  Do you see people you see in the waking world? Close friends who stand by you in every
		  event, people you haven't seen in years because of distance or death, or perhaps strangers
		  you have never spoken to, who lurk in the background, watching? Perhaps you see strange
		  things that defy imagination, things whose forms swim and shift into things both familiar
		  and bizarre?
		    [INPUT NEEDED] [ASCII art?]
		  Tonight, you see a grand city of unrivaled splendor. Giant, towering crystal spires 
		  crowning great golden, sun-dappled buildings create a shining skyline looming over the
		  wharves where colorful foreign ships come into port. Polished marble streets stretch on,
		  reflecting the sun's light and shining brightly. Is this city a real place that you are 
		  visiting in your mind's eye, or is it perhaps a misremembered place of your past? Does it
		  even matter which it is, or if it is something completely different?
		    [INPUT NEEDED]
		  As you wander the city, its knights and citizens going about their day, you hear a voice.*/
	}
	case 1: //It's a squirrel?
	{
		/**/
	}
	}
}