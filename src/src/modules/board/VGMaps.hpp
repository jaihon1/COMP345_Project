#include <stdio.h>

#include "..\tile\BuildingTile.hpp"


enum class Connection
{
	Up,
	Down,
	Left,
	Right
};


enum class VGSlotStatus
{
	Empty, //int 0
	BuildingTile //int 1 
};

class VGSquare{
	VGSlotStatus VGstatus;

}

class VGMaps {
private:
	
	const int* const rows = new int(5); //length of the row
	const int* const colums = new int(6); //length of the column

	bool GreenSheepPlaced = false; 
	bool GreyRockPlaced = false; 
	bool RedLumber = false;
	bool YellowHay = false; 
	
public: 
	VGMaps(); 

	~VGMaps(); 

	VGSquare ** village_board; 

	void addNewBuildingTile(int r, int c);

	VGSlotStatus getStatus(int row, int column); 

};

