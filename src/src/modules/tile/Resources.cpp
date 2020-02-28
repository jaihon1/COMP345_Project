#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include "Resources.h"
#include "Dictionary.h"

using namespace std;

static bool _firstBuilding = true;


HarvestTile::HarvestTile(ResourceName topLeftRes, ResourceName topRightRes, ResourceName bottomLeftRes, ResourceName bottomRightRes)
{
	cout << "Creating HarvestTile with Main: " << this << endl;
	resourceArr = new ResourceName[4] {topLeftRes, topRightRes, bottomLeftRes, bottomRightRes};
}

HarvestTile::HarvestTile(const HarvestTile &harvestTile) {
    cout << "Creating HarvestTile with copy: " << this << endl;
    resourceArr = harvestTile.resourceArr;
}

HarvestTile::~HarvestTile() {
    cout << "Deleting HarvestTile with address: " << this << endl;
	delete[] resourceArr;
    resourceArr = nullptr;
    cout << "DONE" << endl;
}

void HarvestTile::RotateLeft()
{
	ResourceName temp = resourceArr[topLeft];

	resourceArr[topLeft] = resourceArr[topRight];
	resourceArr[topRight] = resourceArr[bottomRight];
	resourceArr[bottomRight] = resourceArr[bottomLeft];
	resourceArr[bottomLeft] = temp;
	
}

void HarvestTile::RotateRight()
{
	ResourceName temp = resourceArr[topLeft];

	resourceArr[topLeft] = resourceArr[bottomLeft];
	resourceArr[bottomLeft] = resourceArr[bottomRight];
	resourceArr[bottomRight] = resourceArr[topRight];
	resourceArr[topRight] = temp;

}

ResourceName HarvestTile::getResource(ResourceLocation inLocation)
{
	return resourceArr[inLocation];
}

BuildingTile::BuildingTile()
{
    //
    _firstBuilding = false;
}

BuildingTile::BuildingTile(BuildingColorType *type, BuildingStatus *status) : _buildingColorType(type), _buildingStatus(status), _buildingNum(generateBuildingNumber())
{
    //*_buildingColorType = type;
    //*_buildingStatus = status;
    //_buildingNum = generateBuildingNumber();

    _firstBuilding = false;
}

BuildingTile::BuildingTile(BuildingColorType *t, int *n, BuildingStatus *s): _buildingColorType(t), _buildingNum(n), _buildingStatus(s)
{
    /*
    _buildingColorType = t;
    _buildingNum = n;
    _buildingStatus = s;
    */
    _firstBuilding = false;
}

BuildingTile::BuildingTile(BuildingColorType t, int n, BuildingStatus s)
{
	*_buildingColorType = t;
	*_buildingNum = n;
	*_buildingStatus = s;
}

BuildingTile::~BuildingTile() {
    //do I need to code?
    //if the member variables dont go on the stack, make them dynamic objects and delete every
    //random to delete
    //delete _int

//    cout << "in destr" << endl;
//    delete _buildingColorType;
//    _buildingColorType = NULL;
//    delete _buildingStatus;
//    _buildingStatus = NULL;

    //delete _buildingNum;
    //_buildingNum = NULL;

}

BuildingColorType BuildingTile::getBuildingColorType() {
    return *_buildingColorType;
}

BuildingStatus BuildingTile::getSide() {
    return *_buildingStatus;
}

int BuildingTile::getBuildingNum() {
    return *_buildingNum;
}


int *BuildingTile::generateBuildingNumber() {
    if (_firstBuilding)
    {
        srand(time(NULL));  //set the seed first
    }
    cout << "Randomizing" << endl;
    int* random = new int(rand() % 6 + 1); //generate a random number from 1 to 6                                                                              //srand and seed it...
    //int rando = rand() % 6 + 1; //generate a random number from 1 to 6
    //int* random = &rando; //generate a random number from 1 to 6
    return random;
}

void BuildingTile::setBuildingNum(int num) {
    *_buildingNum = num;
}

void BuildingTile::setBuildingStatus(BuildingStatus s)
{
    *_buildingStatus = s;
}

void BuildingTile::flip() {
    if (getSide() == BuildingStatus::Normal) {
        setBuildingNum(-1);
        setBuildingStatus(BuildingStatus::Flipped);
    }
    //cannot flip back

}


HarvestDeck::HarvestDeck()
{
	harvestDeck = new HarvestTile*[deckLength]{
		//IMG-1
		new HarvestTile(ResourceName::Wheat, ResourceName::Lumber, ResourceName::Wheat, ResourceName::Sheep),
		new HarvestTile(ResourceName::Sheep, ResourceName::Sheep, ResourceName::Sheep, ResourceName::Rock),
		new HarvestTile(ResourceName::Lumber, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Sheep),
		new HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Rock),

		new HarvestTile(ResourceName::Sheep, ResourceName::Sheep, ResourceName::Sheep, ResourceName::Wheat),
		new HarvestTile(ResourceName::Rock, ResourceName::Wheat, ResourceName::Rock, ResourceName::Lumber),
		new HarvestTile(ResourceName::Rock, ResourceName::Sheep, ResourceName::Rock, ResourceName::Wheat),
		new HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Sheep, ResourceName::Lumber),

		new HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Sheep, ResourceName::Wheat),
		new HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Wheat, ResourceName::Sheep),
		new HarvestTile(ResourceName::Wheat, ResourceName::Wheat, ResourceName::Wheat, ResourceName::Lumber),
		new HarvestTile(ResourceName::Rock, ResourceName::Lumber, ResourceName::Rock, ResourceName::Wheat),

		new HarvestTile(ResourceName::Wheat, ResourceName::Wheat, ResourceName::Wheat, ResourceName::Rock),
		new HarvestTile(ResourceName::Wheat, ResourceName::Wheat, ResourceName::Wheat, ResourceName::Sheep),
		new HarvestTile(ResourceName::Lumber, ResourceName::Lumber, ResourceName::Lumber, ResourceName::Wheat),
		new HarvestTile(ResourceName::Lumber, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Wheat),

		new HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Lumber),
		new HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat),
		new HarvestTile(ResourceName::Rock, ResourceName::Rock, ResourceName::Rock, ResourceName::Lumber),
		new HarvestTile(ResourceName::Rock, ResourceName::Wheat, ResourceName::Rock, ResourceName::Sheep),

		//IMG-2
		new HarvestTile(ResourceName::Rock, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Rock),
		new HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Lumber, ResourceName::Lumber),
		new HarvestTile(ResourceName::Sheep, ResourceName::Lumber, ResourceName::Sheep, ResourceName::Rock),
		new HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Sheep, ResourceName::Rock),

		new HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Lumber, ResourceName::Wheat),
		new HarvestTile(ResourceName::Lumber, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Rock),
		new HarvestTile(ResourceName::Rock, ResourceName::Rock, ResourceName::Rock, ResourceName::Wheat),
		new HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Lumber, ResourceName::Sheep),

		new HarvestTile(ResourceName::Rock, ResourceName::Lumber, ResourceName::Rock, ResourceName::Sheep),
		new HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Sheep, ResourceName::Rock),
		new HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Wheat, ResourceName::Rock),
		new HarvestTile(ResourceName::Sheep, ResourceName::Sheep, ResourceName::Sheep, ResourceName::Lumber),

		new HarvestTile(ResourceName::Lumber, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Sheep),
		new HarvestTile(ResourceName::Lumber, ResourceName::Lumber, ResourceName::Lumber, ResourceName::Sheep),
		new HarvestTile(ResourceName::Sheep, ResourceName::Lumber, ResourceName::Sheep, ResourceName::Wheat),
		new HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Lumber, ResourceName::Rock),

		new HarvestTile(ResourceName::Lumber, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Wheat),
		new HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Wheat, ResourceName::Rock),
		new HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Lumber, ResourceName::Wheat),
		new HarvestTile(ResourceName::Rock, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Rock),

		//IMG-3
		new HarvestTile(ResourceName::Rock, ResourceName::Rock, ResourceName::Rock, ResourceName::Sheep),
		new HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Sheep, ResourceName::Lumber),
		new HarvestTile(ResourceName::Wheat, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Wheat),
		new HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Sheep),

		new HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Wheat, ResourceName::Lumber),
		new HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Wheat, ResourceName::Lumber),
		new HarvestTile(ResourceName::Lumber, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Wheat),
		new HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Wheat, ResourceName::Sheep),

		new HarvestTile(ResourceName::Rock, ResourceName::Sheep, ResourceName::Rock, ResourceName::Lumber),
		new HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat),
		new HarvestTile(ResourceName::Rock, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Rock),
		new HarvestTile(ResourceName::Lumber, ResourceName::Lumber, ResourceName::Lumber, ResourceName::Rock),

		new HarvestTile(ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat, ResourceName::Lumber),
		new HarvestTile(ResourceName::Lumber, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Sheep),
		new HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Sheep, ResourceName::Wheat),
		new HarvestTile(ResourceName::Lumber, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Lumber),

		new HarvestTile(ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat, ResourceName::Rock),
		new HarvestTile(ResourceName::Wheat, ResourceName::Lumber, ResourceName::Wheat, ResourceName::Rock),
		new HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Lumber, ResourceName::Sheep),
		new HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Lumber, ResourceName::Rock)
	};
}

int HarvestDeck::getSize() {
    return deckLength;
}

HarvestTile* HarvestDeck::draw() {
	//use random numbers each draw rather than "shuffling" the deck at the beginning of the game and putting it into a stack
	srand(0); //TODO: hardcoded the seed, need to change to seeding with time from clock
	int randomNumber = rand() % deckLength;

	HarvestTile* temp = harvestDeck[randomNumber];
	
	//deckLength decreases by one as a card is drawn out of the deck
	deckLength--;

	//loop shuffles pointers down to keep remaining HarvestTiles together at the "top" of the deck
	//subtract one again from deckLength to prevent index out of bounds errors
	for (int i = randomNumber; i < deckLength-1; i++) {
		harvestDeck[i] = harvestDeck[i+1];
	}

	harvestDeck[deckLength] = NULL;

	return temp;
}

BuildingDeck::BuildingDeck() {
    cout << "Creating BuildingDeck with Main: " << this << endl;
    
    // Initializing deck size
    int size = 9;
    _sizeMax = &size;
    
    // Initialize deck resources
    BuildingColorType greenSheep = BuildingColorType::GreenSheep;
    BuildingColorType greyRock = BuildingColorType::GreyRock;
    BuildingColorType redLumber = BuildingColorType::RedLumber;
    BuildingColorType yellowHay = BuildingColorType::YellowHay;
    
    BuildingStatus normal = BuildingStatus::Normal;
    
    BuildingTile tiles[9] = {
        BuildingTile(&greenSheep, &normal),
        BuildingTile(&greyRock, &normal),
        BuildingTile(&redLumber, &normal),
        BuildingTile(&yellowHay, &normal),
        BuildingTile(&greenSheep, &normal),
        BuildingTile(&greenSheep, &normal),
        BuildingTile(&greyRock, &normal),
        BuildingTile(&redLumber, &normal),
        BuildingTile(&yellowHay, &normal)
    };
    
    // Initializing _deck vector
    _deck = new vector<BuildingTile*>;
    
    for (int i = 0; i < *_sizeMax; i++) {
        cout << "Adding tile: " << &tiles[i] << endl;
        _deck -> push_back(&tiles[i]);
    }
    
}

BuildingDeck::BuildingDeck(const BuildingDeck &deck) {
    
}

BuildingDeck::~BuildingDeck() {
    if (_deck) {
        cout << "Deleting _deck of BuildingTile with address: " << this << endl;
        delete _deck;
        _deck = nullptr;
        cout << "DONE" << endl;
    }
}

vector<BuildingTile*>* BuildingDeck::getDeck() {
    return _deck;
}

void BuildingDeck::add(BuildingTile &tile) {
    cout << "Adding: " << &tile << endl;
    _deck -> push_back(&tile);
}


void BuildingDeck::remove(BuildingTile &tile) {
    _deck -> erase(std::remove(_deck -> begin(), _deck -> end(), &tile), _deck -> end());
}


BuildingTile* BuildingDeck::draw() {
    if (_deck -> size() > 0) {
        int randomIndex = rand() % _deck -> size();
        BuildingTile *tile = _deck -> at(randomIndex);
        remove(*tile);
        return tile;
    }
    else {
        return nullptr;
    }
}

unsigned long BuildingDeck::getSize() {
    return _deck -> size();
}

