
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

	for (auto const& row : *boardJson)
	{
		VG_row++;
		int VG_col = -1;
		for (auto const& column : row)
		{
			VG_col++;

			
			auto const VGSquare = column.find("VGSquare"); 
			cout << "Found VGSquare" << endl; 

			auto const VGSlotStatus = VGSquare->find("VGstatus"); //get value attached to VGStatus 

			cout << "Find VGStatus: " << endl; 
			//auto const BuildingColorType = VGSquare->find("VGSquare_type"); 

			//to recheck!!! 
			if (sMap[*VGSlotStatus] == VGSlotStatus::Taken)
			{
			
				cout << "inside taken" << endl; 
				/*
				auto const attribute = VGSquare->find("*building_ptr"); //returns pointer pointer to attributes

				cout << "Found attributes" << endl; 

				auto const b_ptr = VGSquare->find("*building_ptr");
				*/ 

				/*

				BuildingColorType c = b_ptr[0].get<BuildingColorType>();
				BuildingStatus s = b_ptr[1].get<BuildingStatus>();
				int  n = b_ptr[2].get<int>();

				auto const b_ct  = &bMap[*b_ptr->find("colortype")];
				auto const b_side = &bMap[*b_ptr->find("side")];
				auto const b_num = &bMap[*b_ptr->find("num")];
				*/
			
				auto const b_type = VGSquare->find("BuildingColorType"); 
				auto const b_side = VGSquare->find("BuildingSide"); 
				auto const b_num = VGSquare->find("BuildingNumber"); 

				cout << "Found each attribute" << endl; 

				
				BuildingColorType c = bCTMap[*b_type]; 
				BuildingStatus s = bSMap[*b_side];
				int n = bIMap[*b_num];
				

				/*
				BuildingColorType c; 
				BuildingStatus s;
				int n; 

				//switch statement for building ColorType 
				switch (bCTMap[*b_type])
				{
				case BuildingColorType::GreenSheep:
					c = BuildingColorType::GreenSheep; 
					break; 
				case BuildingColorType::GreyRock:
					c = BuildingColorType::GreyRock; 
					break;
				case BuildingColorType::None:
					c = BuildingColorType::None;
					break;
				case BuildingColorType::RedLumber:
					c = BuildingColorType::RedLumber;
					break;
				case BuildingColorType::YellowHay:
					c = BuildingColorType::YellowHay; 
					break;
				}

				if (bSMap[*b_side] == BuildingStatus::Normal)
				{
					s = BuildingStatus::Normal; 
				}
				else
				{
					s = BuildingStatus::Flipped; 
				}

				switch (bIMap[*b_num])
				{
				case 1:
					n = 1; 
					break;
				case 2:
					n = 2;
					break;
				case 3:
					n = 3;
					break;
				case 4:
					n = 4; 
					break;
				case 5:
					n = 5; 
					break;
				}
				*/ 
				
				/*
				BuildingColorType c = b_ptr[0].get<BuildingColorType>();
				BuildingStatus s = b_ptr[1].get<BuildingStatus>();
				int  n = b_ptr[2].get<int>();
				

				//temp pointers
				BuildingColorType *c_ptr = &c;
				BuildingStatus *s_ptr = &s;
				int *n_ptr = &n;
				*/ 

				//auto const b_int = VGSquare->find("VGstatus");  //find status of building
				//auto const b_side = VGSlotStatus->find("VGSquare_type"); //same as building type
				//int buildingNum = b_int[0].get<int>();

				BuildingTile *temp = new BuildingTile(c, n, s);

				cout << "created new building" << endl; 

				cout << BuildingTile::Building_typeToChar(temp->getBuildingColorType()) << endl;
				cout << BuildingTile::Building_statusToChar(temp->getSide()) << endl;
				cout << BuildingTile::Building_intToChar(temp->getBuildingNum()) << endl;

				board->addNewBuildingTile(*temp, row, column); //dereference temp

				cout << "Added new building sucess" << endl; 
				
				//delete temp;
				//temp = NULL; //good practice
			}
			else if(sMap[*VGSlotStatus] == VGSlotStatus::Empty)
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
				jsonColumns.push_back({ { "VGSquare" ,{{"VGstatus", "Empty"}}} });
				jsonColumns.push_back({ { "VGSquare" ,{{"VGSquare_type", "None"}}} }); //cuz Empty is automatically associated with none
				jsonColumns.push_back({ { "VGSquare" ,{{"*building_ptr", NULL}}} });
			}
			else if ((inGame->village_board[i][j].VGstatus) == VGSlotStatus::Taken)
			{
				//push back status 
				jsonColumns.push_back({ { "VGSquare" ,{{"VGstatus", "Taken"}}} });

				//push back type
				switch (inGame->village_board[i][j].VGSquare_type)
				{
				case BuildingColorType::GreenSheep:
					jsonColumns.push_back({ { "VGSquare", {{"VGSquare_type", "GreenSheep"}}} });
					break;
				case BuildingColorType::GreyRock:
					jsonColumns.push_back({ { "VGSquare", {{"VGSquare_type", "GreyRock"}}} });
					break;
				case BuildingColorType::RedLumber:
					jsonColumns.push_back({ { "VGSquare", {{"VGSquare_type", "RedLumber"}}} });
					break;
				case BuildingColorType::YellowHay:
					jsonColumns.push_back({ { "VGSquare", {{"VGSquare_type", "YellowHay"}}} });
					break;
				case BuildingColorType::None:
					jsonColumns.push_back({ { "VGSquare", {{"VGSquare_type", "None"}}} });
					break;
				}

				//pushing building attributes
				BuildingTile *t = new BuildingTile(inGame->getBuildingTile(i, j));
				// t = &(inGame->getBuildingTile(i, j));

				cout << "Assining vgmap's building tile to temp tile" << endl;

			//cout << BuildingTile::Building_typeToChar(t->getBuildingColorType()) << endl; 


				//can I do this?
				//json c = json::object({ "*building_ptr", { {"colortype", t->Building_typeToChar}, { "side", t->Building_statusToChar }, { "num", t->getBuildingNum }}});
				//json c = json::object({ "*building_ptr", { {t->Building_typeToChar}, {t->Building_statusToChar }, {t->getBuildingNum }}});

				/*
				nlohmann::basic_json<> building_attributes =
				{
					BuildingTile::Building_typeToChar(t->getBuildingColorType()),
					BuildingTile::Building_statusToChar(t->getSide()),
					//should I do this? 
					BuildingTile::Building_intToChar(t->getBuildingNum())
				};
				*/ 

				/*
				cout << BuildingTile::Building_typeToChar(t->getBuildingColorType()) << endl; 
				cout << BuildingTile::Building_statusToChar(t->getSide()) << endl;
				cout << BuildingTile::Building_intToChar((t->getBuildingNum())) << endl;
				*/ 

				/*
				json bType = json::object({ "* _buildingColorType", {BuildingTile::Building_typeToChar(t->getBuildingColorType()) } });
				json bStatus = json::object({ "*_buildingStatus", {BuildingTile::Building_statusToChar(t->getSide())} });
				json bNum = json::object({ "* _buildingNum", {BuildingTile::Building_intToChar(t->getBuildingNum())} });
				*/

				cout << "built attributes" << endl;


				//this code is good 
				//json b = json::object({ { "*building_ptr", "attributes" },{"attributes", BuildingTile::Building_typeToChar(t->getBuildingColorType())} });
				json b = json::object({ { "*building_ptr", "attributes" },{"BuildingColorType", BuildingTile::Building_typeToChar(t->getBuildingColorType())}, {"BuildingSide",BuildingTile::Building_statusToChar(t->getSide())}, {"BuildingNumber", BuildingTile::Building_intToChar(t->getBuildingNum())} });

				//json b = json::object({ { "*building_ptr" , "attributes"}, { {"ColorType", BuildingTile::Building_typeToChar(t->getBuildingColorType())}, {"Side", BuildingTile::Building_statusToChar(t->getSide())}, {"Num", BuildingTile::Building_intToChar(t->getBuildingNum())} } });
				//json b = json::object({ "*building_ptr", building_attributes }); 

				jsonColumns.push_back({ { "VGSquare" , b} });
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

