#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <algorithm>

#include "Resources.h"
#include "Dictionary.h"
#include "../player/player.h"
#include "../Scoring/Scoring.h"

using namespace std;

static bool _firstBuilding = true;

BuildingPool::BuildingPool(BuildingDeck* inBuildingDeck) {
	buildingDeck = inBuildingDeck;
	for (int i = 0; i < size; i++) {
		buildingPoolArr[i] = buildingDeck->draw();
	}
}

BuildingTile* BuildingPool::pickBuildingTile(int index) {
	BuildingTile* returnTile =  buildingPoolArr[index];
	buildingPoolArr[index] = buildingDeck->draw();
	return returnTile;
}

BuildingTile**  BuildingPool::getBuildingPool() {
	return buildingPoolArr;
}


HarvestTile::HarvestTile(ResourceName topLeftRes, ResourceName topRightRes, ResourceName bottomLeftRes, ResourceName bottomRightRes)
{
	resourceArr = new ResourceName[4] {topLeftRes, topRightRes, bottomLeftRes, bottomRightRes};
}

HarvestTile::HarvestTile(const HarvestTile &harvestTile) {
    resourceArr = harvestTile.resourceArr;
}

HarvestTile::~HarvestTile() {
	delete[] resourceArr;
    resourceArr = nullptr;
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
	_buildingColorType = new BuildingColorType(BuildingColorType::None);
	_buildingStatus = new BuildingStatus(BuildingStatus::Normal);
	_buildingNum = new int(1);

	_firstBuilding = false;
}


BuildingTile::BuildingTile(BuildingColorType* type, BuildingStatus* status)
{
	cout << "Constructor with random number generator" << endl;
	_buildingColorType = new BuildingColorType(*type);
	_buildingStatus = new BuildingStatus(*status);
	_buildingNum = &(*generateBuildingNumber());
	//*_buildingStatus = status;
	//_buildingNum = generateBuildingNumber();

	_firstBuilding = false;
}

BuildingTile::BuildingTile(BuildingColorType* t, int* n, BuildingStatus* s)
{

	_buildingColorType = new BuildingColorType(*t);

	if (numCheck(*n))
	{
		_buildingNum = new int(*n);
	}
	else
	{
		cerr << "Error in assigning value. Please assign a number between 1 to 6" << endl;
	}
	_buildingStatus = new BuildingStatus(*s);

	_firstBuilding = false;
}

/*
BuildingTile::BuildingTile(const BuildingColorType t, const int n, const BuildingStatus s)
{
	*_buildingColorType = t;
	*_buildingNum = n;
	*_buildingStatus = s;
	_firstBuilding = false;
*/

BuildingTile::BuildingTile(BuildingColorType t, int n, BuildingStatus s)
{
	_buildingColorType = new BuildingColorType(t);
	if (numCheck(n))
	{
		_buildingNum = new int(n);
	}
	else
	{
		cerr << "Error in assigning value. Please assign a number between 1 to 6" << endl;
	}
	_buildingStatus = new BuildingStatus(s);

}

BuildingTile::~BuildingTile() {
	delete _buildingColorType;
	cout << "1 \n";
	delete _buildingNum;
//	cout << "2 \n";
	delete _buildingStatus;
//	cout << "3 \n";

	//cout << "Make all 3 pointer variables to null"; 




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


int* BuildingTile::generateBuildingNumber() {
	if (_firstBuilding)
	{
		srand(time(NULL));  //set the seed first
	}
	//    cout << "Randomizing" << endl;
	int* random = new int(rand() % 6 + 1); //generate a random number from 1 to 6                                                                              //srand and seed it...
	//int rando = rand() % 6 + 1; //generate a random number from 1 to 6
	//int* random = &rando; //generate a random number from 1 to 6
	return random;
}

void BuildingTile::setBuildingNum(int num) {

	// do I need to check if it exists 
	if (numCheck(num))
	{
		*_buildingNum = num; //dereference and change it
	}
	else
	{
		cerr << "Error in assigning value. Please assign a number between 1 to 6" << endl;
	}

}

bool BuildingTile::numCheck(int num)
{
	//if number is good - return true
	if ((num >= 1) || (num <= 6))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BuildingTile::setBuildingStatus(BuildingStatus s)
{
	*_buildingStatus = s;
}

void BuildingTile::setBuildingColorType(BuildingColorType c)
{
	*_buildingColorType = c;
}

void BuildingTile::flip() {

	if (getSide() == BuildingStatus::Normal) {
		setBuildingNum(-1);
		setBuildingStatus(BuildingStatus::Flipped);
	}
	//cannot flip back

}

void BuildingTile::deepCopy(const BuildingTile& t)
{

	delete _buildingColorType;

	if (t._buildingColorType)
	{
		_buildingColorType = new BuildingColorType(*t._buildingColorType);
	}
	else
	{
		_buildingColorType = nullptr;
	}

	delete _buildingNum;

	if (t._buildingNum)
	{
		_buildingNum = new int(*t._buildingNum);
	}
	else
	{
		_buildingNum = nullptr;
	}

	delete _buildingStatus;

	if (t._buildingStatus)
	{
		_buildingStatus = new BuildingStatus(*t._buildingStatus);

	}
	else
	{
		_buildingStatus = nullptr;
	}

	cout << "Success in deep copying" << endl;
}

BuildingTile::BuildingTile(const BuildingTile& t) : _buildingColorType{ nullptr }, _buildingNum{ nullptr }, _buildingStatus{ nullptr }
{
	deepCopy(t);
}

//Assignment operator for deep copy 
BuildingTile& BuildingTile:: operator = (const BuildingTile& b)
{
	cout << "Inside deep copy assignment operator " << endl;
	if (this == &b) //self-guarding 
	{
		return *this;
	}
	deepCopy(b);
	return *this;
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

HarvestDeck::~HarvestDeck()
{
	
	for (int i = 0; i < deckLength; i++) {
		delete harvestDeck[i];
	}
	delete[] harvestDeck;

}

int HarvestDeck::getSize() {
    return deckLength;
}

HarvestTile* HarvestDeck::draw() {
	//use random numbers each draw rather than "shuffling" the deck at the beginning of the game and putting it into a stack
	//srand(0); //hardcoded the seed, for test purposes
	srand((unsigned)time(NULL));
	int randomNumber = rand() % deckLength;

	HarvestTile* temp = harvestDeck[randomNumber];

	//deckLength decreases by one as a card is drawn out of the deck
	deckLength--;

	//loop shuffles pointers down to keep remaining HarvestTiles together at the "top" of the deck
	//subtract one again from deckLength to prevent index out of bounds errors
	for (int i = randomNumber; i < deckLength; i++) {
		harvestDeck[i] = harvestDeck[i+1];
	}

	harvestDeck[deckLength] = NULL;

	return temp;
}

BuildingDeck::BuildingDeck() {
	//    cout << "Creating BuildingDeck with Main: " << this << endl;

		// Initializing deck size
	int size = 144;
	_sizeMax = &size;

	// Initialize deck resources
	BuildingColorType greenSheep = BuildingColorType::GreenSheep;
	BuildingColorType greyRock = BuildingColorType::GreyRock;
	BuildingColorType redLumber = BuildingColorType::RedLumber;
	BuildingColorType yellowHay = BuildingColorType::YellowHay;

	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;

	BuildingStatus normal = BuildingStatus::Normal;

	// Deck: 6 x 4 x 6
	BuildingTile* tiles[144] = {
		new BuildingTile(&greenSheep, &num1, &normal),
		new BuildingTile(&greenSheep, &num2, &normal),
		new BuildingTile(&greenSheep, &num3, &normal),
		new BuildingTile(&greenSheep, &num4, &normal),
		new BuildingTile(&greenSheep, &num5, &normal),
		new BuildingTile(&greenSheep, &num6, &normal),
		new BuildingTile(&greyRock, &num1, &normal),
		new BuildingTile(&greyRock, &num2, &normal),
		new BuildingTile(&greyRock, &num3, &normal),
		new BuildingTile(&greyRock, &num4, &normal),
		new BuildingTile(&greyRock, &num5, &normal),
		new BuildingTile(&greyRock, &num6, &normal),
		new BuildingTile(&redLumber, &num1, &normal),
		new BuildingTile(&redLumber, &num2, &normal),
		new BuildingTile(&redLumber, &num3, &normal),
		new BuildingTile(&redLumber, &num4, &normal),
		new BuildingTile(&redLumber, &num5, &normal),
		new BuildingTile(&redLumber, &num6, &normal),
		new BuildingTile(&yellowHay, &num1, &normal),
		new BuildingTile(&yellowHay, &num2, &normal),
		new BuildingTile(&yellowHay, &num3, &normal),
		new BuildingTile(&yellowHay, &num4, &normal),
		new BuildingTile(&yellowHay, &num5, &normal),
		new BuildingTile(&yellowHay, &num6, &normal),

		new BuildingTile(&greenSheep, &num1, &normal),
		new BuildingTile(&greenSheep, &num2, &normal),
		new BuildingTile(&greenSheep, &num3, &normal),
		new BuildingTile(&greenSheep, &num4, &normal),
		new BuildingTile(&greenSheep, &num5, &normal),
		new BuildingTile(&greenSheep, &num6, &normal),
		new BuildingTile(&greyRock, &num1, &normal),
		new BuildingTile(&greyRock, &num2, &normal),
		new BuildingTile(&greyRock, &num3, &normal),
		new BuildingTile(&greyRock, &num4, &normal),
		new BuildingTile(&greyRock, &num5, &normal),
		new BuildingTile(&greyRock, &num6, &normal),
		new BuildingTile(&redLumber, &num1, &normal),
		new BuildingTile(&redLumber, &num2, &normal),
		new BuildingTile(&redLumber, &num3, &normal),
		new BuildingTile(&redLumber, &num4, &normal),
		new BuildingTile(&redLumber, &num5, &normal),
		new BuildingTile(&redLumber, &num6, &normal),
		new BuildingTile(&yellowHay, &num1, &normal),
		new BuildingTile(&yellowHay, &num2, &normal),
		new BuildingTile(&yellowHay, &num3, &normal),
		new BuildingTile(&yellowHay, &num4, &normal),
		new BuildingTile(&yellowHay, &num5, &normal),
		new BuildingTile(&yellowHay, &num6, &normal),

		new BuildingTile(&greenSheep, &num1, &normal),
		new BuildingTile(&greenSheep, &num2, &normal),
		new BuildingTile(&greenSheep, &num3, &normal),
		new BuildingTile(&greenSheep, &num4, &normal),
		new BuildingTile(&greenSheep, &num5, &normal),
		new BuildingTile(&greenSheep, &num6, &normal),
		new BuildingTile(&greyRock, &num1, &normal),
		new BuildingTile(&greyRock, &num2, &normal),
		new BuildingTile(&greyRock, &num3, &normal),
		new BuildingTile(&greyRock, &num4, &normal),
		new BuildingTile(&greyRock, &num5, &normal),
		new BuildingTile(&greyRock, &num6, &normal),
		new BuildingTile(&redLumber, &num1, &normal),
		new BuildingTile(&redLumber, &num2, &normal),
		new BuildingTile(&redLumber, &num3, &normal),
		new BuildingTile(&redLumber, &num4, &normal),
		new BuildingTile(&redLumber, &num5, &normal),
		new BuildingTile(&redLumber, &num6, &normal),
		new BuildingTile(&yellowHay, &num1, &normal),
		new BuildingTile(&yellowHay, &num2, &normal),
		new BuildingTile(&yellowHay, &num3, &normal),
		new BuildingTile(&yellowHay, &num4, &normal),
		new BuildingTile(&yellowHay, &num5, &normal),
		new BuildingTile(&yellowHay, &num6, &normal),

		new BuildingTile(&greenSheep, &num1, &normal),
		new BuildingTile(&greenSheep, &num2, &normal),
		new BuildingTile(&greenSheep, &num3, &normal),
		new BuildingTile(&greenSheep, &num4, &normal),
		new BuildingTile(&greenSheep, &num5, &normal),
		new BuildingTile(&greenSheep, &num6, &normal),
		new BuildingTile(&greyRock, &num1, &normal),
		new BuildingTile(&greyRock, &num2, &normal),
		new BuildingTile(&greyRock, &num3, &normal),
		new BuildingTile(&greyRock, &num4, &normal),
		new BuildingTile(&greyRock, &num5, &normal),
		new BuildingTile(&greyRock, &num6, &normal),
		new BuildingTile(&redLumber, &num1, &normal),
		new BuildingTile(&redLumber, &num2, &normal),
		new BuildingTile(&redLumber, &num3, &normal),
		new BuildingTile(&redLumber, &num4, &normal),
		new BuildingTile(&redLumber, &num5, &normal),
		new BuildingTile(&redLumber, &num6, &normal),
		new BuildingTile(&yellowHay, &num1, &normal),
		new BuildingTile(&yellowHay, &num2, &normal),
		new BuildingTile(&yellowHay, &num3, &normal),
		new BuildingTile(&yellowHay, &num4, &normal),
		new BuildingTile(&yellowHay, &num5, &normal),
		new BuildingTile(&yellowHay, &num6, &normal),

		new BuildingTile(&greenSheep, &num1, &normal),
		new BuildingTile(&greenSheep, &num2, &normal),
		new BuildingTile(&greenSheep, &num3, &normal),
		new BuildingTile(&greenSheep, &num4, &normal),
		new BuildingTile(&greenSheep, &num5, &normal),
		new BuildingTile(&greenSheep, &num6, &normal),
		new BuildingTile(&greyRock, &num1, &normal),
		new BuildingTile(&greyRock, &num2, &normal),
		new BuildingTile(&greyRock, &num3, &normal),
		new BuildingTile(&greyRock, &num4, &normal),
		new BuildingTile(&greyRock, &num5, &normal),
		new BuildingTile(&greyRock, &num6, &normal),
		new BuildingTile(&redLumber, &num1, &normal),
		new BuildingTile(&redLumber, &num2, &normal),
		new BuildingTile(&redLumber, &num3, &normal),
		new BuildingTile(&redLumber, &num4, &normal),
		new BuildingTile(&redLumber, &num5, &normal),
		new BuildingTile(&redLumber, &num6, &normal),
		new BuildingTile(&yellowHay, &num1, &normal),
		new BuildingTile(&yellowHay, &num2, &normal),
		new BuildingTile(&yellowHay, &num3, &normal),
		new BuildingTile(&yellowHay, &num4, &normal),
		new BuildingTile(&yellowHay, &num5, &normal),
		new BuildingTile(&yellowHay, &num6, &normal),

		new BuildingTile(&greenSheep, &num1, &normal),
		new BuildingTile(&greenSheep, &num2, &normal),
		new BuildingTile(&greenSheep, &num3, &normal),
		new BuildingTile(&greenSheep, &num4, &normal),
		new BuildingTile(&greenSheep, &num5, &normal),
		new BuildingTile(&greenSheep, &num6, &normal),
		new BuildingTile(&greyRock, &num1, &normal),
		new BuildingTile(&greyRock, &num2, &normal),
		new BuildingTile(&greyRock, &num3, &normal),
		new BuildingTile(&greyRock, &num4, &normal),
		new BuildingTile(&greyRock, &num5, &normal),
		new BuildingTile(&greyRock, &num6, &normal),
		new BuildingTile(&redLumber, &num1, &normal),
		new BuildingTile(&redLumber, &num2, &normal),
		new BuildingTile(&redLumber, &num3, &normal),
		new BuildingTile(&redLumber, &num4, &normal),
		new BuildingTile(&redLumber, &num5, &normal),
		new BuildingTile(&redLumber, &num6, &normal),
		new BuildingTile(&yellowHay, &num1, &normal),
		new BuildingTile(&yellowHay, &num2, &normal),
		new BuildingTile(&yellowHay, &num3, &normal),
		new BuildingTile(&yellowHay, &num4, &normal),
		new BuildingTile(&yellowHay, &num5, &normal),
		new BuildingTile(&yellowHay, &num6, &normal),
	};

	// Initializing _deck vector
	_deck = new vector<BuildingTile*>;

	for (int i = 0; i < *_sizeMax; i++) {
		//        cout << "Adding tile: " << &tiles[i] << endl;
		_deck->push_back(tiles[i]);
	}

}

BuildingDeck::BuildingDeck(const BuildingDeck& deck) {

}

BuildingDeck::~BuildingDeck() {

	if (_deck) {

		for (vector<BuildingTile*>::iterator it = _deck->begin(); it != _deck->end(); ++it) {
			delete *it;
			*it = nullptr;
		}

		//        cout << "Deleting _deck of BuildingTile with address: " << this << endl;
		delete _deck;
		_deck = nullptr;
		//        cout << "DONE" << endl;
	}
}

vector<BuildingTile*>* BuildingDeck::getDeck() {
	return _deck;
}

void BuildingDeck::add(BuildingTile& tile) {
	//    cout << "Adding: " << &tile << endl;
	_deck->push_back(&tile);
}


void BuildingDeck::remove(BuildingTile& tile) {
	_deck->erase(std::remove(_deck->begin(), _deck->end(), &tile), _deck->end());
}


BuildingTile* BuildingDeck::draw() {
	if (_deck->size() > 0) {
		int randomIndex = rand() % _deck->size();
		BuildingTile* tile = _deck->at(randomIndex);
		remove(*tile);
		return tile;
	}
	else {
		return nullptr;
	}
}

unsigned long BuildingDeck::getSize() {
	return _deck->size();
}


Hand::Hand(Scoring* inSc) {
	sc = inSc;
	resourceScoreArr = new int[4] { 0, 0, 0, 0};
}

void Hand::intializeHand()
{	
	resourceScoreArr[static_cast<int>(ResourceName::Lumber)-1] = sc->get_lumber();
	resourceScoreArr[static_cast<int>(ResourceName::Rock)-1] = sc->get_stone();
	resourceScoreArr[static_cast<int>(ResourceName::Wheat)-1] = sc->get_wheat();
	resourceScoreArr[static_cast<int>(ResourceName::Sheep)-1] = sc->get_sheep();
}

void Hand::displayHand() {

	for (int i = 1; i < 5; i++) {
		cout << HarvestTile::ResourceNameToString(static_cast<ResourceName>(i)) << ": " << resourceScoreArr[i-1]<<" ";
	}
}

int Hand::exchange(ExchangeToken* exchangeToken) {
	Player* player = exchangeToken->getPlayer();
	BuildingTile* buildingTile = exchangeToken->getBT();
	int row = exchangeToken->getRow();
	int column = exchangeToken->getCol();
	int index;

	// get index for resourceScoreArr
	switch (buildingTile->getBuildingColorType()) {

	case BuildingColorType::GreenSheep:
			index = static_cast<int>(ResourceName::Sheep);
			break;
		case BuildingColorType::GreyRock:
			index = static_cast<int>(ResourceName::Rock);
			break;
		case BuildingColorType::RedLumber:
			index = static_cast<int>(ResourceName::Lumber);
			break;
		case BuildingColorType::YellowHay:
			index = static_cast<int>(ResourceName::Wheat);
			break;
		}

	//enum goes from 1-4 but array is 0-3
	index -= 1;

	// verify there are enough resources to add the building tile
	if (resourceScoreArr[index] < buildingTile->getBuildingNum()) {
		return 1;
	}

	player->removeBuildingTile(*buildingTile);
	VGMaps* playersVGBoard = player->getVGBoard();

	// add buildingTile and decrement resource score
	if (playersVGBoard->addNewBuildingTile(*buildingTile, row, column) == 0) {
			resourceScoreArr[index] -= buildingTile->getBuildingNum();
			return 0;
	}
	else {
		player->addBuildingTile(*buildingTile);
		return 2;
	}

}

Hand::ExchangeToken::ExchangeToken(Player* inP, BuildingTile* inBT, int inR, int inC)
{
		player = inP;
		buildingTile = inBT;
		row = inR;
		column = inC;
}

Player* Hand::ExchangeToken::getPlayer()
{
	return player;
}

BuildingTile* Hand::ExchangeToken::getBT()
{
	return buildingTile;
}

int Hand::ExchangeToken::getRow()
{
	return row;
}

int Hand::ExchangeToken::getCol()
{
	return column;
}
