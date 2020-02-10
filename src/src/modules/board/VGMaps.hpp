#include <stdio.h>

#include "..\tile\BuildingTile.hpp"


//not sure if I need 

class VGMaps {
private:
	
	const int* const row s = new int(6);
	const int* const colums = new int(7); 

	bool GreenSheepPlaced;
	bool GreyRockPlaced; 
	bool RedLumber; 
	bool YellowHay; 
	//pointer to the map
	VGMaps * Map; 
	
public: 
	VGMaps(); 

	~VGMaps(); 

	BuildingTile ** village_board; 

};

