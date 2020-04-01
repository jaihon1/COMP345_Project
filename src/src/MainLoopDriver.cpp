#include "files/modules/MainLoop/MainLoop.h"
#include "files/modules/player/player.h"
#include "files/modules/board/VGMaps.h"
#include <vector>
using namespace std; 


int main()
{
	
	MainLoop *m = new MainLoop(4); //2 is the number of players 

	vector <Player*> *temp = m->getPlayers(); 

	Player *pp1 = temp->at(0); 

	VGMaps *v = pp1->getVGMaps(); 

	v->printVGMap(); 
	

	return 0; 
}