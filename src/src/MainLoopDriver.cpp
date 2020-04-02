#include "files/modules/MainLoop/MainLoop.h"
#include "files/modules/player/player.h"
#include "files/modules/board/VGMaps.h"
#include <vector>
using namespace std; 

int main()
{
	cout << "Driver for MainLoop" << endl; 

	MainLoop *m = new MainLoop(); //2 is the number of players 
	m->MainLoopSetup(3); 
	/*
	vector <Player*> *temp = m->getPlayers(); 
	Player *pp1 = temp->at(0); 
	VGMaps *v = pp1->getVGMaps(); 
	v->printVGMap(); 
	*/ 

	m->MainLoopStart(); 

	return 0; 
}