#include "MainLoop.h"

MainLoop::MainLoop()
{

}

MainLoop::MainLoop(int n)
{
	
	
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

	delete scobj;
	scobj = NULL;
}


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
	//cout << min << endl; 

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
	cout << "Inside main loop constructor" << endl;
	//check for safety 
	if ((n >= 2) && (n <= 4))
	{
		num_players = new int(n);
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

		p2 = new Player();
		p2->setID(player_order.at(1));
		players->push_back(p2);

		//game_limit = new int(game_limits.at(0)); 

		//*game_limit = 25; 
		//game_limit = new int(game_limits.at(0));
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

		//game_limit = new int(game_limits.at(1));
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

		//game_limit = new int(game_limits.at(2));
		break;
	}

	cout << "Created players" << endl;

	harvestDeck = new HarvestDeck();
	buildingDeck = new BuildingDeck();
	scobj = new Scoring();
	building_pool = new BuildingPool(buildingDeck);
	gameboard = new GBMaps(n, 'a', scobj); //initialize board A

	scobj->reset_res();
	testHarvestTile = harvestDeck->draw();

}


void MainLoop::MainLoopStart() //Function that the entire game relies upon 
{
	cout << "Here are the orders for the players - (-1 means that there are no valid player)" << endl;

	cout << "Player 1 has ID : " << player_order.at(0) << endl;
	cout << "Player 2 has ID : " << player_order.at(1) << endl;
	cout << "Player 3 has ID : " << player_order.at(2) << endl;
	cout << "Player 4 has ID : " << player_order.at(3) << endl;
	//keep looping while the number of tiles and game limits arent done 
	while (gameboard->getOccupiedTile() < *game_limit)
	{
		//cout << *num_players << endl; 
		for (int i = 0; i < *num_players; i++) //0 to max 4 
		{
			cout << "Player " << i + 1 << " 's turn" << endl;
			//PART 1. Player 1 Turn: Place harvest tile on board
			/// Simulating player to use one of his own harvest tile
			Player * temp = players->at(i); 

			cout << "Here is the current game board" << endl;
			gameboard->printGameBoard(); 

			cout << "Here is your hands" << endl; 
			vector <HarvestTile*> *harvest_tile = temp->getHarvestTiles();  //should print harvest tiles; 

			//CODE MENU FOR PLAYER ACTION : PLACE HARVEST TILE OR PLACE SHIPMENT TILE //int ship = 3;
			//Print 

			int row;
			int column;

			cout << "Choose where you want to place your harvest tile: " << endl; 
			cout << "Row: " << endl; 
			cin >> row; 
			cout << "Column: " << endl; 
			cin >> column;

			int h_index; 

			cout << "Enter index of which HarvestTile of your hand you want to use: " << endl; 
			cin >> h_index; 

			HarvestTile *select_h = harvest_tile->at(h_index); 
			

			temp->placeHarvestTile(row, column, *select_h, *gameboard); 

			cout << "Placed harvest tile" << endl;

			//PART 2. Determine ressources 
			int res[4];
			scobj->get_res(res);
			scobj->display_res(); //print ressources 

			//PART 3. Place building tile on board. Must be running in while(true) and until player decided to not do it anymore
			
			//SHOW PLAYER BUILDING TILE

			int build_tile; 

			while (build_tile != 0)
			{
				temp->getVGBoard()->printVGMap();

				vector <BuildingTile*> *building_tile = temp->getBuildings();

				cout << "Enter 1 to build a building tile, 0 to skip" << endl;
				int choice;
				cin >> choice;

				//CHECK FOR VALIDITY!!!  while(wrong) cout << "again"

				if (choice == 1)
				{
					int b_index;
					cout << "Enter index of which building tile you want to use" << endl;
					cin >> b_index;
					BuildingTile *select_b = building_tile->at(b_index);

					int row_village;
					int column_village;
					cout << "Choose where you want to place your building tile: " << endl;
					cout << "Row: " << endl;
					cin >> row_village;
					cout << "Column: " << endl;
					cin >> column_village;

					temp->placeBuildingTile(row_village, column_village, *select_b);
					scobj->remove_res(static_cast<int>(select_b->getBuildingColorType()), row_village);//remove resource match the type of building???

					cout << "Do you want to build another tile? 1 for yes, 2 for no" << endl;
					cin >> build_tile; 
				}
				else if(choice == 0)
				{
					cout << "DEBUG LOG: Breaking the current loop" << endl; 
					building_tile = 0; 
					break; 
				}
				else //for any other input 
				{
					cout << "Wrong input, try again" << endl; 
					build_tile = 2; 
				}
			}
			
			//PART 4. Share the Wealth
			scobj->get_res(res);
			cout << endl << "Sharing the Wealth" << endl;

			vector <Player*> *remaining; 
			//Get remaining players
			switch (i)
			{
			case 0: //first player  HELP 
				remaining->push_back(players->at(1)); 
				remaining->push_back(players->at(2)); 
				remaining->push_back(players->at(3)); 
				break; 
			case 1:
				remaining->push_back(players->at(2)); 
				remaining->push_back(players->at(3));
				remaining->push_back(players->at(0));
				break; 
			case 2:
				remaining->push_back(players->at(3));
				remaining->push_back(players->at(0));
				remaining->push_back(players->at(1));
				break;
			case 3:
				remaining->push_back(players->at(0));
				remaining->push_back(players->at(1));
				remaining->push_back(players->at(2));
				break; 
			}
			
			cout << "Stored remaining players" << endl; 

			for (int i = 0; i < *num_players - 1; i++) { //cuz this is for the remaining players 
	
				Player *next = remaining->at(i); 

				cout << "Next Player: " << next->getID() << endl ; 

				cout << "Here is the display of the current ressources: " << endl;
				scobj->display_res();

				int repeat; 
				while (repeat != 0)
				{
					int player_decision_pass; // must take input from player (1 == use resource) (0 == pass turn)

					cout << "Enter 1 if you want to build. 0 if you want to pass turn" << endl;
					if (player_decision_pass == 1) {
						//WHAT IS THIS??? 

						int player_decision_resource_lumber = 1; // Decision to use Lumber
						if (player_decision_resource_lumber) {
							int resource_quantity = rand() % 6;
							if (scobj->remove_res(1, resource_quantity) == 0)
								cout << endl << "Not enough resource" << endl;
						}
						int player_decision_resource_sheep = 1; // Decision to use Sheep
						if (player_decision_resource_sheep) {
							int resource_quantity = rand() % 6;
							if (scobj->remove_res(2, resource_quantity) == 0)
								cout << endl << "Not enough resource" << endl;
						}
						int player_decision_resource_wheat = 0; // Decision to use Wheat
						if (player_decision_resource_wheat) {
							int resource_quantity = rand() % 6;
							if (scobj->remove_res(3, resource_quantity) == 0)
								cout << endl << "Not enough resource" << endl;
						}
						int player_decision_resource = 0; // Decision to use Rock
						if (player_decision_resource) {
							int resource_quantity = rand() % 6;
							if (scobj->remove_res(4, resource_quantity) == 0)
								cout << endl << "Not enough resource" << endl;
						}
					}
					else {
						cout << "Passing turn" << endl; 
						repeat = 0; 
					}
				}
				
				
			}

			// 5. Player draws building tiles. 1) Pick from game pool, 2) Pick from pool or deck
			/// Simulating player to select a buidling tile from pool and then select one more building tile from building deck
			int pick_index_1 = 1;
			int pick_index_2 = 3;
			int decision = 1;

			temp->pickFromBuildingPool(*building_pool, pick_index_1);

			if (decision == 0) {
				temp->pickFromBuildingPool(*building_pool, pick_index_2);
			}
			else if (decision == 1) {
				temp->drawBuilding(*buildingDeck);
			}

			/***********the below maybe a more detail version*************/
			scobj->get_res(res);
			int total_left = 0;
			for (int i = 0; i < 4; i++) {
				total_left += res[i];
			}
			int pool_pick = total_left % 5;
			for (int i = 0; i < pool_pick; i++) {
				temp->pickFromBuildingPool(*building_pool, i);
			}
			for (int i = 0; i < total_left - pool_pick; i++) {
				temp->drawBuilding(*buildingDeck);
			}

			// 6. Reset Resource Markers back to 0 AND draw one harvest tile
			temp->drawHarvestTile(*harvestDeck);

			cout << endl << "End of Turn" << endl;
			scobj->display_res();

			gameboard->printGameBoard(); 

			if ((i + 1) == (*num_players + 1))
			{
				cout << "End of the players vector" << endl; 
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


