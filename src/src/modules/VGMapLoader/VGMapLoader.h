
#pragma once
#include "../board/VGMaps.hpp"
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
			this->operator[]("Unavailable") = VGSlotStatus::Unavailable;
		}

		//Damian: forgot the tilde symbol in front of the destructor
		~statusVGMap() {}; 
	};

	struct buildingMap : public map<string, BuildingColorType>
	{
		buildingMap() {
			this->operator[]("GreenSheep") = BuildingColorType::GreenSheep;
			this->operator[]("GreyRock") = BuildingColorType::GreyRock;
			this->operator[]("RedLumber") = BuildingColorType::RedLumber;
			this->operator[]("YellowHay") = BuildingColorType::YellowHay;
			/* 
			Damian:
			I looked in your VGMaps and saw that you had a none type which wasn't included in your map
			*/
			this->operator[]("None") = BuildingColorType::None;
		}

		~buildingMap() {}; 
	};

	//Had to define a map for building status
	struct buildingStatusMap : public map<string, BuildingStatus>
	{
		buildingStatusMap() {
			this->operator[]("Normal") = BuildingStatus::Normal;
			this->operator[]("Flipped") = BuildingStatus::Flipped;
		}

		//Damian: forgot the tilde symbol in front of the destructor
		~buildingStatusMap();
	};

public:
	VGMapLoader();

	VGMapLoader(const char* inFile); //read in a file 

	~VGMapLoader();

	VGMaps * getBoard(); 
};

