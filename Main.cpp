// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameState.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;


int main()
{
	

	/*cout << "This is a test. Press Enter to continue.";
	cin.get();*/

	srand(time(0));
	screenAdjust();
	//startupAnim();
	GameState();

	//cout << "The test has been run.";
	cout << "Thank you for testing this game engine.\nPress ENTER to close the window.";
	cin.get();
	cin.get();

    return 0;
}

/*TO DO LIST
-Implement Owl and Deer enemy
-Allow new moves to be learned as level increases
-Overhaul stat increases (Thinking maybe 10%, 25%, then 50%)
*/
