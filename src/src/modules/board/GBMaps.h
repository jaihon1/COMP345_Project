#ifndef board_h
#define board_h
#include<iostream> 
#include "../tile/Resources.h"
class Scoring;

#define _DEBUG
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

//enumerated class to give name to the status that a square could have
enum class GBSquareStatus {
	Empty, //associated square holds nothing (empty)
	HarvestTile, //associated square holds a harvest tile
	PondTile, //associated square holds a pond tile (Side B)
	BuildingTile, //associated square holds a BuildingTile
	Unavailable //when playing with four players the corner squares are unavailable
};

//GBSquare contains information about a square on the game board
class GBSquare {
public:
	GBSquareStatus status;
	Tile* tilePtr;

	GBSquare();
	~GBSquare();
};

//Game Board is an array of GBSquare objects identified by row and column number
class GBMaps {

private:
	int* numberOfPlayers;
	Scoring* scoringObj;

	//using const pointers because the assignment says attributes have to be pointers
	const int* const rows = new int(7);
	const int* const columns = new int(7);
	const int total_tile = 49;
	int occupied_tile = 0;

	//Game Board is a pointer to an array of pointers
	GBSquare** board;

	void initializeBoardA();

	void intializeBoardB();

public:
	//constructor takes number of players and whether the game is played on Side A or Side B
    GBMaps(int numberOfPlayers, char boardSide, Scoring* sc);
	
    ~GBMaps();
    
	GBSquare getSquare(int row, int column);

	GBSquareStatus getSquareStatus(int row, int column);

	//return int: 1 = tile successfully added, 0 = tile not added (probably because square is unavailable)
	int addHarvestTile(int row, int column, HarvestTile * inHarvestTilePtr);
	int addShipmentTile(int row, int column, HarvestTile * inHarvestTilePtr, int type);

	HarvestTile* getHarvestTile(int row, int column);

	//return boolean: true = tile successfully added, false = tile not added (probably because square is unavailable)
	int addPondTile(int row, int column);

	int getRows();

	int getColumns();

	int getNumberOfPlayers();

	int getOccupiedTile();
};

#endif /* board_h */


