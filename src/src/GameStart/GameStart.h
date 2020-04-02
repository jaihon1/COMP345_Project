#pragma once

class GameStart {
private:
	GBMaps* gB;
	Scoring* sc;
	HarvestDeck* harvestDeck;
	BuildingDeck* buildingDeck;
	BuildingPool* buildingPool;
	Player** playerArr;
	Hand* hand;
	int numPlayers;

public:
	GBMaps* getGBoard();
	Player** getPlayerArr();
	Scoring* getSc();
	HarvestDeck* getHarvestDeck();
	BuildingDeck* getBuildingDeck();
	Hand* getHand();
	int getNumPlayers();

	void setup(int inNumPlayers);
	void gameResourceMarker(Scoring sc);
};
