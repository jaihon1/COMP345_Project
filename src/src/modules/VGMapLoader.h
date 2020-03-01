
#pragma once
#include "board/VGMaps.hpp"
#include <iostream>
#include <fstream>
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

		~statusVGMap() {}; 
	};

	struct buildingMap : public map<string, BuildingColorType>
	{
		buildingMap() {
			this->operator[]("GreenSheep") = BuildingColorType::GreenSheep;
			this->operator[]("GreyRock") = BuildingColorType::GreyRock;
			this->operator[]("RedLumber") = BuildingColorType::RedLumber;
			this->operator[]("YellowHay") = BuildingColorType::YellowHay;
			this->operator[]("None") = BuildingColorType::None;
		}
	
		~buildingMap() {}; 
	};

public:
	VGMapLoader();

	VGMapLoader(const char* inFile); //read in a file 

	~VGMapLoader();

	VGMaps * getBoard();

};

class VGMapSaver {
public: 
	void save(VGMaps * inGame, const char * inFilePath);

private: 
	ofstream outFile; 
};

