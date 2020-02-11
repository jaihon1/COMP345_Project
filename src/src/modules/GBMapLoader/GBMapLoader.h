#pragma once

#include <map>
#include <string>

using namespace std;

class GBMapLoader {
	public:
		GBMapLoader(const char* inFilePath);
		GBMaps* getBoard();

	private:

		GBMaps* board;

		//redefining index operator of the struct so that it will return an enum
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
