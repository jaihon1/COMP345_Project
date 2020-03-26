#pragma once

#include <algorithm> //for min and max function 
#include <vector>
#include <iostream>
#include "files/modules/player/player.h"
#include "files/modules/board/GBMaps.h"
using namespace std; 

class MainLoop
{
private:
	vector <int> player_order { player1, player2, player3, player4 };
	int * num_players; 

	//for the IDs 
	int player1;
	int player2;
	int player3; 
	int player4; 

	vector <Player> players; 

	Player *p1; 
	Player *p2; 
	Player *p3;
	Player *p4; 

	vector <int> game_limits{ 25, 35, 45};

	int *game_limit; 

	//create gameboard

	GBMaps * gameboard; 

	Scoring * sc; 

public:
	MainLoop();
	MainLoop(int n); 

	~MainLoop();

	//Accessors
	//vector <int> *getPlayerOrder();
	int * getNumPlayers(); 
	void findPlayerOrder(int n);

	void MainLoopSetup(int n);

	void MainLoopStart(int n); 

	void setGameLimit(int n); 

};

