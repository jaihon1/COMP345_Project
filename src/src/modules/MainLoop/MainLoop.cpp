#include "MainLoop.h"

MainLoop::MainLoop()
{

}

MainLoop::MainLoop(int n)
{
	cout << "Inside main loop constructor" << endl; 
	//check for safety 
	if ((n >=2)&&(n <= 4))
	{
		this->num_players = new int(n);
	}
	else
	{
		cout << "wrong number of players" << endl; 
	}	

	//Code to request the player 

	for (int i = 0; i < n; i++)
	{
		cout << "Hello! Enter the ID of player # " << endl;
		cin >> player_order.at(i);
	}

	//Filler function 
	if (n != 4)
	{
		switch (n)
		{
		case 2:
			player_order.at(2) = -1; 
			player_order.at(3) = -1;
			break; 
		case 3:
			player_order.at(3) = -1; 
			break; 
		}
	}

	cout << player_order.at(0) << endl;
	cout << player_order.at(1) << endl;
	cout << player_order.at(2) << endl;
	cout << player_order.at(3) << endl;

	//I'm assuming the rest will be initialized by default to 0 (default for int).
	findPlayerOrder(n);

	cout << "Found the order of the players" << endl;

	cout << player_order.at(0) << endl; 
	cout << player_order.at(1) << endl;
	cout << player_order.at(2) << endl;
	cout << player_order.at(3) << endl;
	//create players and set game limits

	game_limit = new int(0);

	players = new vector <Player*>; 

	switch (n)
	{
	case 2:
		p1 = new Player();
		p1->setID(player_order.at(0)); //double check this 
		players->push_back(p1);

		cout << "Created P1" << endl; 

		p2 = new Player();
		p2->setID(player_order.at(1));
		players->push_back(p2);

		cout << "Created P2" << endl; 

		setGameLimit(game_limits.at(0)); //set game limit to 25

		cout << "Set game limit" + *game_limit << endl;
		break;
	case 3:
		p1 = new Player();
		p1->setID(player_order.at(0));
		players->push_back(p1);

		p2 = new Player();
		p2->setID(player_order.at(1));
		players->push_back(p2);

		p3 = new Player();
		p3->setID(player_order.at(2));
		players->push_back(p3);

		setGameLimit(game_limits.at(1));
		break;
	case 4:
		p1 = new Player();
		p1->setID(player_order.at(0));
		players->push_back(p1);

		p2 = new Player();
		p2->setID(player_order.at(1));
		players->push_back(p2);

		p3 = new Player();
		p3->setID(player_order.at(2));
		players->push_back(p3);

		p4 = new Player();
		p4->setID(player_order.at(3));
		players->push_back(p4);

		setGameLimit(game_limits.at(2));
		break;
	}

	cout << "Created players" << endl;
	//Create a new Gameboard

	gameboard = new GBMaps(n, 'a', sc); //initialize board A

}


MainLoop::~MainLoop()
{
	cout << "Main loop destructor" << endl; 
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

	delete players; 
	players = nullptr; 

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
	cout << "Finding player order" << endl; 
	//int min = *min_element(player_order.begin(), player_order.end());  //this would return 0 as the smalles which is what i dont want 

	//find min 
	int min = player_order.at(0); 

	for (int i = 1; i < n; i++)
	{
		if (player_order.at(i) == -1)
		{
			cout << "There is no id in this location" << endl; 
			continue; 

		} else if (player_order.at(i) < min) {
			min = player_order.at(i); 
		}

	}
	cout << min << endl; 

	int start = 0; 
	//find which index the min element is at 
	for (int i = 0; i < n; i++)
	{
		if (player_order.at(i) == min)
		{
			start = i;
		}
	}

	int tem1; 


	if (n == 2)
	{
		switch (start)
		{
		case 0: 
			//everything is in the right order
			break; 
		case 1:
			tem1 = player_order.at(0);
			player_order.at(0) = player_order.at(1); 
			player_order.at(1) = tem1; 
			break; 
		}
	}
	

	if (n == 3)
	{
		switch (start)
		{
		case 0:
			break; 
		case 1:
			tem1 = player_order.at(0); 
			player_order.at(0) = player_order.at(1); 
			player_order.at(1) = player_order.at(2);
			player_order.at(2) = tem1; 
			break; 
		case 2:
			tem1 = player_order.at(2); 
			player_order.at(2) = player_order.at(1); 
			player_order.at(1) = player_order.at(0); 
			player_order.at(0) = tem1; 
			break; 
		}
	}

	if (n == 4)
	{
		int temp = player_order.at(0);
		int temp1 = player_order.at(0);
		int temp2 = player_order.at(1);
		int temp3 = player_order.at(3);

		switch (start)
		{
		case 0:
			break;
		case 1:
			//the starter is at the 2nd index
			//int temp = player_order.at(0); 

			player_order.at(0) = player_order.at(1); //make this the first 
			player_order.at(1) = player_order.at(2);
			player_order.at(2) = player_order.at(3);
			player_order.at(3) = temp; //move to last one 
			break;
		case 2:
			//int temp1 = player_order.at(0); 
			//int temp2 = player_order.at(1); 

			player_order.at(0) = player_order.at(2);
			player_order.at(1) = player_order.at(3);
			player_order.at(2) = temp1;
			player_order.at(3) = temp2;
			break;
		case 3:
			//int temp3 = player_order.at(3); 

			player_order.at(3) = player_order.at(2);
			player_order.at(2) = player_order.at(1);
			player_order.at(1) = player_order.at(0);
			player_order.at(0) = temp3;
			break;
		}
	}
}


void MainLoop::MainLoopSetup(int n)
{

}


void MainLoop::MainLoopStart(int n)
{
	//keep looping while the number of tiles and game limits arent done 
	while (gameboard->getNumTiles() < *game_limit)
	{
		for (int i = 0; i < n; i++)
		{
			//code for player
			cout << "Player " << ++i << " 's turn" << endl; 

			//*** IMPUT TURN SEQUENCE HERE AND IM DONE ***// 

			//to write 

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

vector <Player*> *MainLoop::getPlayers()
{
	return players; 
}


