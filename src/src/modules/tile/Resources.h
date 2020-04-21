#pragma once

#include <string>
#include <vector>
#include "Dictionary.h"

class Player;
class Scoring;

using namespace std;

class BuildingTile {
private:
	BuildingColorType* _buildingColorType;
	int* _buildingNum;
	BuildingStatus* _buildingStatus;

public:
	BuildingTile();
	BuildingTile(BuildingColorType* type, BuildingStatus* status);
	BuildingTile(BuildingColorType* t, int* n, BuildingStatus* s);
	//buildingTile for map loader
	BuildingTile(const BuildingColorType t, const int n, const BuildingStatus s);

	~BuildingTile();

	BuildingColorType getBuildingColorType();
	BuildingStatus getSide();
	int getBuildingNum();

	void setBuildingNum(int num);

	bool numCheck(int num); 

	void setBuildingStatus(BuildingStatus s);
	void setBuildingColorType(BuildingColorType c);

	int* generateBuildingNumber();
	void flip();

	void deepCopy(const BuildingTile& t);

	//Deep copy constructor 
	BuildingTile(const BuildingTile& t);

	BuildingTile & operator = (const BuildingTile &b); 

	void printBuildingTile(); 

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
	static string Building_intToChar(int i)
	{
		string digits[] = { "1", "2", "3", "4", "5", "6" };
		//char *aChar = new char(); 

		string aChar = digits[--i];
		return aChar; //returning the value assigned to the pointer 
	}
};

class BuildingDeck {
private:
	int* _sizeMax;
	vector<BuildingTile*>* _deck;

public:
	BuildingDeck();
	BuildingDeck(const BuildingDeck& deck);
	~BuildingDeck();

	vector<BuildingTile*>* getDeck();
	BuildingTile* draw();
	unsigned long getSize();
	void add(BuildingTile& tile);
	void remove(BuildingTile& tile);

};

class BuildingPool {
private:
	int size = 5;
	BuildingTile** buildingPoolArr = new BuildingTile * [size];
	BuildingDeck* buildingDeck;

public:
	BuildingPool(BuildingDeck* inBuildingDeck);
	char* displayPool();
	BuildingTile* pickBuildingTile(int index);
	BuildingTile** getBuildingPool();
};

class HarvestTile {
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

	void printHarvestTile(); 

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
	~HarvestDeck();
	HarvestTile* draw();
	int getSize();

};


class Hand {
private:
	Scoring* sc;
	int* resourceScoreArr;

public:
	class ExchangeToken {
	private:
		Player* player;
		BuildingTile* buildingTile;
		int row;
		int column;
	
	public:
		ExchangeToken(Player* inP, BuildingTile* inBT, int inR, int inC);
		Player* getPlayer();
		BuildingTile* getBT();
		int getRow();
		int getCol();

	};

	Hand(Scoring* sc);
	void intializeHand();
	void displayHand();
	int exchange(ExchangeToken* exchangeToken);
};

