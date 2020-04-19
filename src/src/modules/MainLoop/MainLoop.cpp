#include "MainLoop.h"
#include "../../GameObservers/ViewObserver.h"

MainLoop::MainLoop()
{

}

MainLoop::MainLoop(int n)
{
	MainLoopSetup(n); 
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

	//delete game_limit; 
	//game_limit = NULL; 

	delete gameboard; 
	gameboard = NULL; 

	delete scobj;
	scobj = NULL;

	delete gstart; 
	gstart = NULL; 

	//delete remaining;  //Deallocate 
	//remaining = NULL;

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

	//game_limit = new int(0);

	gstart->setup(*num_players);
	ViewObserver* vObs = new ViewObserver(gstart->getSc());
	Player **players_fromGameStart = gstart->getPlayerArr(); 
	players = new vector <Player*>;

	switch (n)
	{
	case 2:
		//p1 = new Player();
		p1 = players_fromGameStart[0]; 
		p1->setID(player_order.at(0), 1); //double check this 
		players->push_back(p1);

		//p2 = new Player();
		p2 = players_fromGameStart[1]; 
		p2->setID(player_order.at(1), 2);
		players->push_back(p2);

		//game_limit = new int(game_limits.at(0)); 

		//*game_limit = 25; 
		//game_limit = new int(game_limits.at(0));
		break;
	case 3:
		//p1 = new Player();
		p1 = players_fromGameStart[0];
		p1->setID(player_order.at(0), 1);
		players->push_back(p1);

		//p2 = new Player();
		p2 = players_fromGameStart[1];
		p2->setID(player_order.at(1), 2);
		players->push_back(p2);

		p3 = players_fromGameStart[2]; 
		p3->setID(player_order.at(2), 3);
		players->push_back(p3);

		//game_limit = new int(game_limits.at(1));
		break;
	case 4:
		//p1 = new Player();
		p1 = players_fromGameStart[0];
		p1->setID(player_order.at(0), 1);
		players->push_back(p1);

		//p2 = new Player();
		p2 = players_fromGameStart[1];
		p2->setID(player_order.at(1), 2);
		players->push_back(p2);

		//p3 = new Player();
		p3 = players_fromGameStart[2];
		p3->setID(player_order.at(2), 3);
		players->push_back(p3);

		//p4 = new Player();
		p4 = players_fromGameStart[3];
		p4->setID(player_order.at(3), 4);
		players->push_back(p4);
		//game_limit = new int(game_limits.at(2));
		break;
	}

	cout << "Created players" << endl;

	/*
	harvestDeck = new HarvestDeck();
	buildingDeck = new BuildingDeck();
	scobj = new Scoring();
	building_pool = new BuildingPool(buildingDeck);
	gameboard = new GBMaps(n, 'a', scobj); //initialize board A
	*/ 

	harvestDeck = gstart->getHarvestDeck(); 
	buildingDeck = gstart->getBuildingDeck(); 
	scobj = gstart->getSc(); 
	building_pool = gstart->getBuildingPool(); 
	gameboard = gstart->getGBoard(); 

	scobj->reset_res();
}


void MainLoop::MainLoopStart() //Function that the entire game relies upon 
{
	cout << "Here are the orders for the players - (-1 means that there are no valid player)" << endl;

	cout << "Player 1 has ID : " << player_order.at(0) << endl;
	cout << "Player 2 has ID : " << player_order.at(1) << endl;
	cout << "Player 3 has ID : " << player_order.at(2) << endl;
	cout << "Player 4 has ID : " << player_order.at(3) << endl;
	//keep looping while the number of tiles and game limits arent done 

	GameEnded(false); 

	cout << gameboard->getOccupiedTile() << endl; 

	while (gameboard->getOccupiedTile() != 48)
	{
		
		cout << "Number of occupied tiles right now: " << gameboard->getOccupiedTile() << endl; 
		//cout << "Inside game loop" << endl; 
		
		for (int i = 0; i < *num_players; i++) //0 to max 4 
		{
			cout << "Player " << (i + 1) << " 's turn" << endl;
			//PART 1. Player 1 Turn: Place harvest tile on board
			Player *temp = players->at(i); 

			cout << "Here is the current game board" << endl;
			gameboard->printGameBoard(); 

			cout << endl << "Here are your harvest tiles in your possession: " << endl; 
			vector <HarvestTile*> *harvest_tile = temp->getHarvestTiles(); 

			cout << endl << "You also have a shipment tile  that allows you to palce a tile with 4 of the same ressources!" << endl; 

			int harvest_choice = 0;
			cout << "Enter 1 if you want to place a harvest tile or enter 2 if you want to place your shipment tile: " << endl; 
			cin >> harvest_choice; 

			hschoice(harvest_choice); //update functions 
			int row = 0; 
			int column = 0; 

			if (harvest_choice == 1) 
			{
				bool h_placed = true; 
				while (h_placed)
				{
					cout << "Choose where you want to place your harvest tile: " << endl;
					cout << "Row: " << endl;
					cin >> row;
					cout << "Column: " << endl;
					cin >> column;

					int h_index;

					cout << "Enter index of which HarvestTile of your hand you want to use: " << endl;
					cin >> h_index;

					HarvestTile *select_h = harvest_tile->at(h_index);
					int place_h_valid = temp->placeHarvestTile(row, column, *select_h, *gameboard);

					if (place_h_valid == 0)
					{
						h_placed = true;  //redundant 
						cout << "Wrong placement of harvest tile" << endl; 
						//break; 
					}
					else if (place_h_valid == 1)
					{
						cout << "Success in placing harvest tile" << endl; 
						h_placed = false; 
					}
				}
				cout << "Placed harvest tile" << endl;
			}
			else if (harvest_choice == 2)
			{
				bool s_placed = true; 
				//For testing? 
				//HarvestTile *special = harvestDeck->draw(); 
				HarvestTile *special = temp->getShipmentTile(); 
				while (s_placed)
				{
					int type = 0; 
					cout << "Enter what type you want: Lumber - 1, Sheep - 2, Wheat - 3, Rock - 4" << endl;
					cin >> type;

					cout << "Choose where you want to place your shipment tile: " << endl;
					cout << "Row: " << endl;
					cin >> row;
					cout << "Column: " << endl;
					cin >> column; 

					//HarvestTile *special = new HarvestTile(); 

					int place_s_valid = temp->placeShipmentTile(row, column, *special, *gameboard, type);

					if (place_s_valid == 0)
					{
						cout << "Wrong placement of shipment tile, try again" << endl;
						s_placed = true;
					}
					else if (place_s_valid == 1)
					{
						cout << "Success in placing shipment tile" << endl;
						s_placed = false;
					}
				}
				cout << "Place Shipment tile" << endl; 
				//delete special; 
				//special = NULL; 
			}
			cout << endl << "Here is the updated game board" << endl; 
			gameboard->printGameBoard();
			
			//PART 2. Determine ressources 
			int res[4]; //store the current ressources here to display 



			//scobj->get_res(res);
			//scobj->display_res(); //print ressources 

			//PART 3. Place building tile on board. Must be running in while(true) and until player decided to not do it anymore
			//SHOW PLAYER BUILDING TILE
			int build_tile = 2; 

			while (build_tile == 2)
			{
				scobj->get_res(res); 

				//use notify to call instead of this? 
				scobj->display_res();

				cout << endl << "Here is your village board" << endl << endl;
				temp->getVGBoard()->printVGMap();

				cout << endl <<"Here are the building tiles in your hand: " << endl; 
				vector <BuildingTile*> *building_tile = temp->getBuildings();

				cout << endl << "Enter 1 to build a building tile, 0 to skip" << endl;
				int choice;
				cin >> choice; 

				if (choice == 1)
				{
					hschoice(3); 
					//Checking ressources input 
					int res_use[4]; //why 4 - does user input four type and how many they want to use right away?

					cout << "For each type of ressources (Lumber - 0, Sheep - 1, Wheat - 2, Rock - 3), select how many you need" << endl;
					for (int i = 0; i < 4; i++)
					{
						//res_usage[i] = rand() % 10; 
						cout << endl << "Type # " << i; 
						switch (i)
						{
						case 0:
							cout << " Lumber";
							break;
						case 1:
							cout <<  " Sheep";
							break;
						case 2:
							cout << " Wheat";
							break;
						case 3:
							cout << " Rock";
							break;
						} 
						cout << " and how many: " << endl;
						cin >> res_use[i];
					}

					for (int i = 0; i < 4; i++)
					{
						if (res_use[i] > 0)
						{
							if (scobj->remove_res(1, res_use[i] == 0))
							{
								cout << endl << "Not enough resource type " << i << endl;
							}
							else{

								cout << "For type ";  
								switch (i)
								{
								case 0:
									cout << "Lumber" << endl; 
									break; 
								case 1: 
									cout << "Sheep" << endl; 
									break; 
								case 2:
									cout << "Wheat" << endl; 
									break;
								case 3:
									cout << "Rock" << endl; 
									break; 
								}

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
								scobj->remove_res(static_cast<int>(select_b->getBuildingColorType()), row_village);//remove resource match the type of building??	
							}
						}
						else
						{
							cout << "Player does not want to use ressource type " << i; 
								
							switch (i)
							{
							case 0:
								cout << "- Lumber" << endl;
								break;
							case 1:
									cout << "- Sheep" << endl;
									break;
							case 2:
									cout << "- Wheat" << endl;
									break;
							case 3:
									cout << "- Rock" << endl;
									break;
							}
						}
					}
					cout << "Player temp finished building. " << endl << endl << endl;
					building_tile = 0;
				}
				else if(choice == 0) 
				{
					hschoice(4); 
					cout << "DEBUG LOG: Breaking the current loop, player skipping turn." << endl; 
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
			cout << endl << "Sharing the Wealth" << endl << endl;

			/**
			switch (i)
			{
			case 0: 
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
			*/ 

			int current_position = i; 

			for (int k = 0; k < *num_players - 1; k++) { //cuz this is for the remaining players 
	
				current_position++; 
				if (current_position == *num_players) //if current position is equal to the max of num players (restart)
				{
					current_position = 0; 
				}
				Player *next = players->at(current_position); 

				cout << "Next Player: " << next->getID() << endl << endl; 

				cout << "Here is the display of the current ressources: " << endl << endl;
				scobj->display_res();

				int repeat = 2; 
				while (repeat == 2)
				{
					//SHOW EACH REMAINING PLAYER THEIR VILLAGEA BOARD
					cout << "Here is your current village board: " << endl; 
					next->getVGBoard()->printVGMap();


					cout << endl << "Here are the building tiles in your hand (by index): " << endl << endl;
					vector <BuildingTile*> *next_btiles = next->getBuildings();


					int player_decision_pass; // must take input from player (1 == use resource) (0 == pass turn)
					cout << "Enter 1 if you want to build. 0 if you want to pass turn" << endl;
					cin >> player_decision_pass; 

					if (player_decision_pass == 1) {
	
						//Shouldnt I do this for the player at the start too? 
						int res_usage[4]; //why 4 - does user input four type and how many they want to use right away?
						for (int i = 0; i < 4; i++)
						{
							//res_usage[i] = rand() % 10; 
							cout << "For each type of ressources (Lumber - enter 1, Sheep - enter 2, Wheat - enter 3, Rock - enter 4), select how many you need" << endl; 
							cout << endl << "Type # " << i << " and how many: " << endl; 
							cin >> res_usage[i]; 
						}

						//Use ressouces 
						for (int i = 0; i < 4; i++)
						{
							if (res_usage[i] > 0)
							{
								if (scobj->remove_res(1, res_usage[i] == 0))
								{
									cout << endl << "Not enough resource type " << i << endl;
								}
								else
								{
									cout << "For type " << i << endl; //Print which type it is?
									
									int b_index2;
									cout << "Enter index of which building tile you want to use" << endl;
									cin >> b_index2;
									BuildingTile *select_b2 = next_btiles->at(b_index2);

									int row_village2;
									int column_village2;
									cout << "Choose where you want to place your building tile: " << endl;
									cout << "Row: " << endl;
									cin >> row_village2;
									cout << "Column: " << endl;
									cin >> column_village2;

									next->placeBuildingTile(row_village2, column_village2, *select_b2);
									scobj->remove_res(static_cast<int>(select_b2->getBuildingColorType()), row_village2);
								}
							}
							else
							{
								cout << "Player does not want to use ressource type " << i << endl; 
							}
						}
						cout << "Player next finished building. " << endl; 
						repeat = 0; 
					}
					else if(player_decision_pass == 0)
					{
						cout << "Passing turn" << endl; 
						repeat = 0; 
					}
					else
					{
						cout << "Wrong player decision input, retry" << endl;
						repeat = 2; 
					}
				}
			}

			// 5. Player draws building tiles. 1) Pick from game pool, 2) Pick from pool or deck
			
			/*
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
			*/ 

			/***********the below maybe a more detail version*************/
			//For now its simulated - make the player 

			//TO CHECK 
			scobj->get_res(res);
			int total_building = 0;
			for (int i = 0; i < 4; i++) {
				if (res[i] == 0)
					total_building++;
			}

			//FULL IMPLEMENTATION - PRINT POOL OUT AND LET THE PLAYER CHOOSE

			int pool_pick = total_building % 3;
			for (int i = 0; i < pool_pick; i++) {
				temp->pickFromBuildingPool(*building_pool, i);
			}
			for (int i = 0; i < total_building - pool_pick; i++) {
				temp->drawBuilding(*buildingDeck);
			}

			// 6. Reset Resource Markers back to 0 AND draw one harvest tile
			temp->drawHarvestTile(*harvestDeck);

			cout << endl << "End of Turn" << endl << endl;

			scobj->display_res();

			gameboard->printGameBoard(); 

			cout << endl; 

			if ((i + 1) == (*num_players + 1))
			{
				cout << "End of the players vector" << endl; 
				i = 0; //reset the loop 
			}
		}
	}
	cout << "Number of tiles inputed" << gameboard->getOccupiedTile() << endl;

	cout << "End of the game" << endl; 
	GameEnded(true); 
}

/*
void MainLoop::setGameLimit(int n)
{
	*game_limit = n; 
}
*/ 

vector <Player*> *MainLoop::getPlayers()
{
	return players; 
}

Scoring* MainLoop::getScoringObject()
{
	return scobj; 
}

bool MainLoop::GameEnded(bool check)
{
	return check; 
}

Player* MainLoop::getCurrentPlayer(int index)
{
	//validity needed to check 
	return players->at(index); 
}

void MainLoop::hschoice(int c)
{
	player_action = c; 
}

int MainLoop::getPlayerAction()
{
	return player_action; 
}



