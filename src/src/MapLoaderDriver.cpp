/*
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
string status_to_string(VGSlotStatus s)
{
	switch (s)
	{
	case VGSlotStatus::Empty:
		return "Empty";
	case VGSlotStatus::Taken:
		return "Taken";
	case VGSlotStatus::Unavailable:
		return "Unavailable";
	}
}

string colortype_to_string(BuildingColorType c)
{
	switch (c)
	{
	case BuildingColorType::GreenSheep:
		return "GreenSheep";
	case BuildingColorType::GreyRock:
		return "GreyRock";
	case BuildingColorType::RedLumber:
		return "RedLumber";
	case BuildingColorType::YellowHay:
		return "YellowHay";
	case BuildingColorType::None:
		return "None";
	}
}
//Main for Map Loader part 3 


//Test run for VGMap Loader

int main()
{
	//create a new VGBoard
	VGMaps *v = new VGMaps(); 

	int ro = *(v->rows);
	int co = *(v->columns);

	for (int i = 0; i < ro; i++)
	{
		for (int j = 0; j < co; j++)
		{
			//VGSquare *s = v->village_board[i]; 
			//VGSlotStatus check = v->village_board[i][j].VGstatus; 
			//cout << status_to_string(check); 

			BuildingColorType check2 = v->village_board[i][j].VGSquare_type;
			cout << colortype_to_string(check2) << "   ";

			/*if (check == VGSlotStatus::Empty)
			{
				string current = status_to_string(check);
				cout << current;
			}
			else
			{
				string color = colortype_to_string(check2);
				cout << color;
			}
			*/
/**
		}
		cout << "\n";
		cout << "=====================================" << endl;
	}
	cout << "created VGMap" << endl;

	cout << "Loading VGMAP out" << endl; 

	//jsonf jsonfile; 

	return 0; 
}
*/