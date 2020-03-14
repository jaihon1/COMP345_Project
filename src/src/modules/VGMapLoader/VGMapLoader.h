#define _DEBUG
#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#pragma once
#include "../board/VGMaps.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "../tile/Resources.h"
#include <nlohmann/json.hpp>
//#include "../../nlohmann/json.hpp"
using namespace std;

//VGMapLoader just needs to be able to read in a existing building board
class VGMapLoader
{
private:
	VGMaps* board; //does

	struct statusVGMap : public map<string, VGSlotStatus> //Status of the VGSquare
	{
		statusVGMap()
		{
			this->operator[]("Empty") = VGSlotStatus::Empty;
			this->operator[]("Taken") = VGSlotStatus::Taken;
			this->operator[]("Unavailable") = VGSlotStatus::Unavailable;
		}

		~statusVGMap() {};
	};

	struct buildingColorTypeMap : public map<string, BuildingColorType> //use for both VGMap and BuildingTile
	{
		buildingColorTypeMap() {
			this->operator[]("GreenSheep") = BuildingColorType::GreenSheep;
			this->operator[]("GreyRock") = BuildingColorType::GreyRock;
			this->operator[]("RedLumber") = BuildingColorType::RedLumber;
			this->operator[]("YellowHay") = BuildingColorType::YellowHay;
			this->operator[]("None") = BuildingColorType::None;
		}

		~buildingColorTypeMap() {};
	};

	struct buildingStatusMap : public map <string, BuildingStatus> //Status of the BuildingTile
	{
		buildingStatusMap()
		{
			this->operator[]("Normal") = BuildingStatus::Normal;
			this->operator[]("Flipped") = BuildingStatus::Flipped;
		}

		~buildingStatusMap() {};
	};

	struct buildingInt : public map <string, int>
	{
		buildingInt()
		{
			this->operator[]("1") = 1;  //does this work?
			this->operator[]("2") = 2;
			this->operator[]("3") = 3;
			this->operator[]("4") = 4;
			this->operator[]("5") = 5;
			this->operator[]("6") = 6;
		}

		~buildingInt() {};
	};

public:
	VGMapLoader();

	VGMapLoader(const char* inFile); //read in a file 

	~VGMapLoader();

	VGMaps* getBoard();

};

class VGMapSaver {
public:
	void save(VGMaps* inGame, const char* inFilePath);

private:
	ofstream outFile;
};

