#pragma once
#include "board/VGMaps.hpp"

#include <map>
#include <string>
using namespace std;

//VGMapLoader just needs to be able to read in a existing building board
class VGMapLoader
{
private: 
	VGMaps * board;

	struct statusVGMap : public map<string, VGSlotStatus>
	{
		statusVGMap()
		{
			this->operator[]("Empty") = VGSlotStatus::Empty;
			this->operator[]("BuildingColorType") = VGSlotStatus::BuildingColorType;
			this->operator[]("Unavailable") = VGSlotStatus::Unavailable;
		}

		statusVGMap() {}; 
	};

	struct buildingMap : public map<string, BuildingColorType>
	{
		buildingMap() {
			this->operator[]("GreenSheep") = BuildingColorType::GreenSheep;
			this->operator[]("GreyRock") = BuildingColorType::GreyRock;
			this->operator[]("RedLumber") = BuildingColorType::RedLumber;
			this->operator[]("YellowHay") = BuildingColorType::YellowHay;

		}

		buildingMap() {}; 
	};

public:
	VGMapLoader();

	VGMapLoader(const char* inFile); //read in a file 

	~VGMapLoader();

	VGMaps * getBoard(); 
};

