/*Esssentially this is part 1's observer and viewobserver is part 2*/

#pragma once
#include <iostream>
#include "Observer.h"
#include "../testdriver/GamePlay.h"

using namespace std;

class GameObservers : public Observer //inheriting from Observer 
{
private:
	GamePlay* _subject; //observing the turn
	int* n_players; //number of players 
	CConsoleLoggerEx turnConsole;

public:
	GameObservers();
	GameObservers(GamePlay* const gp);

	~GameObservers();

	void update() override;

	void turndisplay();


};

