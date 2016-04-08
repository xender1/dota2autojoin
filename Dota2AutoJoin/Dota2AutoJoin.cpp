// Dota2AutoJoin.cpp : Run after starting/searching for Dota2 game - leave Dota2 window open/focused. 
//						Will AutoJoin game when found and send message.
//

#include "Main.h"

void startAutoJoin();
int getPixelColor();
int clickAccept();

int main()
{
	cout << "Dota2 Auto Join..." << endl << "Type s to start, x to exit." << endl;
	char input;
	do {
		cin >> input;

		if (input == 's' || input == 'S') {
			startAutoJoin();
			input = 'x';
		}
		else {
			//cout << "Invalid input -- Type s to start, x to exit." << endl;
		}
	} while (input != 'x');

	cout << "Exiting..." << endl;
	_sleep(2000);
    return 0;
}

void startAutoJoin() 
{
	//get pixel color
	//if green accept match
	int found = 0;

	cout << "--Started--" << endl << "--Checking for match to be found...." << endl;
	do {
		found = getPixelColor();
		//sleep(60);
	} while (found != 1);

	cout << "--Match Found..." << endl;
	//found match now accept
	clickAccept();

	cout << "--Accepted Match..." << endl;

	//some check to see if match is now loading

	cout << "--The match is now loading." << endl << "-------------" << endl;
}

int getPixelColor()
{
	int found = 0;

	return found;
}

int clickAccept()
{
	return 1;
}