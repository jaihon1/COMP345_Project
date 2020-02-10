#include <stdio.h>

#include "..\tile\BuildingTile.hpp"


class VGSquare {
public:
	

	VGSquare(); 
	~VGSquare(); 


};
class VGMaps {
private:
	
	//pointer to the map
	VGMaps * Map; 
	
public: 
	VGMaps(); 

	~VGMaps(); 

	VGSquare ** village_board; 

};

