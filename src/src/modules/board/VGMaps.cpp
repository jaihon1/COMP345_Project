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
	if (row < 0 || row>6 || column < 0 || column>6) {
		return VGSlotStatus::Unavailable;
	}

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

bool VGMaps::checkConnections(BuildingColorType bct, int r, int c) {

	// -1 offset because bt color type starts at 1
	int firstTileArrIndex = static_cast<int>(bct) - 1;

	if (firstTileArr[firstTileArrIndex]) {
		firstTileArr[firstTileArrIndex] = false;
		return true;
	}

	// up
	if (getStatus(r, c - 1) == VGSlotStatus::Taken && getBuildingTile(r, c - 1).getBuildingColorType() == bct) {
			return true;
	}
	// down
	if (getStatus(r, c + 1) == VGSlotStatus::Taken && getBuildingTile(r, c + 1).getBuildingColorType() == bct) {
			return true;
	}
	// left
	if (getStatus(r - 1, c) == VGSlotStatus::Taken && getBuildingTile(r - 1, c).getBuildingColorType() == bct) {
			return true;
	}
	// right
	if (getStatus(r + 1, c) == VGSlotStatus::Taken && getBuildingTile(r + 1, c).getBuildingColorType() == bct) {
			return true;
	}

	return false;
}


int VGMaps::addNewBuildingTile(BuildingTile &buildingTile, int r, int c) {
 
	if (getStatus(r, c) == VGSlotStatus::Taken || getStatus(r, c) == VGSlotStatus::Unavailable || village_board[r][c].slotnum != buildingTile.getBuildingNum()) {
		return 1;
	}

	// -1 offset because bt color type starts at 1
	int firstTileArrIndex = static_cast<int>(buildingTile.getBuildingColorType())-1;

	if (checkConnections(buildingTile.getBuildingColorType(), r, c)) {
		village_board[r][c].building_ptr = &buildingTile;
		setStatus(r, c, VGSlotStatus::Taken);
		village_board[r][c].VGSquare_type = buildingTile.getBuildingColorType();
		return 0;
	}

	return 1;
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
			cout << " " << colortype_to_string(check2) << "(" << this->village_board[i][j].slotnum << ")   ";

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
