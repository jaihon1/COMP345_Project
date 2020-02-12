#include <stdio.h>

#include "BuildingTile.h"
#include "Dictionary.h"


//enum class Connection
//{
//	BuildingColorType
//};


class VGSquare{
public: 
	VGSlotStatus VGstatus;
	BuildingTile *building_ptr;
    
	/**
	Connection up;
	Connection down;
	Connection left;
	Connection right;
	**/
};

class VGMaps {
private:
	

	const int* const rows = new int(6); //length of the row
	const int* const columns = new int(5); //length of the column

	//start off with flags that indicate false, meaning that no tile of that type has been placed yet. 
	bool GreenSheepPlaced = false; 
	bool GreyRockPlaced = false; 
	bool RedLumberPlaced = false;
	bool YellowHayPlaced = false; 

	
public: 
	VGMaps(); 

	~VGMaps(); 

	VGSquare ** village_board; 
	VGSlotStatus getStatus(int row, int column);

	bool getGreenSheepPlaced() { return GreenSheepPlaced; }
	bool getGreyRockPlaced() { return GreyRockPlaced;  }
	bool getRedLumberPlaced() { return RedLumberPlaced;  }
	bool getYellowHayPlaced() { return YellowHayPlaced;  }

	bool setstate(bool state, bool given); 

	//void flipIndexes(); //function you call to flip the indexes inside the village board -> update: dont need cuz it doesnt affect the game

	VGSlotStatus [] checkConnectionsOfSlot(BuildingTile t, int r, int c); 

	void addNewBuildingTile(BuildingTile t, int r, int c); 

};

