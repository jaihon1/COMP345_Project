/*Esssentially this is part 1's observer and viewobserver is part 2*/

#pragma once
#include <iostream>
#include "Observer.h"
#include "../modules/MainLoop/MainLoop.h"

using namespace std; 

class GameObservers: public Observer //inheriting from Observer 
{
private: 
	MainLoop *_subject; //observing the turn
	int *n_players; //number of players 
	CConsoleLoggerEx turnConsole;

public:
	GameObservers();
	GameObservers(MainLoop *s); 

	~GameObservers();

	void update() override; 

	void turndisplay();


};

