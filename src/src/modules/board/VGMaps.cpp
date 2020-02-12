#include <stdio.h>
#include "VGMaps.hpp"

#include <iostream>
using namespace std; 


VGMaps::VGMaps()
{
	village_board = new VGSquare*[*rows]; 

	for (int i = 0, i < *rows; i++)
	{
		village_board[i] = new VGSquare*[*columns]; 

		//initialized the current 2D array
		for (int j = 0; j < *columns; j++)
		{
			village_board[i][j].VGstatus = VGSlotStatus::Empty;
		}
	}

}

VGMaps::~VGMaps()
{
	for (int i = 0; i < *rows; i++)
	{
		delete[] village_board[i]; 
	}
	delete village_board;
}

VGMaps::getStatus(int row, int column)
{
	return village_board[row][column].VGstatus; 
}

VGMaps:VGSlotStatus [] checkConnectionsOfSlot(BuildingTile t, int r, int c)
{
	VGSlotStatus [] connections = new VGSlotStatus[4]; 

	// 0 -> top, 2 -> right, 3 -> bot, 4 -> left

	//check top

	if ((r - 1) => 0)
	{
		connections[0] = village_board[r - 1][c].VGSlotStatus;
	}
	else
	{
		connections[0] = NULL; 
	}

	//check right
	if ((c + 1) <= 4)
	{
		connections[1] = village_board[r][c + 1].VGSlotStatus;
	}
	else
	{
		//this means that there are no slots at the right -> you are at the most right column
		connections[1] = NULL; 
	}
	
	//check bottom
	if ((r + 1) <= 4)
	{
		connections[2] = village_board[r + 1][c].VGSlotStatus;
	}
	else
	{
		//this means there are no slots at the bottom -> you are at the bottom row
		connections[2] = NULL;
	}

	//check left 
	if ((c - 1) => 0)
	{
		connections[3] = village_board[r][c - 1].VGSlotStatus;
	}
	else
	{
		//this means there are no slots at the left -> you are at the most left column
		connections[3] = NULL; 
	}
	return connections;

}

VGMaps::addNewBuildingTile(BuildingTile t, int r, int c)
{
	t_type = t.getBuildingColorType; 
	t_num = t.getBuildingNum; 

	//check everytype

	if (t_type == BuildingColorType::"GreenSheep")
	{
		//check does it exist already or not
		if (this.getGreenSheepPlaced()) //is this code right
		) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus [] find_green = checkConnectionOfSlot(t, r, c); 

			for (int i = 0; i < find_green.length; i++)
			{
				if (find_green[i] == "GreenSheep")
				{
					//place tile right there 
					village_board[r][c].building_ptr == t; 
					break; 
				}
			}

			if (village_board[r][c].VGSlotStatus == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (GREEN SHEEP) is already on village board, player has to place it next to it" << endl; 

			}
		}
		else
		{
			if (village_board[r][c].VGSlotstatus == VGSlotStatus::"Empty")
			{
				village_board[r][c].VGSlotstatus == VGSlotStatus::BuildingTile; 
				village_board[r][c].building_ptr = t; 
			}
		}
	}
	else if (t_type == BuildingColorType::"GreyRock")
	{
		if (this.getGreyRockPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus[] find_grey = checkConnectionOfSlot(t, r, c);

			for (int i = 0; i < find_grey.length; i++)
			{
				if (find_grey[i] == BuildingColorType::"GreyRock")
				{
					//place tile right there 
					village_board[r][c].building_ptr == t;
					break;
				}
			}

			if (village_board[r][c].VGSlotStatus == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (GREY ROCK) is already on village board, player has to place it next to it" << endl;

			}
		}
		else
		{
			if (village_board[r][c].VGSlotstatus == VGSlotStatus::"Empty")
			{
				village_board[r][c].VGSlotstatus == VGSlotStatus::BuildingTile;
				village_board[r][c].building_ptr = t;
			}
		}
	}
	else if (t_type == BuildingColorType::"RedLumber")
	{
		if (this.getRedLumberPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus[] find_red = checkConnectionOfSlot(t, r, c);

			for (int i = 0; i < find_red.length; i++)
			{
				if (find_red[i] == BuildingColorType::"GreyRock")
				{
					//place tile right there 
					village_board[r][c].building_ptr == t;
					break;
				}
			}
			if (village_board[r][c].VGSlotStatus == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (RED LUMBER) is already on village board, player has to place it next to it" << endl;
			}
		}
		else
		{
			if (village_board[r][c].VGSlotstatus == VGSlotStatus::"Empty")
			{
				village_board[r][c].VGSlotstatus == VGSlotStatus::BuildingTile;
				village_board[r][c].building_ptr = t;
			}
		}
	}
	else if (t_type == BuildingColorType::"YellowHay")
	{
		if (this.getYellowHayPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus[] find_yellow = checkConnectionOfSlot(t, r, c);

			for (int i = 0; i < find_yellow.length; i++)
			{
				if (find_yellow[i] == BuildingColorType::"YellowHay")
				{
					//place tile right there 
					village_board[r][c].building_ptr == t;
					break;
				}
			}
			if (village_board[r][c].VGSlotStatus == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (RED LUMBER) is already on village board, player has to place it next to it" << endl;
			}
		}
		else
		{
			if (village_board[r][c].VGSlotstatus == VGSlotStatus::"Empty")
			{
				village_board[r][c].VGSlotstatus == VGSlotStatus::BuildingTile;
				village_board[r][c].building_ptr = t;
			}
		}
	}


}

