#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "../board/GBMaps.h"
#include "../tile/Dictionary.h"
#include "../tile/Resources.h"
#include "../Scoring/Scoring.h"
#include "../player/player.h"

using namespace std;

class GBMapLoader {
	public:
		GBMapLoader(const char* inFilePath, Scoring* sc);
		GBMaps* getBoard();

	private:

		GBMaps* board;

		//redefining index operator of the struct so that it will return an enum
		//the purpose of this is to convert string to enum
		struct statusMap : public map<string, GBSquareStatus> {
			statusMap() {
				this->operator[]("Empty") = GBSquareStatus::Empty;
				this->operator[]("BuildingTile") = GBSquareStatus::BuildingTile;
				this->operator[]("HarvestTile") = GBSquareStatus::HarvestTile;
				this->operator[]("PondTile") = GBSquareStatus::PondTile;
				this->operator[]("Unavailable") = GBSquareStatus::Unavailable;
			}
			~statusMap() {};
		};

		//redefining index operator of the struct so that it will return an enum
		//the purpose of this is to convert string to enum
		struct resourceMap : public map<string, ResourceName> {
			resourceMap() {
				this->operator[]("Lumber") = ResourceName::Lumber;
				this->operator[]("Rock") = ResourceName::Rock;
				this->operator[]("Sheep") = ResourceName::Sheep;
				this->operator[]("Wheat") = ResourceName::Wheat;
			}
			~resourceMap() {};
		};
};

class GBMapSaver {
public:
	void save(GBMaps* inBoard, const char* inFilePath);

private:
	ofstream outFile;
};
