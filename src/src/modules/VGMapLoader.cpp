/*
#include "VGMapLoader.h"
#include <iostream>
#include <fstream>
#include "board/VGMaps.hpp"
#include <nlohmann/json.hpp>
using namespace std; 

using json = nlohmann::json; 
//VGMapLoader write out to file the current map loader 
VGMapLoader::VGMapLoader()
{
	//deliberately empty for now 
}

VGMapLoader::VGMapLoader(const char * inFile)
{
	ifstream inFileStream; 
	inFileStream.open(inFile); 

	json VGMapDoc; 
	inFileStream >> VGMapDoc; //dump inpute file strea into the DOM

	board = new VGMaps(); 

	auto const boardJson = VGMapDoc.find("board"); 

	if (boardJson == VGMapDoc.end())
	{
		cerr << "board not found"; 
		return;  //return back to where you were
	}

	int VG_row = -1;  //why -1 rather than 0? is it because you want to consatntly iterate through? yes 

	statusVGMap sMap; 
	buildingMap bMap; 

	for (auto const& row : *boardJson)
	{
		VG_row++; 
		int VG_col = -1; 
		for (auto const& column : row)
		{
			VG_col++; 

			auto const VGSquare = column.find("VGSquare"); 

			auto const VGSlotStatus = VGSquare->find("VGstatus"); 

			auto const BuildingColorType = VGSquare->find("VGSquare_type"); 
		
			//to recheck!!! 
			if (sMap[*BuildingColorType] == BuildingColorType) //is this line good? 
			{
				auto const b_type = VGSlotStatus->find("_buildingColorType"); 
				auto const b_int = VGSlotStatus->find("_buildingNum"); 
				auto const b_side = VGSlotStatus->find("_buildingStatus");

				//do you create the buildingTile again? im assuming yes
				BuildingTile *temp = new BuildingTile(b_type, b_int, b_side); 
				board->addNewBuildingTile(*temp , row, column); //dereference temp 
			}
			else
			{
				//make this area empty
				board[row][column].VGStatus == VGSlotStatus::Empty; 
			}

		}

		//Make the remaining of the board empty in status


	}
}

VGMapLoader::~VGMapLoader()
{

}

VGMaps * VGMapLoader::getBoard()
{
	return board; 
}
**/
