#pragma once
#define _DEBUG
#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#include <stdio.h>
#include <vector>
#include "../tile/Resources.h"

using std::vector;

struct VGSquare { //why struct? 
	VGSlotStatus VGstatus;
	BuildingTile* building_ptr;
	BuildingColorType VGSquare_type;  //same as buildingtype 

	//void deepCopy_square(const VGSquare & v); 
};


class VGMaps {
private:
	//const int* const rows = new int(6); //length of the row
	//const int* const columns = new int(5); //length of the column
	//start off with flags that indicate false, meaning that no tile of that type has been placed yet. 
	bool GreenSheepPlaced = false;
	bool GreyRockPlaced = false;
	bool RedLumberPlaced = false;
	bool YellowHayPlaced = false;

public:

	//is it the end of the world 
	const int* rows = new int(6); //length of the row
	const int* columns = new int(5); //length of the column

	VGMaps();

	~VGMaps();

	VGSlotStatus getStatus(int row, int column);

	VGSquare** village_board;

	//useless?
	bool getGreenSheepPlaced() { return GreenSheepPlaced; }
	bool getGreyRockPlaced() { return GreyRockPlaced; }
	bool getRedLumberPlaced() { return RedLumberPlaced; }
	bool getYellowHayPlaced() { return YellowHayPlaced; }
	bool isEmpty(int row, int column);
	bool isFlipped(int row, int column);


	void setStatus(int row, int column, VGSlotStatus inStatus);


	//void flipIndexes(); //function you call to flip the indexes inside the village board -> update: dont need cuz it doesnt affect the game

	vector <VGSquare> checkConnectionsOfSlot(BuildingTile t, int r, int c);

	void addNewBuildingTile(BuildingTile t, int r, int c);

	BuildingTile getBuildingTile(int r, int c);
	void printVGMap();


};

