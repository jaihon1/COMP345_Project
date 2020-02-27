#include <stdio.h>
#include <iostream>
#include <vector>

#include "VGMaps.hpp"
using namespace std;
using std::vector;


VGMaps::VGMaps()
{
	village_board = new VGSquare*[*rows];

	for (int i = 0; i < *rows; i++)
	{
		village_board[i] = new VGSquare[*columns];  

		//initialized the current 2D array, might have to do outside 
		for (int j = 0; j < *columns; j++)
		{
			village_board[i][j].VGstatus = VGSlotStatus::Empty;
			//for now for testing
			village_board[i][j].VGSquare_type = BuildingColorType::None; 
			
		}
	}
}

//I do not think we need, 
VGMaps::~VGMaps()
{
	for (int i = 0; i < *rows; i++)
	{
		delete[] village_board[i]; 
	}
	delete village_board;
}

//function is not useful, it is only called through the VGMaps but not inside connections 
VGSlotStatus VGMaps::getStatus(int row, int column)
{
	return village_board[row][column].VGstatus; 
}

void VGMaps::setstate(bool state, bool given)
{
	state = given; 
}

vector<VGSquare> VGMaps::checkConnectionsOfSlot(BuildingTile t, int r, int c)
{
	vector <VGSquare> connections(4);
	//get the square where you are currently at

	VGSquare current = village_board[r][c]; 
	VGSquare unavailable; //declaration of a default constructor for VGSquare empty
	//to print to check if it actually works 

	//create iterator for insertion
	vector <VGSquare>::iterator it; 
	it = connections.begin(); 

	// 0 -> top, 2 -> right, 3 -> bot, 4 -> left

	//check top
	int top = r - 1;
	if(top >= 0) //ensure that top is greater or equal to 0 (not above the first row) 
	{
		connections.insert(it, village_board[r - 1][c]); //insert at position 1 , dpes the iterator moves?
	}
	else
	{
		//this means that you are at the top row
		connections.insert(it, unavailable); //throwing an error? 

	}

	//check right
	int right = c + 1; 
	if (right <= 4)
	{
		connections.insert(it + 1, village_board[r][c + 1]); 
	}
	else
	{
		//this means that there are no slots at the right -> you are at the most right column
		connections.insert(it + 1, unavailable);
	}
	
	int bottom = r + 1; 
	//check bottom
	if (bottom <= 4)
	{
		connections.insert(it + 2, village_board[r+1][c]);
	}
	else
	{
		//this means there are no slots at the bottom -> you are at the bottom row
		connections.insert(it + 2, unavailable);
	}

	//check left 
	int left = c - 1; 
	if(left >= 0)
	{
		connections.insert(it + 3, village_board[r][c-1]);
	}
	else
	{
		//this means there are no slots at the left -> you are at the most left column
		connections.insert(it + 3, unavailable);
	}
	return connections;

}

//use vectors...

void VGMaps::addNewBuildingTile(BuildingTile t, int r, int c)
{
	BuildingColorType t_type = t.getBuildingColorType(); 
	int t_num = t.getBuildingNum(); 

	//create local iterator
	vector <VGSquare>::iterator it;
	

	if (t_type == BuildingColorType::GreenSheep)
	{
		//check does it exist already or not
		if (getGreenSheepPlaced()) //is this code right
								  // true, this means that there already exist a tile of that type on the board, check connections!
		{
			vector <VGSquare> find_green = checkConnectionsOfSlot(t, r, c); 
			it = find_green.begin(); 

			//go through the iterations to check if one of its surroundings is of type GreenSheep
			for (int i = 0; i < 4; i++)
			{
				if ((*(it + i)).VGSquare_type == BuildingColorType::GreenSheep) //derefference the iterator 
				{
					//place tile right there 
					village_board[r][c].building_ptr = &t; //is this right?
					village_board[r][c].VGSquare_type = BuildingColorType::GreenSheep; 
					village_board[r][c].VGstatus = VGSlotStatus::Taken; 

					break; 
				}
			}

			if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (GREEN SHEEP) is already on village board, player has to place it next to it" << endl; 

			}
		}
		else
		{
			//placing new tile
			if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
			{
				village_board[r][c].VGSquare_type = BuildingColorType::GreenSheep; //help 
				village_board[r][c].building_ptr = &t; 
				village_board[r][c].VGstatus = VGSlotStatus::Taken; 

				setstate(getGreenSheepPlaced(), true); 
			}
		}
	}
	else if (t_type == BuildingColorType::GreyRock)
	{
		if (getGreyRockPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			vector <VGSquare> find_grey = checkConnectionsOfSlot(t, r, c);
			it = find_grey.begin();

			for (int i = 0; i < 4; i++)
			{
				if ((*(it + i)).VGSquare_type == BuildingColorType::GreyRock)
				{
					//place tile right there 
					village_board[r][c].building_ptr = &t;
					village_board[r][c].VGSquare_type = BuildingColorType::GreyRock; 
					village_board[r][c].VGstatus = VGSlotStatus::Taken; 

					break;
				}
			}

			if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (GREY ROCK) is already on village board, player has to place it next to it" << endl;

			}
		}
		else
		{
			if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
			{
				village_board[r][c].VGSquare_type = BuildingColorType::GreyRock; //help 
				village_board[r][c].building_ptr = &t;
				village_board[r][c].VGstatus = VGSlotStatus::Taken; 
				setstate(getGreyRockPlaced(), true);
			}
		}
	}
	else if (t_type == BuildingColorType::RedLumber)
	{
		if (getRedLumberPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			vector <VGSquare> find_red = checkConnectionsOfSlot(t, r, c);
			it = find_red.begin();

			for (int i = 0; i < 4; i++)
			{
				if ((*(it + i)).VGSquare_type == BuildingColorType::RedLumber)
				{
					//place tile right there 
					village_board[r][c].building_ptr = &t;
					village_board[r][c].VGSquare_type = BuildingColorType::RedLumber; 
					village_board[r][c].VGstatus = VGSlotStatus::Taken; 
					break;
				}
			}
			if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (RED LUMBER) is already on village board, player has to place it next to it" << endl;
			}
		}
		else
		{
			if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
			{
				village_board[r][c].VGSquare_type = BuildingColorType::RedLumber; //help 
				village_board[r][c].building_ptr = &t;
				village_board[r][c].VGstatus = VGSlotStatus::Taken; 
				setstate(getRedLumberPlaced(), true);
			}
		}
	}
	else if (t_type == BuildingColorType::YellowHay)
	{
		if (getYellowHayPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			vector <VGSquare> find_yellow = checkConnectionsOfSlot(t, r, c);
			it = find_yellow.begin();

			for (int i = 0; i < 4; i++)
			{
				if ((*(it + i)).VGSquare_type == BuildingColorType::YellowHay)
				{
					//place tile right there 
					village_board[r][c].building_ptr = &t;
					village_board[r][c].VGSquare_type = BuildingColorType::YellowHay; 
					village_board[r][c].VGstatus = VGSlotStatus::Taken; 

					break;
				}
			}
			if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (RED LUMBER) is already on village board, player has to place it next to it" << endl;
			}
		}
		else
		{
			//empty slot
			if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
			{
				village_board[r][c].VGSquare_type = BuildingColorType::YellowHay; //help 
				village_board[r][c].building_ptr = &t;
				village_board[r][c].VGstatus = VGSlotStatus::Taken; 
				setstate(getYellowHayPlaced(), true);
			}
		}
	}


}

