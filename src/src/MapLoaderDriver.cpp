
#include "modules/VGMapLoader.h"
#include "modules/board/VGMaps.hpp"
#include "modules/tile/Resources.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <ostream>
#include <iostream>
#include <stdlib.h>
using namespace std;


//Methods to print out VGMap to see if it works in creating it 
//Main for Map Loader part 3 

//Test run for VGMap Loader

int main()
{
	//create a new VGBoard
	VGMaps *va = new VGMaps(); 

	int ro = *(va->rows);
	int co = *(va->columns);

	va->printVGMap(); 

	cout << "created VGMap" << endl;
	cout << "Loading VGMAP out" << endl; 

	VGMapSaver *s = new VGMapSaver();

	s->save(va, "C:\json_test\VGMaptest.json"); 

	cout << "Saved va map" << endl; 

	//VGMapLoader * m = new VGMapLoader(); 

	return 0; 
}
