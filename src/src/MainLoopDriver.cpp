#include "modules/MainLoop/MainLoop.h"
#include "modules/player/player.h"
#include "modules/board/VGMaps.h"
#include "GameObservers/GameObservers.h"
#include <vector>
using namespace std; 


int main()
{
	cout << "Driver for MainLoop" << endl; 

	MainLoop *m = new MainLoop(); //2 is the number of players 
	m->MainLoopSetup(2); 
	
	//Attaching observer 
	GameObservers *g = new GameObservers(m); 

	/*
	vector <Player*> *temp = m->getPlayers(); 
	Player *pp1 = temp->at(0); 
	Player *pp2 = temp->at(1); 
	VGMaps *v = pp1->getVGBoard(); 
	v->printVGMap(); 
	VGMaps *v2 = pp2->getVGBoard(); 
	cout << "changed board" << endl << endl; 
	v2->printVGMap(); 
	*/ 

	m->MainLoopStart(); 



	return 0; 
}

