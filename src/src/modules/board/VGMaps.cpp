#include <stdio.h>
#include <iostream>
#include <string>
#include <ostream>
#include <stdlib.h>
#include "VGMaps.h"

using namespace std;
using std::vector;

int VGMaps::check_name = 0;

string status_to_string(VGSlotStatus s)
{
	switch (s)
	{
	case VGSlotStatus::Empty:
		return "Empty";
	case VGSlotStatus::Taken:
		return "Taken";
	case VGSlotStatus::Unavailable:
		return "Unavailable";
	}

}

string colortype_to_string(BuildingColorType c)
{
	switch (c)
	{
	case BuildingColorType::GreenSheep:
		return "GreenSheep";
	case BuildingColorType::GreyRock:
		return "GreyRock";
	case BuildingColorType::RedLumber:
		return "RedLumber";
	case BuildingColorType::YellowHay:
		return "YellowHay";
	case BuildingColorType::None:
		return "  None   ";
	}
}

VGMaps::VGMaps()
{ 

	village_board = new VGSquare * [*rows]; //on the heap

	for (int i = 0; i < *rows; i++)
	{
		village_board[i] = new VGSquare[*columns]; // on the heap 

		//initialized the current 2D array, might have to do outside 
		for (int j = 0; j < *columns; j++)
		{
			village_board[i][j].VGstatus = VGSlotStatus::Empty;
			village_board[i][j].VGSquare_type = BuildingColorType::None;
			village_board[i][j].building_ptr = NULL; 
		}
	}

	//set VGMAP name
	if ((check_name >= 0) && (check_name <= 3))
	{
		this->village_name = village_names.at(check_name);
		check_name++;
	}
	else if (check_name >= 4)
	{
		cout << "More than 4 players" << endl; 
		this->village_name = " "; //empty string 
	}

	//initialize the slotnum
	int fill = 6; 

	for (int i = 0; i < *rows; i++)
	{
		for (int j = 0; j < *columns; j++)
		{
			village_board[i][j].slotnum = fill; 
		}
		fill--; 
	}
}

VGMaps::~VGMaps()
{
	cout << "Inside VGMAP destructor" << endl; 
	//delete everything inside the village board that is dynamically allocated
	for (int i = 0; i < *rows; i++)
	{
		for (int j = 0; j < *columns; j++)
		{
			delete village_board[i][j].building_ptr; //deleting each building ptr to new

			village_board[i][j].building_ptr = NULL; 
		}
		delete [] village_board[i]; //deleting the rows 
		village_board[i] = NULL; 
	}

	delete [] village_board; //delete the array of pointers 

	village_board = NULL;  //make village_board null 

	//deallocate the rows and colums pointer

	delete rows; 
	rows = NULL; 
	delete columns; 
	columns = NULL; 
	
}

//function is not useful, it is only called through the VGMaps but not inside connections 
VGSlotStatus VGMaps::getStatus(int row, int column)
{
	return village_board[row][column].VGstatus;
}


bool VGMaps::isEmpty(int row, int column) const
{
	return (village_board[row][column].VGstatus == VGSlotStatus::Empty);
}

bool VGMaps::isFlipped(int row, int column) const
{
	return ((*village_board[row][column].building_ptr).getSide() == BuildingStatus::Flipped);
}


void VGMaps::setStatus(int row, int column, VGSlotStatus inStatus) {
	village_board[row][column].VGstatus = inStatus;
}

vector<VGSquare> VGMaps::checkConnectionsOfSlot(BuildingTile t, int r, int c)
{
	VGSquare current = village_board[r][c];

	cout << "Checking connection slots" << endl; 
	vector <VGSquare> connections(4); 

	cout << "Created connections" << endl; 
	cout << "Created unavaiblable square" << endl; 


	//create iterator for insertion
	
	/*
	vector <VGSquare>::iterator it; 
	it = connections.begin(); 
	*/ 

	// 0 -> top, 2 -> right, 3 -> bot, 4 -> left

	//check top
	int top = r - 1;
	if (top >= 0) //ensure that top is greater or equal to 0 (not above the first row) 
	{

		cout << "Checking top" << endl; 
		connections[0] = village_board[r - 1][c]; 


		cout << "Checking top" << endl;
		connections[0] = village_board[r - 1][c];
		//connections->insert(it, village_board[r - 1][c]); //insert at position 1 , dpes the iterator moves?
	}
	else
	{
		cout << "top-unavailable" << endl;
		//this means that you are at the top row
		//connections.insert(it, unavailable); //throwing an error? 
		VGSquare unavailable;
		//declaration of a default constructor for VGSquare empty
		//to print to check if it actually works 

		//initialization of an empty building tile 
		unavailable.VGSquare_type = BuildingColorType::None;
		unavailable.VGstatus = VGSlotStatus::Unavailable;
		unavailable.building_ptr = NULL; //points to nothing cuz no building tile

		connections[0] = unavailable; 

	}

	//check right
	int right = c + 1;
	if (right <= 4)
	{
		cout << "Checking right" << endl; 
		//connections.insert(it + 1, village_board[r][c + 1]); 
		connections[1] = village_board[r][c + 1]; 
	}
	else
	{
		VGSquare unavailable;
		//declaration of a default constructor for VGSquare empty
		//to print to check if it actually works 

		//initialization of an empty building tile 
		unavailable.VGSquare_type = BuildingColorType::None;
		unavailable.VGstatus = VGSlotStatus::Unavailable;
		unavailable.building_ptr = NULL; //points to nothing cuz no building tile

		//this means that there are no slots at the right -> you are at the most right column
		//connections.insert(it + 1, unavailable);
		cout << "right - unavailable" << endl; 
		connections[1] = unavailable; 
	}

	int bottom = r + 1;
	//check bottom
	if (bottom <= 4)
	{

		cout << "checking bottom" << endl; 
		connections[2] = village_board[r + 1][c]; 

		//connections.insert(it + 2, village_board[r+1][c]);
	}
	else
	{
		cout << "bottom - unavailable" << endl; 

		VGSquare unavailable;
		//declaration of a default constructor for VGSquare empty
		//to print to check if it actually works 

		//initialization of an empty building tile 
		unavailable.VGSquare_type = BuildingColorType::None;
		unavailable.VGstatus = VGSlotStatus::Unavailable;
		unavailable.building_ptr = NULL; //points to nothing cuz no building tile

		//this means there are no slots at the bottom -> you are at the bottom row
		//connections.insert(it + 2, unavailable);
		connections[2] = unavailable; 
	}

	//check left 
	int left = c - 1;
	if (left >= 0)
	{
		cout << "checking left" << endl; 
		connections[3] = village_board[r][c - 1]; 


		//connections.insert(it + 3, village_board[r][c-1]);
	}
	else
	{

		cout << "left - unavailable" << endl; 

		VGSquare unavailable;
		//declaration of a default constructor for VGSquare empty
		//to print to check if it actually works 

		//initialization of an empty building tile 
		unavailable.VGSquare_type = BuildingColorType::None;
		unavailable.VGstatus = VGSlotStatus::Unavailable;
		unavailable.building_ptr = NULL; //points to nothing cuz no building tile

		//this means there are no slots at the left -> you are at the most left column
		//connections.insert(it + 3, unavailable);
		connections[3] = unavailable; 


	}
	//cout << "Returning collections " << endl; 
	return connections;

}

//use vectors...

int VGMaps::addNewBuildingTile(BuildingTile t, int r, int c)
{
	
	//assume successful add (only change return status if there is an error)
	int returnStatus = 0;

	//check if its taken
	if (village_board[r][c].VGstatus == VGSlotStatus::Taken)
	{
		cout << "Error in placing tile: tile already existing on this slot" << endl;
		returnStatus = 1;
	}
	else
	{

		BuildingTile* to_add = new BuildingTile(t); //deep copy constructor, prepare to add tile 

		BuildingColorType t_type = t.getBuildingColorType();
		//int t_num = t.getBuildingNum(); 

		//create local iterator
		vector <VGSquare>::iterator it;

		if (t_type == BuildingColorType::GreenSheep)
		{
			//check does it exist already or not
			if (getGreenSheepPlaced()) //is this code right
								  // true, this means that there already exist a tile of that type on the board, check connections!
			{
				vector <VGSquare> find_green = checkConnectionsOfSlot(t, r, c);

				//cout << "Going through iterator" << endl;
				it = find_green.begin();

				//go through the iterations to check if one of its surroundings is of type GreenSheep
				for (int i = 0; i < 4; i++)
				{
					//Condition 1-Has a type of GreenSheep around it
					if ((*(it + i)).VGSquare_type == BuildingColorType::GreenSheep)//derefference the iterator 
					{
						//Condition 2-Has to match the number 
						if (to_add->getBuildingNum() == village_board[r][c].slotnum)
						{
							village_board[r][c].building_ptr = to_add; //copy of assignment operator 
							village_board[r][c].VGSquare_type = BuildingColorType::GreenSheep;
							village_board[r][c].VGstatus = VGSlotStatus::Taken;

							cout << "Success in placing another GreenSheepTile" << endl;
							break;
						}
						else
						{
							cout << "Error in placing GreenSheep - Building Number do not match slot number!" << endl;
							returnStatus = 2;
						}
					}
				}

				if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
				{
					//failed to 
					cout << "Error in placing tile: existing type (GREEN SHEEP) is already on village board, player has to place it next to it" << endl;
					returnStatus = 3;
				}
			}
			else
			{
				//placing new tile
				if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
				{
					if (to_add->getBuildingNum() == village_board[r][c].slotnum)
					{
						village_board[r][c].VGSquare_type = BuildingColorType::GreenSheep;
						village_board[r][c].building_ptr = to_add;
						village_board[r][c].VGstatus = VGSlotStatus::Taken;

						this->GreenSheepPlaced = true;
					}
					else
					{
						cout << "Error in placing GreenSheep - Building Number do not match slot number!" << endl;
						returnStatus = 2;
					}
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
						if (to_add->getBuildingNum() == village_board[r][c].slotnum)
						{
							//place tile right there 
							village_board[r][c].building_ptr = to_add;
							village_board[r][c].VGSquare_type = BuildingColorType::GreyRock;
							village_board[r][c].VGstatus = VGSlotStatus::Taken;

							cout << "Success in placing another GreyRockTile" << endl;
							break;

						}
						else
						{
							cout << "Error in placing GreyRock - Building Number do not match slot number!" << endl;
							returnStatus = 2;
						}
					}
				}

				if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
				{
					//failed to 
					cout << "Error in placing tile: existing type (GREY ROCK) is already on village board, player has to place it next to it" << endl;
					returnStatus = 3;
				}
			}
			else
			{

				if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
				{
					if (to_add->getBuildingNum() == village_board[r][c].slotnum)
					{
						village_board[r][c].VGSquare_type = BuildingColorType::GreyRock;
						village_board[r][c].building_ptr = to_add;
						village_board[r][c].VGstatus = VGSlotStatus::Taken;

						this->GreyRockPlaced = true;
					}
					else
					{
						cout << "Error in placing GreyRock - Building Number do not match slot number!" << endl;
						returnStatus = 2;
					}
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
						//Condition 2
						if (to_add->getBuildingNum() == village_board[r][c].slotnum)
						{
							village_board[r][c].building_ptr = to_add;
							village_board[r][c].VGSquare_type = BuildingColorType::RedLumber;
							village_board[r][c].VGstatus = VGSlotStatus::Taken;

							cout << "Success in placing another RedLumberTile" << endl;
							break;
						}
						else
						{
							cout << "Error in placing RedLumber - Building Number do not match slot number!" << endl;
							returnStatus = 2;
						}
					}
				}

				if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
				{

					//failed to 
					cout << "Error in placing tile: existing type (RED LUMBER) is already on village board, player has to place it next to it" << endl;
					returnStatus = 3;
				}
			}
			else
			{

				if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
				{
					if (to_add->getBuildingNum() == village_board[r][c].slotnum)
					{
						village_board[r][c].VGSquare_type = BuildingColorType::RedLumber;
						village_board[r][c].building_ptr = to_add;
						village_board[r][c].VGstatus = VGSlotStatus::Taken;

						this->RedLumberPlaced = true;
					}
					else
					{
						cout << "Error in placing RedLumber - Building Number do not match slot number!" << endl;
						returnStatus = 2;
					}
					
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
						if (to_add->getBuildingNum() == village_board[r][c].slotnum)
						{
							village_board[r][c].building_ptr = to_add;
							village_board[r][c].VGSquare_type = BuildingColorType::YellowHay;
							village_board[r][c].VGstatus = VGSlotStatus::Taken;

							cout << "Success in placing another YelloHayTile" << endl;
							break;
						}
						else
						{
							cout << "Error in placing YellowHay - Building Number do not match slot number!" << endl;
							returnStatus = 2;
						}
					}
				}
				if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
				{
					//failed to 
					cout << "Error in placing tile: existing type (YELLOW HAY) is already on village board, player has to place it next to it" << endl;
					returnStatus = 3;
				}
			}
			else
			{

				//empty slot
				if (village_board[r][c].VGstatus == VGSlotStatus::Empty)
				{
					if (to_add->getBuildingNum() == village_board[r][c].slotnum)
					{
						village_board[r][c].VGSquare_type = BuildingColorType::YellowHay;
						village_board[r][c].building_ptr = to_add;
						village_board[r][c].VGstatus = VGSlotStatus::Taken;

						this->YellowHayPlaced = true;
					}
					else
					{
						cout << "Error in placing YellowHay - Building Number do not match slot number!" << endl;
						returnStatus = 3;
					}
				}
			}
		}

		//cout << "Deallocate local ptr and Null the to add" << endl;
		//make to_add point to null ptr
		//delete to_add; 
		to_add = NULL; //make to_add point to null but dont delete it because we are adding the buildingTile

		return returnStatus;

	}
    return returnStatus;

}

BuildingTile VGMaps::getBuildingTile(int r, int c)
{
	return *(village_board[r][c].building_ptr); 
}

void VGMaps::printVGMap()
{
	int ro = *rows;
	int co = *columns; 

	cout << setw(8) << this->getVillageName() << endl;

	for (int columnNUM = 0; columnNUM < 5; columnNUM++) {
		cout << "     " << columnNUM << "         ";
	}
	cout << endl;

	for (int i = 0; i < ro; i++)
	{
		cout << i;
		for (int j = 0; j < co; j++)
		{
			//VGSquare *s = v->village_board[i]; 
			//VGSlotStatus check = v->village_board[i][j].VGstatus; 
			//cout << status_to_string(check); 

			BuildingColorType check2 = this->village_board[i][j].VGSquare_type;
			cout << colortype_to_string(check2) << "(" << this->village_board[i][j].slotnum << ")   ";

		}
		cout << "\n";
		//cout << "=====================================" << endl;
	}

}

string VGMaps::getVillageName()
{
	return village_name; 
}

int VGMaps::getScore()
{
	int rowScore = 0;
	int colScore = 0;
	emptySpaces = 0;
	for (int row = 0; row < 6; row++) {
		bool filled = true;
		bool allSameType = village_board[row][0].VGstatus != VGSlotStatus::Empty;
		BuildingColorType rowType = BuildingColorType::None;
		if (allSameType) {
			rowType = village_board[row][0].building_ptr->getBuildingColorType();
			}
		for (int col = 0; col < 5; col++) {
			if (village_board[row][col].VGstatus == VGSlotStatus::Empty) {
				filled = false;
				emptySpaces += 1;
			}
			else if (village_board[row][col].building_ptr->getBuildingColorType() != rowType){
				allSameType = false;
			}
		}
		if (filled) {
			rowScore += allSameType ? row*2 : row;
		}		
	}

	for (int col = 0; col < 5; col++) {
		bool filled = true;
		bool allSameType = village_board[0][col].VGstatus != VGSlotStatus::Empty;
		BuildingColorType colType = BuildingColorType::None;
		if (allSameType) {
			colType = village_board[0][col].building_ptr->getBuildingColorType();
		}
		for (int row = 0; row < 6; row++) {
			if (village_board[row][col].VGstatus == VGSlotStatus::Empty) {
				filled = false;
				break;
			}
			else if (village_board[row][col].building_ptr->getBuildingColorType() != colType) {
				allSameType = false;
			}
		}
		if (filled) {
			switch (col) {
			case 0:
			case 4:
				colScore += allSameType ? 5 *2 : 5;
				break;
			case 1:
			case 3:
				colScore += allSameType ? 4 * 2 : 4;
				break;
			case 2:
				colScore += allSameType ? 3 * 2 : 4;
				break;
			}
		}
	}

	return rowScore + colScore;
		
}

int VGMaps::getEmptySpaces() {
	return emptySpaces;
}
