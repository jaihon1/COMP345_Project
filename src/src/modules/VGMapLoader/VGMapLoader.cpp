
#include "VGMapLoader.h"
#include <iostream>
#include <fstream>
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
	// Damian: needed to instantiate the new enum class
	buildingStatusMap bsMap;

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
			/*
			 Damian: 
			 it looked like you were trying to check the status of the VGMap with the BuildColorType which are incompatable
			 I'm assuming you wanted to check wether the VGSlotStatus was empty?  
			 also, you comparing specific enum to a whole enum class so again I assumed you only wanted to execute the if-statement when the slot status wasn't empty
			 I'm confused because you index into your sMap with BuildingColorType.  So this code will build but will result in runtime failure because there is no buildingColorType names in your sMap
			*/
			
			if (sMap[*BuildingColorType] != VGSlotStatus::Empty) //is this line good? 
			{
				auto const b_type = VGSlotStatus->find("_buildingColorType"); 
				auto const b_int = VGSlotStatus->find("_buildingNum"); 
				auto const b_side = VGSlotStatus->find("_buildingStatus");

				/*
				Damian:
				BuildingTile constructor takes an int pointer as second argument
				so first created int variable and then get the address in the constructor
				with that said, this line converts from JSON int to actual int
				*/
				int buildingNum = b_int[0].get<int>();
				
				//do you create the buildingTile again? im assuming yes
				/*
				Damian:
				BuildingTile constructor takes all pointers in the parameter so
				changed b_type string to enum and then passing the address of that enum to the constructor
				same thing for b_side
				*/
				BuildingTile *temp = new BuildingTile(&bMap[*b_type], &buildingNum, &bsMap[*b_side]); 
				board->addNewBuildingTile(*temp , row, column); //dereference temp 
			}
			else
			{
				/*
				Damian:
				this "board" variable is a VGMap object so you can't index into it like an array
				so I created a setStatus method in your VGmaps to set the slot status to empty
				*/
				board->setStatus(row, column, VGSlotStatus::Empty);
				//make this area empty
				//board[row][column].VGStatus == VGSlotStatus::Empty; 
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

