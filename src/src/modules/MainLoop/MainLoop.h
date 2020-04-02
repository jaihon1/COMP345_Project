#pragma once

#include <algorithm> //for min and max function 
#include <vector>
#include <iostream>
#include "../player/player.h"
#include "../board/GBMaps.h"
#include <iomanip>
#include "../tile/Resources.h"
#include "../tile/Dictionary.h"
using namespace std; 

class MainLoop
{
private:

	int * num_players; 
	vector <int> player_order{ player1, player2, player3, player4 }; //determined should do that for this too - if its 0 its gonna mess up 

	//for the IDs 
	int player1;
	int player2;
	int player3; 
	int player4; 
	
	vector <Player*> *players = new vector <Player *> (4); //vector with player objects (because idk the number of players)

	Player *p1; 
	Player *p2; 
	Player *p3;
	Player *p4; 

	vector <int> game_limits{25, 35, 45};

	int *game_limit; 

	//SET UP ITEMS 
	HarvestDeck * harvestDeck; 
	BuildingDeck * buildingDeck; 
	
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

	void MainLoopStart(); 

	void setGameLimit(int n); 

	vector <Player*> * getPlayers(); 



};

