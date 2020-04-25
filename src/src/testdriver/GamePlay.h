#pragma once
#include "../modules/board/GBMaps.h"
#include "../modules/GBMapLoader/GBMapLoader.h"
#include "../modules/tile/Dictionary.h"
#include "../modules/tile/Resources.h"
#include "../modules/Scoring/Scoring.h"
#include "../modules/player/player.h"
#include "../modules/board/VGMaps.h"
#include "../modules/VGMapLoader/VGMapLoader.h"
#include "../GameStart/GameStart.h"
#include "../GameObservers/Subject.h"

class GamePlay : public Subject
{
private:
	BuildingTile* selectBT(vector<BuildingTile*>* btVector, Hand* hand);
	bool placeBT(BuildingTile* btToAdd, Player* player, Hand* hand);
	void placeHarvestTile(HarvestTile* harvestTile, GBMaps* gameBoard);
	HarvestTile* shipmentTile();
	ResourceName getResourceName(const char* name);
	void singlePlayerBTplacement(Player* player, Hand* hand);
	bool exitBT(bool placeAnother);
	void singleTurn(GBMaps* gameBoard, Player** playerArr, Hand* hand, int turnIndex, int numPlayers);
	int getID(Player** playerArr, int numPlayers);
	void showResources(Hand* hand);
	bool enoughResourcesToPlayBT(vector<BuildingTile*>* btVector, Hand* hand);
	int tieBreaker(Player* winner, Player* contender);
	void declareWinner(Player** playerArr, int numPlayer);

	// ATTRIBUTES FOR TIFF's GAME OBSERVER
	Player* currentPlayer;
	int player_action;
	Scoring* sc;
	void notifyStateChange(int action);

public:
	void playGame();
	Player* getCurrentPlayer();
	int getPlayerAction();
	Scoring* getScoringObject();
};

