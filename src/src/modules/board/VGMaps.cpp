#include <stdio.h>
#include "VGMaps.hpp"

#include <iostream>
using namespace std; 


VGMaps::VGMaps()
{
	village_board[*rows];

	for (int i = 0; i < *rows; i++)
	{
		village_board[*columns];  

		//initialized the current 2D array
		for (int j = 0; j < *columns; j++)
		{
			village_board[i][j].VGstatus = VGSlotStatus::Empty;
		}
	}
}

//I do not think we need
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

VGSlotStatus* VGMaps::checkConnectionsOfSlot(BuildingTile t, int r, int c)
{
	VGSlotStatus connections[4];

	// 0 -> top, 2 -> right, 3 -> bot, 4 -> left

	//check top
	int top = r - 1;
	if(top >= 0) //ensure that top is greater or equal to 0 (not above the 
	{
		connections[0] = village_board[r - 1][c].VGstatus;
	}
	else
	{
		//this means that you are at the top row
		connections[0] = VGSlotStatus::Unavailable; 
	}

	//check right
	int right = c + 1; 
	if (right <= 4)
	{
		connections[1] = village_board[r][c + 1].VGstatus;
	}
	else
	{
		//this means that there are no slots at the right -> you are at the most right column
		connections[1] = VGSlotStatus::Unavailable;
	}
	
	int bottom = r + 1; 
	//check bottom
	if (bottom <= 4)
	{
		connections[2] = village_board[r + 1][c].VGstatus;
	}
	else
	{
		//this means there are no slots at the bottom -> you are at the bottom row
		connections[2] = VGSlotStatus::Unavailable;
	}

	//check left 
	int left = c - 1; 
	if(left >= 0)
	{
		connections[3] = village_board[r][c - 1].VGstatus;
	}
	else
	{
		//this means there are no slots at the left -> you are at the most left column
		connections[3] = VGSlotStatus::Unavailable;
	}
	return connections;

}

//use vectors...

void VGMaps::addNewBuildingTile(BuildingTile t, int r, int c)
{
	BuildingColorType t_type = t.getBuildingColorType(); 
	int t_num = t.getBuildingNum(); 

	//check everytype

	if (t_type == BuildingColorType::GreenSheep)
	{
		//check does it exist already or not
		if (getGreenSheepPlaced()) //is this code right
								  // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus * find_green = checkConnectionsOfSlot(t, r, c); 

			for (int i = 0; i < 4; i++)
			{
				if ((*find_green)[i].BuildingColorType == BuildingColorType::GreenSheep) //?
				{
					//place tile right there 
					village_board[r][c].building_ptr = &t; //is this right?
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
				village_board[r][c].VGstatus.BuildingColorType == BuildingColorType::GreenSheep; //help 
				village_board[r][c].building_ptr = &t; 
				setstate(getGreenSheepPlaced(), true); 
			}
		}
	}
	else if (t_type == BuildingColorType::GreyRock)
	{
		if (getGreyRockPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus * find_grey = checkConnectionsOfSlot(t, r, c);

			for (int i = 0; i < 4; i++)
			{
				if (find_grey[i].BuildingColorType == BuildingColorType::GreyRock)
				{
					//place tile right there 
					village_board[r][c].building_ptr = &t;
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
				village_board[r][c].VGstatus.BuildingColorType == BuildingColorType::GreyRock; //help 
				village_board[r][c].building_ptr = &t;
				setstate(getGreenSheepPlaced(), true);
			}
		}
	}
	else if (t_type == BuildingColorType::RedLumber)
	{
		if (getRedLumberPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus [] find_red = checkConnectionOfSlot(t, r, c);

			for (int i = 0; i < 4; i++)
			{
				if (find_red[i] == BuildingColorType::RedLumber)
				{
					//place tile right there 
					village_board[r][c].building_ptr == &t;
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
				village_board[r][c].VGstatus.BuildingColorType == BuildingColorType::RedLumber; //help 
				village_board[r][c].building_ptr = &t;
				setstate(getGreenSheepPlaced(), true);
			}
		}
	}
	else if (t_type == BuildingColorType::YellowHay)
	{
		if (getYellowHayPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus[] find_yellow = checkConnectionOfSlot(t, r, c);

			for (int i = 0; i < 4; i++)
			{
				if (find_yellow[i] == BuildingColorType::YellowHay)
				{
					//place tile right there 
					village_board[r][c].building_ptr == &t;
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
				village_board[r][c].VGstatus.BuildingColorType == BuildingColorType::YellowHay; //help 
				village_board[r][c].building_ptr = &t;
				setstate(getGreenSheepPlaced(), true);
			}
		}
	}


}

