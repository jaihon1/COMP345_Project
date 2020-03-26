#include "MainLoop.h"

MainLoop::MainLoop()
{

}

MainLoop::MainLoop(int n)
{
	//check for safety 
	if ((n >=2)&&(n <= 4))
	{
		this->num_players = new int(n);
	}
	else
	{
		cout << "wrong number of players" << endl; 
	}	

}


MainLoop::~MainLoop()
{
	switch (*num_players)
	{
	case 2:
		delete p1; 
		p1 = NULL; 

		delete p2;
		p2 = NULL;
		break; 
	case 3:
		delete p1;
		p1 = NULL;

		delete p2;
		p2 = NULL;

		delete p3;
		p3 = NULL;
		break; 
	case 4:
		delete p1;
		p1 = NULL;

		delete p2;
		p2 = NULL;

		delete p3;
		p3 = NULL;

		delete p4; 
		p4 = NULL; 

		break; 
	}

	delete num_players;
	num_players = NULL; 
	delete game_limit; 
	game_limit = NULL; 

	delete gameboard; 
	gameboard = NULL; 
}

/*
vector<int> * MainLoop::getPlayerOrder()
{
	return ; 
}
*/ 

int * MainLoop::getNumPlayers()
{
	return this->num_players; 
}

void MainLoop::findPlayerOrder(int n)
{
	int min = *min_element(player_order.begin(), player_order.end()); 

	int start = 0; 
	//find which index the min element is at 
	for (int i = 0; i < n; i++)
	{
		if (player_order.at(i) == min)
		{
			start = i;
		}
	}

	switch (start)
	{
	case 0:
		//do nothing cuz everything is in the right order;
		break; 
	case 1:
		//the starter is at the 2nd index
		int temp = player_order.at(0); 

		player_order.at(0) = player_order.at(1); //make this the first 
		player_order.at(1) = player_order.at(2);
		player_order.at(2) = player_order.at(3);
		player_order.at(3) = temp; //move to last one 
		break; 
	case 2:
		int temp1 = player_order.at(0); 
		int temp2 = player_order.at(1); 

		player_order.at(0) = player_order.at(2); 
		player_order.at(1) = player_order.at(3); 
		player_order.at(2) = temp1; 
		player_order.at(3) = temp2; 
		break; 
	case 3:
		int temp3 = player_order.at(3); 

		player_order.at(3) = player_order.at(2); 
		player_order.at(2) = player_order.at(1); 
		player_order.at(1) = player_order.at(0); 
		player_order.at(0) = temp3; 
		break; 
	}
}


void MainLoop::MainLoopSetup(int n)
{
	//Code to request the player 

	for (int i = 0; i < n; i++)
	{
		cout << "Enter the ID of player #" + (i + 1) << endl;
		cin >> player_order.at(i);
	}
	//I'm assuming the rest will be initialized by default to 0 (default for int).
	findPlayerOrder(n);

	//create players and set game limits

	game_limit = new int(0);

	switch (n)
	{
	case 2:
		p1 = new Player();
		p1->setID(player_order.at(0));
		players.push_back(*p1);

		p2 = new Player();
		p2->setID(player_order.at(1));
		players.push_back(*p2);

		setGameLimit(game_limits.at(0)); //set game limit to 25
		break;
	case 3:
		p1 = new Player();
		p1->setID(player_order.at(0));
		players.push_back(*p1);

		p2 = new Player();
		p2->setID(player_order.at(1));
		players.push_back(*p2);

		p3 = new Player();
		p3->setID(player_order.at(2));
		players.push_back(*p3);

		setGameLimit(game_limits.at(1));
		break;
	case 4:
		p1 = new Player();
		p1->setID(player_order.at(0));
		players.push_back(*p1);

		p2 = new Player();
		p2->setID(player_order.at(1));
		players.push_back(*p2);

		p3 = new Player();
		p3->setID(player_order.at(2));
		players.push_back(*p3);

		p4 = new Player();
		p4->setID(player_order.at(3));
		players.push_back(*p4);

		setGameLimit(game_limits.at(2));
		break;
	}

	//Create a new Gameboard

	gameboard = new GBMaps(n, 'a', sc); //initialize board A
}


void MainLoop::MainLoopStart(int n)
{
	//keep looping while the number of tiles and game limits arent done 
	while (gameboard->getNumTiles() < *game_limit)
	{
		for (int i = 0; i < n; i++)
		{

			//code for player 

			if (i++ == n)
			{
				i = 0; //reset the loop 
			}
		}
	}


}


void MainLoop::setGameLimit(int n)
{
	*game_limit = n; 
}

