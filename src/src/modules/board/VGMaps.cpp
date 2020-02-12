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
}; 

//I do not think we need
VGMaps::~VGMaps()
{
	for (int i = 0; i < *rows; i++)
	{
		delete[] village_board[i]; 
	}
	delete village_board;
};


VGMaps::getStatus(int row, int column)
{
	return village_board[row][column].VGstatus; 
}


void VGMaps::setstate(bool state, bool given)
{
	state = given; 
}

VGMaps::VGSlotStatus[] checkConnectionsOfSlot(BuildingTile t, int r, int c)
{
	VGSlotStatus connections[4];

	// 0 -> top, 2 -> right, 3 -> bot, 4 -> left

	//check top

	if ((r - 1) => 0)
	{
		connections[0] = village_board[r - 1][c].getStatus();
	}
	else
	{
		connections[0] = NULL; 
	}

	//check right
	if ((c + 1) <= 4)
	{
		connections[1] = village_board[r][c + 1].getStatus();
	}
	else
	{
		//this means that there are no slots at the right -> you are at the most right column
		connections[1] = NULL; 
	}
	
	//check bottom
	if ((r + 1) <= 4)
	{
		connections[2] = village_board[r + 1][c].getStatus();
	}
	else
	{
		//this means there are no slots at the bottom -> you are at the bottom row
		connections[2] = NULL;
	}

	//check left 
	if ((c - 1) => 0)
	{
		connections[3] = village_board[r][c - 1].getStatus();
	}
	else
	{
		//this means there are no slots at the left -> you are at the most left column
		connections[3] = NULL; 
	}
	return connections;
	//delete after the return 

}

VGMaps::addNewBuildingTile(BuildingTile t, int r, int c)
{
	t_type = t.getBuildingColorType(); 
	t_num = t.getBuildingNum(); 

	//check everytype

	if (t_type == BuildingColorType::"GreenSheep")
	{
		//check does it exist already or not
		if (this.getGreenSheepPlaced()) //is this code right
		) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus [] find_green = checkConnectionOfSlot(t, r, c); 

			for (int i = 0; i < 4; i++)
			{
				if (find_green[i] == "GreenSheep")
				{
					//place tile right there 
					village_board[r][c].building_ptr == t; 
					break; 
				}
			}

			if (village_board[r][c].getStatus() == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (GREEN SHEEP) is already on village board, player has to place it next to it" << endl; 

			}
		}
		else
		{
			//placing new tile
			if (village_board[r][c].getStatus() == VGSlotStatus::"Empty")
			{
				village_board[r][c].getStatus() == VGSlotStatus::BuildingTile;
				village_board[r][c].building_ptr = t; 
				this.setstate(this.getGreenSheepPlaced(), true); 
			}
		}
	}
	else if (t_type == BuildingColorType::"GreyRock")
	{
		if (this.getGreyRockPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus[] find_grey = checkConnectionOfSlot(t, r, c);

			for (int i = 0; i < 4; i++)
			{
				if (find_grey[i] == BuildingColorType::"GreyRock")
				{
					//place tile right there 
					village_board[r][c].building_ptr == t;
					break;
				}
			}

			if (village_board[r][c].getStatus() == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (GREY ROCK) is already on village board, player has to place it next to it" << endl;

			}
		}
		else
		{
			if (village_board[r][c].getStatus() == VGSlotStatus::"Empty")
			{
				village_board[r][c].getStatus() == VGSlotStatus::BuildingTile;
				village_board[r][c].building_ptr = t;
				this.setstate(this.getGreyRockPlaced(), true);
			}
		}
	}
	else if (t_type == BuildingColorType::"RedLumber")
	{
		if (this.getRedLumberPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus[] find_red = checkConnectionOfSlot(t, r, c);

			for (int i = 0; i < 4; i++)
			{
				if (find_red[i] == BuildingColorType::"GreyRock")
				{
					//place tile right there 
					village_board[r][c].building_ptr == t;
					break;
				}
			}
			if (village_board[r][c].getStatus() == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (RED LUMBER) is already on village board, player has to place it next to it" << endl;
			}
		}
		else
		{
			if (village_board[r][c].getStatus() == VGSlotStatus::"Empty") //double check that the slot is empty and you can place new tile
			{
				village_board[r][c].getStatus == VGSlotStatus::BuildingTile;
				village_board[r][c].building_ptr = t;
				this.setstate(this.getRedLumberPlaced(), true);
			}
		}
	}
	else if (t_type == BuildingColorType::"YellowHay")
	{
		if (this.getYellowHayPlaced()) // true, this means that there already exist a tile of that type on the board, check connections!
		{
			VGSlotStatus[] find_yellow = checkConnectionOfSlot(t, r, c);

			for (int i = 0; i < 4; i++)
			{
				if (find_yellow[i] == BuildingColorType::"YellowHay")
				{
					//place tile right there 
					village_board[r][c].building_ptr == t;
					break;
				}
			}
			if (village_board[r][c].getStatus() == VGSlotStatus::Empty)
			{
				//failed to 
				cout << "Error in placing tile: existing type (RED LUMBER) is already on village board, player has to place it next to it" << endl;
			}
		}
		else
		{
			if (village_board[r][c].getStatus() == VGSlotStatus::"Empty")
			{
				village_board[r][c].getStatus() == VGSlotStatus::BuildingTile;
				village_board[r][c].building_ptr = t;
				this.setstate(this.getYellowHayPlaced(), true);
			}
		}
	}


}
