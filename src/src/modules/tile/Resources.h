#pragma once

#include <vector>
#include "Dictionary.h"

using namespace std;

class Tile {

};

class BuildingTile {
private:
	BuildingColorType* _buildingColorType;
	int* _buildingNum;
	BuildingStatus* _buildingStatus;

public:

	BuildingTile();
	BuildingTile(BuildingColorType* type, BuildingStatus* status);
	BuildingTile(BuildingColorType *t, int *n, BuildingStatus *s);
	//buildingTile for map loader
	BuildingTile(const BuildingColorType t, const int n, const BuildingStatus s);

	~BuildingTile();

	BuildingColorType getBuildingColorType();
	BuildingStatus getSide();
	int getBuildingNum();

	void setBuildingNum(int num);
	void setBuildingStatus(BuildingStatus s);
	void setBuildingColorType(BuildingColorType c);

	int* generateBuildingNumber();
	void flip();

	//methods for map Loader 
	static const char* Building_typeToChar(BuildingColorType b)
	{
		switch (b)
		{
		case BuildingColorType::GreenSheep:
			return "GreenSheep";
		case BuildingColorType::GreyRock:
			return "GreyRock";
		case BuildingColorType::None:
			return "None";
		case BuildingColorType::RedLumber:
			return "RedLumber";
		case BuildingColorType::YellowHay:
			return "YellowHay";
		}
	}

	//methods for map Loader 
	static const char* Building_statusToChar(BuildingStatus t)
	{
		switch (t)
		{
		case BuildingStatus::Normal:
			return "Normal";
		case BuildingStatus::Flipped:
			return "Flipped";
		}

	}

	//methods for map Loader 
	static char * Building_intToChar(int i)
	{
		char digits[] = { '1', '2', '3', '4', '5', '6' };
		char aChar = digits[i];

		return &aChar; 

	}




};

	class HarvestTile :
		public Tile
	{
	private:
		ResourceName* resourceArr;

	public:
		//parameters are the resources intended for the various locations on the tile
		HarvestTile(ResourceName topRightRes, ResourceName topLeftRes, ResourceName bottomLeftRes, ResourceName bottomRightRes);
		HarvestTile(const HarvestTile &harvestTile);
		HarvestTile();

		~HarvestTile();

		void RotateRight();

		void RotateLeft();

		ResourceName getResource(ResourceLocation inLocation);

		static const char* ResourceNameToString(ResourceName inResourceName) {
			switch (inResourceName) {
			case ResourceName::Lumber:
				return "Lumber";

			case ResourceName::Rock:
				return "Rock";

			case ResourceName::Sheep:
				return "Sheep";

			case ResourceName::Wheat:
				return "Wheat";
			}

			return "Error from ResourceNameToString";
		}
	};

	class HarvestDeck {
	private:
		HarvestTile** harvestDeck;
		int deckLength = 60;

	public:
		HarvestDeck();
		HarvestTile* draw();
		int getSize();

	};

	class BuildingDeck {
	private:
		int *_sizeMax;
		vector<BuildingTile*> *_deck;

	public:
		BuildingDeck();
		BuildingDeck(const BuildingDeck &deck);
		~BuildingDeck();

		vector<BuildingTile*>* getDeck();
		BuildingTile* draw();
		unsigned long getSize();
		void add(BuildingTile &tile);
		void remove(BuildingTile &tile);

	};