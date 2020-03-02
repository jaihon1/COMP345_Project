
#include "VGMapLoader.h"
#include <iostream>
#include <fstream>
#include "board/VGMaps.hpp"
#include "tile/Resources.h"
#include "../nlohmann/json.hpp"
using namespace std; 

using json = nlohmann::json; 
//VGMapLoader write out to file the current map loader 
VGMapLoader::VGMapLoader()
{
	//deliberately empty for now
}

VGMapLoader::VGMapLoader(const char * inFile)
{
	cout << "Inside in File VGMAPLoader constructor" << endl;
	ifstream inFileStream;
	inFileStream.open(inFile);

	json VGMapDoc;
	inFileStream >> VGMapDoc; //dump inpute file strea into the DOM

	board = new VGMaps();

	auto const boardJson = VGMapDoc.find("VGboard");

	cout << "Found VGBoard" << endl; 

	if (boardJson == VGMapDoc.end())
	{
		cerr << "VGboard not found";
		return;  //return back to where you were
	}

	int VG_row = -1;  

	statusVGMap sMap;
	buildingColorTypeMap bCTMap; //for both vgMap and BuildingTile
	buildingStatusMap bSMap; 
	buildingInt bIMap; 
	cout << "Created the maps to check " << endl; 


	for (auto const& row : *boardJson)
	{
		VG_row++;
		int VG_col = -1;
		for (auto const& column : row)
		{
			VG_col++;

			auto const VGSquare = column.find("VGSquare");  

			auto const VGstat = VGSquare->find("VGstatus"); //get value attached to VGStatus 

			if (sMap[*VGstat] == VGSlotStatus::Taken)
			{
			
				cout << "inside taken" << endl; 

				auto const b_ptr = VGSquare->find("*building_ptr");

				auto const b_type = b_ptr->find("BuildingColorType");
				auto const b_side = b_ptr->find("BuildingSide");
				auto const b_num = b_ptr->find("BuildingNumber");
				cout << "Found each building attribute" << endl;


				BuildingColorType c = bCTMap[*b_type];
				BuildingStatus s = bSMap[*b_side];
				int n = bIMap[*b_num];

				BuildingTile *temp = new BuildingTile(c, n, s);

				cout << "created new building" << endl;

				cout << BuildingTile::Building_typeToChar(temp->getBuildingColorType()) << endl;
				cout << BuildingTile::Building_statusToChar(temp->getSide()) << endl;
				cout << BuildingTile::Building_intToChar(temp->getBuildingNum()) << endl;

				board->addNewBuildingTile(*temp, row, column); //dereference temp
				cout << "Added new building sucess" << endl;


				auto const VGSquare_type = VGSquare->find("VGSquare_type");

				//delete temp;
				//temp = NULL; //good practice
			}
			else if(sMap[*VGstat] == VGSlotStatus::Empty)
			{
				cout << "Inside empty" << endl; 
				/*
				Damian:
				this "board" variable is a VGMap object so you can't index into it like an array
				so I created a setStatus method in your VGmaps to set the slot status to empty
				*/

				//board->setStatus(row, column, VGSlotStatus::Empty);
				//make this area empty

				board->village_board[row][column].VGstatus = VGSlotStatus::Empty;
				board->village_board[row][column].VGSquare_type = BuildingColorType::None;
				board->village_board[row][column].building_ptr = NULL; 

				cout << "Set status to empty and color type to none" << endl; 
			}
					

		}

	}
}

VGMapLoader::~VGMapLoader()
{

}

VGMaps * VGMapLoader::getBoard()
{
	return board; 
}

//why VGMapsaver? 
void VGMapSaver::save(VGMaps * inGame, const char * inFilePath)
{
	outFile.open(inFilePath); 
	cout << "Opening file path " << endl; 
	json d; 
	
	nlohmann::basic_json<> jsonRows = json::array(); 

	for (int i = 0; i < *(inGame->rows); i++)
	{
		nlohmann::basic_json<> jsonColumns = json::array();

		for (int j = 0; j < *(inGame->columns); j++)
		{

			if ((inGame->village_board[i][j].VGstatus) == VGSlotStatus::Empty)
			{
				nlohmann::basic_json <> stats = 
				{
					{"VGstatus", "Empty"}, 
					{"VGSquare_type", "None"}, 
					{"*building_ptr", NULL}
				}; 

				jsonColumns.push_back({"VGSquare", stats });

				/*
				jsonColumns.push_back({ { "VGSquare" ,{{"VGstatus", "Empty"}}} });
				jsonColumns.push_back({ { "VGSquare" ,{{"VGSquare_type", "None"}}} }); //cuz Empty is automatically associated with none
				jsonColumns.push_back({ { "VGSquare" ,{{"*building_ptr", NULL}}} });
				*/ 
			
			}
			else if ((inGame->village_board[i][j].VGstatus) == VGSlotStatus::Taken)
			{
				//push back status 

				BuildingTile *t = new BuildingTile(inGame->getBuildingTile(i, j));

				nlohmann::basic_json <> building_stats = 
				{
					{"VGstatus", "Taken"}, 
					{"VGSquare_type", BuildingTile::Building_typeToChar(t->getBuildingColorType())},
					{"*building_ptr", {{"BuildingColorType", BuildingTile::Building_typeToChar(t->getBuildingColorType())}, {"BuildingSide",BuildingTile::Building_statusToChar(t->getSide())}, {"BuildingNumber", BuildingTile::Building_intToChar(t->getBuildingNum())} } }
				
				}; 

				//json b = json::object({ { "*building_ptr", "attributes" },{"BuildingColorType", BuildingTile::Building_typeToChar(t->getBuildingColorType())}, {"BuildingSide",BuildingTile::Building_statusToChar(t->getSide())}, {"BuildingNumber", BuildingTile::Building_intToChar(t->getBuildingNum())} });

				/*
				nlohmann::basic_json<> building_attributes =
				{
					BuildingTile::Building_typeToChar(t->getBuildingColorType()),
					BuildingTile::Building_statusToChar(t->getSide()),
					//should I do this? 
					BuildingTile::Building_intToChar(t->getBuildingNum())
				};
				*/ 

				//jsonColumns.push_back({ { "VGSquare" , b} });

				jsonColumns.push_back({ "VGSquare", building_stats });
				cout << "Pushed json object back" << endl; 
				
			}
			
		}
		jsonRows.push_back(jsonColumns);

	}
	d["VGboard"] = jsonRows;

	//cout << "printing out d test" << endl;
	// cout << d << endl;

	outFile << d.dump(2);
	outFile.close();
	cout << "Closing outFile path" << endl; 

}

