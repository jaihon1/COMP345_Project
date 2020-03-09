#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <algorithm>

#include "Resources.h"
#include "Dictionary.h"
#include "../Scoring/Scoring.h"

using namespace std;

static bool _firstBuilding = true;


HarvestTile::HarvestTile(ResourceName topLeftRes, ResourceName topRightRes, ResourceName bottomLeftRes, ResourceName bottomRightRes)
{
	resourceArr = new ResourceName[4]{ topLeftRes, topRightRes, bottomLeftRes, bottomRightRes };
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
	//*_buildingColorType = BuildingColorType::None; 
	//*_buildingStatus = BuildingStatus::Normal; 
	//*_buildingNum = 0; 

	_firstBuilding = false;
}

BuildingTile::BuildingTile(BuildingColorType* type, BuildingStatus* status) : _buildingColorType(type), _buildingStatus(status), _buildingNum(generateBuildingNumber())
{
	//*_buildingColorType = type;
	//*_buildingStatus = status;
	//_buildingNum = generateBuildingNumber();

	_firstBuilding = false;
}

BuildingTile::BuildingTile(BuildingColorType* t, int* n, BuildingStatus* s) : _buildingColorType(t), _buildingNum(n), _buildingStatus(s)
{
	/*
	_buildingColorType = t;
	_buildingNum = n;
	_buildingStatus = s;
	*/
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
	cout << "inside constructor" << endl; 
	*_buildingColorType = t;
	if (numCheck(n))
	{
		*_buildingNum = n;
	}
	else
	{
		cerr << "Error in assigning value. Please assign a number between 1 to 6" << endl;
	}
	*_buildingStatus = s;

}

BuildingTile::~BuildingTile() {

	//if the member variables dont go on the stack, make them dynamic objects and delete every
	//random to delete
	//delete _int

	cout << "in destr" << endl;

	
	delete _buildingColorType;
	//_buildingColorType = NULL;
	delete _buildingStatus;
	//_buildingStatus = NULL;
	delete _buildingNum;
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
	if (numCheck(num))
	{
		*_buildingNum = num;
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
}

BuildingTile::BuildingTile(const BuildingTile& t) : _buildingColorType{ nullptr }, _buildingNum{ nullptr }, _buildingStatus{ nullptr }
{
	deepCopy(t);
}

//Assignment operator for deep copy 
BuildingTile &BuildingTile:: operator = (const BuildingTile &b)
{
	if (this == &b) //self-guarding 
	{
		return *this; 
	}
	deepCopy(b);
	return *this; 
}

HarvestDeck::HarvestDeck()
{
	harvestDeck = new HarvestTile*[deckLength] {
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
		harvestDeck[i] = harvestDeck[i + 1];
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
	BuildingTile tiles[144] = {
		BuildingTile(&greenSheep, &num1, &normal),
		BuildingTile(&greenSheep, &num2, &normal),
		BuildingTile(&greenSheep, &num3, &normal),
		BuildingTile(&greenSheep, &num4, &normal),
		BuildingTile(&greenSheep, &num5, &normal),
		BuildingTile(&greenSheep, &num6, &normal),
		BuildingTile(&greyRock, &num1, &normal),
		BuildingTile(&greyRock, &num2, &normal),
		BuildingTile(&greyRock, &num3, &normal),
		BuildingTile(&greyRock, &num4, &normal),
		BuildingTile(&greyRock, &num5, &normal),
		BuildingTile(&greyRock, &num6, &normal),
		BuildingTile(&redLumber, &num1, &normal),
		BuildingTile(&redLumber, &num2, &normal),
		BuildingTile(&redLumber, &num3, &normal),
		BuildingTile(&redLumber, &num4, &normal),
		BuildingTile(&redLumber, &num5, &normal),
		BuildingTile(&redLumber, &num6, &normal),
		BuildingTile(&yellowHay, &num1, &normal),
		BuildingTile(&yellowHay, &num2, &normal),
		BuildingTile(&yellowHay, &num3, &normal),
		BuildingTile(&yellowHay, &num4, &normal),
		BuildingTile(&yellowHay, &num5, &normal),
		BuildingTile(&yellowHay, &num6, &normal),

		BuildingTile(&greenSheep, &num1, &normal),
		BuildingTile(&greenSheep, &num2, &normal),
		BuildingTile(&greenSheep, &num3, &normal),
		BuildingTile(&greenSheep, &num4, &normal),
		BuildingTile(&greenSheep, &num5, &normal),
		BuildingTile(&greenSheep, &num6, &normal),
		BuildingTile(&greyRock, &num1, &normal),
		BuildingTile(&greyRock, &num2, &normal),
		BuildingTile(&greyRock, &num3, &normal),
		BuildingTile(&greyRock, &num4, &normal),
		BuildingTile(&greyRock, &num5, &normal),
		BuildingTile(&greyRock, &num6, &normal),
		BuildingTile(&redLumber, &num1, &normal),
		BuildingTile(&redLumber, &num2, &normal),
		BuildingTile(&redLumber, &num3, &normal),
		BuildingTile(&redLumber, &num4, &normal),
		BuildingTile(&redLumber, &num5, &normal),
		BuildingTile(&redLumber, &num6, &normal),
		BuildingTile(&yellowHay, &num1, &normal),
		BuildingTile(&yellowHay, &num2, &normal),
		BuildingTile(&yellowHay, &num3, &normal),
		BuildingTile(&yellowHay, &num4, &normal),
		BuildingTile(&yellowHay, &num5, &normal),
		BuildingTile(&yellowHay, &num6, &normal),

		BuildingTile(&greenSheep, &num1, &normal),
		BuildingTile(&greenSheep, &num2, &normal),
		BuildingTile(&greenSheep, &num3, &normal),
		BuildingTile(&greenSheep, &num4, &normal),
		BuildingTile(&greenSheep, &num5, &normal),
		BuildingTile(&greenSheep, &num6, &normal),
		BuildingTile(&greyRock, &num1, &normal),
		BuildingTile(&greyRock, &num2, &normal),
		BuildingTile(&greyRock, &num3, &normal),
		BuildingTile(&greyRock, &num4, &normal),
		BuildingTile(&greyRock, &num5, &normal),
		BuildingTile(&greyRock, &num6, &normal),
		BuildingTile(&redLumber, &num1, &normal),
		BuildingTile(&redLumber, &num2, &normal),
		BuildingTile(&redLumber, &num3, &normal),
		BuildingTile(&redLumber, &num4, &normal),
		BuildingTile(&redLumber, &num5, &normal),
		BuildingTile(&redLumber, &num6, &normal),
		BuildingTile(&yellowHay, &num1, &normal),
		BuildingTile(&yellowHay, &num2, &normal),
		BuildingTile(&yellowHay, &num3, &normal),
		BuildingTile(&yellowHay, &num4, &normal),
		BuildingTile(&yellowHay, &num5, &normal),
		BuildingTile(&yellowHay, &num6, &normal),

		BuildingTile(&greenSheep, &num1, &normal),
		BuildingTile(&greenSheep, &num2, &normal),
		BuildingTile(&greenSheep, &num3, &normal),
		BuildingTile(&greenSheep, &num4, &normal),
		BuildingTile(&greenSheep, &num5, &normal),
		BuildingTile(&greenSheep, &num6, &normal),
		BuildingTile(&greyRock, &num1, &normal),
		BuildingTile(&greyRock, &num2, &normal),
		BuildingTile(&greyRock, &num3, &normal),
		BuildingTile(&greyRock, &num4, &normal),
		BuildingTile(&greyRock, &num5, &normal),
		BuildingTile(&greyRock, &num6, &normal),
		BuildingTile(&redLumber, &num1, &normal),
		BuildingTile(&redLumber, &num2, &normal),
		BuildingTile(&redLumber, &num3, &normal),
		BuildingTile(&redLumber, &num4, &normal),
		BuildingTile(&redLumber, &num5, &normal),
		BuildingTile(&redLumber, &num6, &normal),
		BuildingTile(&yellowHay, &num1, &normal),
		BuildingTile(&yellowHay, &num2, &normal),
		BuildingTile(&yellowHay, &num3, &normal),
		BuildingTile(&yellowHay, &num4, &normal),
		BuildingTile(&yellowHay, &num5, &normal),
		BuildingTile(&yellowHay, &num6, &normal),

		BuildingTile(&greenSheep, &num1, &normal),
		BuildingTile(&greenSheep, &num2, &normal),
		BuildingTile(&greenSheep, &num3, &normal),
		BuildingTile(&greenSheep, &num4, &normal),
		BuildingTile(&greenSheep, &num5, &normal),
		BuildingTile(&greenSheep, &num6, &normal),
		BuildingTile(&greyRock, &num1, &normal),
		BuildingTile(&greyRock, &num2, &normal),
		BuildingTile(&greyRock, &num3, &normal),
		BuildingTile(&greyRock, &num4, &normal),
		BuildingTile(&greyRock, &num5, &normal),
		BuildingTile(&greyRock, &num6, &normal),
		BuildingTile(&redLumber, &num1, &normal),
		BuildingTile(&redLumber, &num2, &normal),
		BuildingTile(&redLumber, &num3, &normal),
		BuildingTile(&redLumber, &num4, &normal),
		BuildingTile(&redLumber, &num5, &normal),
		BuildingTile(&redLumber, &num6, &normal),
		BuildingTile(&yellowHay, &num1, &normal),
		BuildingTile(&yellowHay, &num2, &normal),
		BuildingTile(&yellowHay, &num3, &normal),
		BuildingTile(&yellowHay, &num4, &normal),
		BuildingTile(&yellowHay, &num5, &normal),
		BuildingTile(&yellowHay, &num6, &normal),

		BuildingTile(&greenSheep, &num1, &normal),
		BuildingTile(&greenSheep, &num2, &normal),
		BuildingTile(&greenSheep, &num3, &normal),
		BuildingTile(&greenSheep, &num4, &normal),
		BuildingTile(&greenSheep, &num5, &normal),
		BuildingTile(&greenSheep, &num6, &normal),
		BuildingTile(&greyRock, &num1, &normal),
		BuildingTile(&greyRock, &num2, &normal),
		BuildingTile(&greyRock, &num3, &normal),
		BuildingTile(&greyRock, &num4, &normal),
		BuildingTile(&greyRock, &num5, &normal),
		BuildingTile(&greyRock, &num6, &normal),
		BuildingTile(&redLumber, &num1, &normal),
		BuildingTile(&redLumber, &num2, &normal),
		BuildingTile(&redLumber, &num3, &normal),
		BuildingTile(&redLumber, &num4, &normal),
		BuildingTile(&redLumber, &num5, &normal),
		BuildingTile(&redLumber, &num6, &normal),
		BuildingTile(&yellowHay, &num1, &normal),
		BuildingTile(&yellowHay, &num2, &normal),
		BuildingTile(&yellowHay, &num3, &normal),
		BuildingTile(&yellowHay, &num4, &normal),
		BuildingTile(&yellowHay, &num5, &normal),
		BuildingTile(&yellowHay, &num6, &normal),
	};

	// Initializing _deck vector
	_deck = new vector<BuildingTile*>;

	for (int i = 0; i < *_sizeMax; i++) {
		//        cout << "Adding tile: " << &tiles[i] << endl;
		_deck->push_back(&tiles[i]);
	}

}

BuildingDeck::BuildingDeck(const BuildingDeck &deck) {

}

BuildingDeck::~BuildingDeck() {
	if (_deck) {
		//        cout << "Deleting _deck of BuildingTile with address: " << this << endl;
		delete _deck;
		_deck = nullptr;
		//        cout << "DONE" << endl;
	}
}

vector<BuildingTile*>* BuildingDeck::getDeck() {
	return _deck;
}

void BuildingDeck::add(BuildingTile &tile) {
	//    cout << "Adding: " << &tile << endl;
	_deck->push_back(&tile);
}


void BuildingDeck::remove(BuildingTile &tile) {
	_deck->erase(std::remove(_deck->begin(), _deck->end(), &tile), _deck->end());
}


BuildingTile* BuildingDeck::draw() {
	if (_deck->size() > 0) {
		int randomIndex = rand() % _deck->size();
		BuildingTile *tile = _deck->at(randomIndex);
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
	resourceScoreArr = new int[4]{ 0, 0, 0, 0 };
}

int* Hand::exchange()
{
	resourceScoreArr[static_cast<int>(ResourceName::Rock)] = sc->get_stone();
	resourceScoreArr[static_cast<int>(ResourceName::Lumber)] = sc->get_lumber();
	resourceScoreArr[static_cast<int>(ResourceName::Wheat)] = sc->get_wheat();
	resourceScoreArr[static_cast<int>(ResourceName::Sheep)] = sc->get_sheep();

	return resourceScoreArr;
}

void Hand::displayHand() {

	for (int i = 0; i < 4; i++) {
		cout << HarvestTile::ResourceNameToString(static_cast<ResourceName>(i)) << ": " << resourceScoreArr[i];
	}
}