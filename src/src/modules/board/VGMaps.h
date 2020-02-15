#include <stdio.h>

#include "BuildingTile.h"
#include "Dictionary.h"


<<<<<<< HEAD:src/src/modules/board/VGMaps.h
//enum class Connection
//{
//	BuildingColorType
//};

=======
enum class VGSlotStatus
{
	Empty, //int 0
	BuildingColorType, //int 1 
	Unavailable //int 2 - any invalid slot (outside the actual map)
};
>>>>>>> 229802b06425541d64ddb51b7b2ca7e5b6d0ebd2:src/src/modules/board/VGMaps.hpp


struct VGSquare{
	VGSlotStatus VGstatus;
<<<<<<< HEAD:src/src/modules/board/VGMaps.h
	BuildingTile *building_ptr;
    
	/**
	Connection up;
	Connection down;
	Connection left;
	Connection right;
	**/
};
=======
	BuildingTile *building_ptr; 

}; 
>>>>>>> 229802b06425541d64ddb51b7b2ca7e5b6d0ebd2:src/src/modules/board/VGMaps.hpp

class VGMaps{
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

	VGSlotStatus getStatus(int row, int column);

	VGSquare ** village_board; 

	bool getGreenSheepPlaced() { return GreenSheepPlaced; }
	bool getGreyRockPlaced() { return GreyRockPlaced;  }
	bool getRedLumberPlaced() { return RedLumberPlaced;  }
	bool getYellowHayPlaced() { return YellowHayPlaced;  }

	void setstate(bool state, bool given); 

	//void flipIndexes(); //function you call to flip the indexes inside the village board -> update: dont need cuz it doesnt affect the game

	VGSlotStatus* checkConnectionsOfSlot(BuildingTile t, int r, int c); 

	void addNewBuildingTile(BuildingTile t, int r, int c); 

};
