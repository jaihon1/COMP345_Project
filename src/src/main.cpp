#include <iostream>

#include <fstream>

/*
#include "player.h"
#include "Dictionary.h"
#include "GBMaps.h"
*/

using namespace std;

/*
int main(int argc, const char * argv[]) {

//    ResourceLocation location = ResourceLocation::topLeft;
//
//    ResourceName lumber = ResourceName::Lumber;
//    ResourceName rock = ResourceName::Rock;
//    ResourceName sheep = ResourceName::Sheep;
//    ResourceName wheat = ResourceName::Wheat;
    
//    HarvestTile harvestTile1(lumber, rock, sheep, wheat);
//    HarvestTile harvestTile2(rock, rock, sheep, wheat);
        
    BuildingDeck buildingDeck;
    HarvestDeck harvestDeck;
//    cout << "Deck size: " << buildingDeck.getSize() << endl;
//    cout << "Draw from BuildingDeck: " << buildingDeck.draw() << endl;
//    cout << "Draw from BuildingDeck: " << buildingDeck.draw() << endl;
//    cout << "Deck size: " << buildingDeck.getSize() << endl;
//    cout << "Draw from BuildingDeck: " << buildingDeck.draw() << endl;
//    cout << "Draw from BuildingDeck: " << buildingDeck.draw() << endl;
//    cout << "Deck size: " << buildingDeck.getSize() << endl;
//    cout << "Draw from BuildingDeck: " << buildingDeck.draw() << endl;
//    cout << "Draw from BuildingDeck: " << buildingDeck.draw() << endl;
//    cout << "Deck size: " << buildingDeck.getSize() << endl;
    
    Player bob;
   
    cout << "Deck size: " << buildingDeck.getSize() << endl;
    cout << "My Buildings size: " << bob.getNumberOfBuildingTiles() << endl;
    cout << "Draw from BuildingDeck: " <<  bob.drawBuilding(buildingDeck) << endl;
    cout << "Deck size: " << buildingDeck.getSize() << endl;
    cout << "My Buildings size: " << bob.getNumberOfBuildingTiles() << endl;
    cout << "Draw from BuildingDeck: " <<  bob.drawBuilding(buildingDeck) << endl;
    
    cout << "H Deck size: " << harvestDeck.getSize() << endl;
    cout << "My Harvest size: " << bob.getNumberOfHarvestTiles() << endl;
    cout << "Draw from HarvestDeck: " <<  bob.drawHarvestTile(harvestDeck) << endl;
    cout << "H Deck size: " << harvestDeck.getSize() << endl;
    cout << "My Harvest size: " << bob.getNumberOfHarvestTiles() << endl;
    cout << "Draw from HarvestDeck: " <<  bob.drawHarvestTile(harvestDeck) << endl;
    
//    bob.addHarvestTile(harvestTile2);
//    cout << "Before:" << endl;
//    bob.getHarvestTiles();
//
//    bob.removeHarvestTile(harvestTile1);
//    cout << "After:" << endl;
//    bob.getHarvestTiles();
    
//    cout << "Address of new tile main: " << &harvestTile1 << endl;
    
//    if(bob.addHarvestTile(harvestTile1).getResource(location) == ResourceName::Lumber) {
//        cout << "Lumber" << endl;
//    }
//
//
//    cout << "Board ID: " << map1.getIdAddress() << endl;
//    cout << "Number of Players: " << map1.getNumberOfPlayers() << endl;


    
	//Damian's test code
	/**
	int id = 11;
    int players = 4;
    
    GBMaps map1(&id, &players);
    
    cout << "Board ID: " << map1.getIdAddress() << endl;
    cout << "Number of Players: " << map1.getNumberOfPlayers() << endl;
	**/

//	VGMaps bmap1 = new VGMaps();


//	VGMaps bmap1 = new VGMaps();
//
//	BuildingTile t1 = new BuildingTile();
//
//	bmap1.addNewBuildingTile(t1, 1, 1);

    
//	system("pause");

   // return 0;
// }



// MAIN FUNCTIONS FROM A main.cpp FILE OUTSIDE src DRIECTORY !!!
/*
int main()
{
	BuildingColorType * type1 = new BuildingColorType(BuildingColorType::GreenSheep); 
	BuildingStatus *status1 = new BuildingStatus(BuildingStatus::Normal); 

	BuildingTile t1(type1, status1); //on stack? do I delete?
	cout << t1.getBuildingNum() << endl;

	BuildingColorType * type2 = new BuildingColorType(BuildingColorType::RedLumber);
	BuildingStatus *status2 = new BuildingStatus(BuildingStatus::Normal);
	BuildingTile t2(type2, status2); //why??? 

	cout << t2.getBuildingNum() << endl;

	cout << "Created building tile"; 

	//A a(); stack
	//A* aPtr = &a; 

	//driver?
	return 0; 
}
*/

//main for VGMaps

/**/
// int main()
// {
// 	//test 
// 	//VGMaps *map = new VGMaps();
// 	VGMaps* v =  &VGMaps();
// 
// 	VGMaps* gg(); //most vexing part annoying error 
// 	//int r = *(v.rows);
// 	//int c = *(v.columns); 
// 
// 	//int *r = map->rows; 
// 	//int *c = map->columns; 
// 
// 	int ro = *(v->rows); 
// 	int co = *(v->columns); 
// 
// 	for (int i = 0; i < ro; i++)
// 	{
// 		for (int j = 0;  j < co; j++)
// 		{
// 			cout << "TILE ";
// 		}
// 		cout << "\n";
// 		cout << "==========================" << endl; 
// 	}
// 	cout << "created VGMap"; 
// 
// 	
// 	//enum function with a switch statements 
// 	//give an example of VGMaps filled 
// 	//edits 
// 
// 	BuildingColorType * type1 = new BuildingColorType(BuildingColorType::GreenSheep);
// 	BuildingStatus *status1 = new BuildingStatus(BuildingStatus::Normal);
// 
// 	BuildingTile t1(type1, status1); //on stack? do I delete?
// 
// 	v->addNewBuildingTile(t1, 1, 1); 
// 	cout << "added new tile" << endl; 
// 
// 	for (int i = 0; i < ro; i++)
// 	{
// 		for (int j = 0; j < co; j++)
// 		{
// 			//BuildingColorType e =
// 			
// 		}
// 		cout << "\n";
// 		cout << "==========================" << endl;
// 	}
// 	cout << "created VGMap";
// 
// 
// 	return 0; 
// }
