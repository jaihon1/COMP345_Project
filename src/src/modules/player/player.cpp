#include "player.h"
#include "../Scoring/Scoring.h"
#include <algorithm>

/*
***DO NOT USE BECAUSE PLAYER REQUIRES SCORING OBJECT***
Player::Player() {
//    cout << "Creating Player with Main: " << this << endl;

	cout << "Inside player constructor" << endl;
	_villageBoard = new VGMaps();
	_harvestTiles = new vector<HarvestTile*>;
	_buildingTiles = new vector<BuildingTile*>;
	ID = new int(-1); //will be decided at runtime
}
*/

Player::Player(Scoring* inSc, int indexPosition)
{
	_villageBoard = new VGMaps();
	_harvestTiles = new vector<HarvestTile*>;
	_buildingTiles = new vector<BuildingTile*>;
	ID = new int(-1); //will be decided at runtime 
	position = new int(indexPosition+1);
	sc = inSc;
}

Player::Player(const Player& player) {
	_villageBoard = player._villageBoard;
	_harvestTiles = player._harvestTiles;
	_buildingTiles = player._buildingTiles;
	shipmentTile = player.shipmentTile;
}

Player::~Player() {

	cout << "Player destructor" << endl;
	if (_villageBoard) {
		delete _villageBoard;
		_villageBoard = nullptr;
	}

	if (_harvestTiles) {
		delete _harvestTiles;
		_harvestTiles = nullptr;
	}

	if (_buildingTiles) {
		delete _buildingTiles;
		_buildingTiles = nullptr;
	}

	if (ID)
	{
		delete ID;
		ID = nullptr;
	}

}


HarvestTile* Player::addHarvestTile(HarvestTile& tile) {
	_harvestTiles->push_back(&tile);
	return &tile;
}

HarvestTile* Player::removeHarvestTile(HarvestTile& tile) {
	_harvestTiles->erase(std::remove(_harvestTiles->begin(), _harvestTiles->end(), &tile), _harvestTiles->end());
	return &tile;
}

vector<HarvestTile*>* Player::getHarvestTiles() {
	return _harvestTiles;
}

int Player::placeHarvestTile(int row, int col, HarvestTile& tile, GBMaps& gameBoard) {
	int tile_success = gameBoard.addHarvestTile(row, col, &tile);
	removeHarvestTile(tile);
	return tile_success;
}

int Player::placeShipmentTile(int row, int col, HarvestTile& tile, GBMaps& gameBoard, int type) {

	int ship_success = gameBoard.addShipmentTile(row, col, &tile, type);
	//removeHarvestTile(tile); //Dont remove it from the hand cuz it's never inside the hand to begin with
	return ship_success;
}

HarvestTile* Player::drawHarvestTile(HarvestDeck& deck) {
	HarvestTile* drawn_card = deck.draw();
	addHarvestTile(*drawn_card);
	return drawn_card;
}

unsigned long Player::getNumberOfHarvestTiles() {
	return _harvestTiles->size();
}

void Player::setShipmentTile(HarvestTile* harvestTile)
{
	shipmentTile = harvestTile;
}



vector<BuildingTile*>* Player::getBuildings() {
	return _buildingTiles;
}

BuildingTile* Player::addBuildingTile(BuildingTile& tile) {
	_buildingTiles->push_back(&tile);
	sc->set_avail_building(*position, getNumberOfBuildingTiles());
	return &tile;
}

BuildingTile* Player::removeBuildingTile(BuildingTile& tile) {
	_buildingTiles->erase(std::remove(_buildingTiles->begin(), _buildingTiles->end(), &tile), _buildingTiles->end());
	sc->set_avail_building(*position, getNumberOfBuildingTiles());
	return &tile;
}

BuildingTile* Player::drawBuilding(BuildingDeck& deck) {
	BuildingTile* drawn_card = deck.draw();
	addBuildingTile(*drawn_card);
	return drawn_card;
}

int Player::placeBuildingTile(int row, int col, BuildingTile& tile) {
	int status = _villageBoard->addNewBuildingTile(tile, row, col);

	if (status == 0) {
		removeBuildingTile(tile);
		sc->remove_res(static_cast<int>(tile.getBuildingColorType()), tile.getBuildingNum());
		sc->add_density(*position, 1);

		// get the current score of the player from the scoring object in order to set the score in the statistics table of the scoring object which will then notify the observer
		int score = sc->get_score(*_villageBoard);
		sc->set_score(*position, score);
	}

	return status;

}

BuildingTile* Player::pickFromBuildingPool(BuildingPool& pool, int index) {
	BuildingTile* drawn_card = pool.pickBuildingTile(index);
	addBuildingTile(*drawn_card);
	return drawn_card;
}

unsigned long Player::getNumberOfBuildingTiles() {
	return _buildingTiles->size();
}

VGMaps* Player::getVGMaps()
{
	return _villageBoard;
}

void Player::ressourceTracker() {
	cout << "--Player Resources--" << endl;
	cout << "Number of Building Tiles: " << getNumberOfBuildingTiles() << endl;
	cout << "Number of Harvest Tiles: " << getNumberOfHarvestTiles() << endl << endl;
	cout << "Building Tiles: " << endl;
	getBuildings();
	cout << endl << "Harvest Tiles: " << endl;
	getHarvestTiles();
	cout << "-- END --" << endl << endl;
}


int Player::getID()
{
		return *ID;

}

void Player::setID(int n, int index)
{
	*ID = n;
	sc->set_id(*position, n);
}

VGMaps* Player::getVGBoard()
{
	return _villageBoard;

}

HarvestTile* Player::getShipmentTile()
{
	return shipmentTile;
}

int Player::getScore()
{ 
	return _villageBoard->getScore();
}

int Player::getPosition()
{
	return *position;
}
