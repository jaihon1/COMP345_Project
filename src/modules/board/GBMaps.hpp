#ifndef board_h
#define board_h

//enumerated class to give name to the status that a square could have
enum class GBSquareStatus {
	Empty, //associated square holds nothing (empty)
	HarvestTile, //associated square holds a harvest tile
	PondTile, //associated square holds a pond tile (Side B)
	Unavailable //when playing with four players the corner squares are unavailable
};

//Game Board is an array of GBSquare objects identified by row and column number
class GBSquare {
public:
	GBSquareStatus status;
};

class GBMaps {

private:
	//no length function for arrays in c++
	int* rows;
	int* columns;

	//an array of pointers that point to GBSquare objects
	typedef GBSquare* GBSquareArrayPtr;

	//Game Board is a pointer to an array of pointers
	GBSquareArrayPtr *board;

	void initializeBoard();

public:
	//constructor takes number of players and whether the game is played on Side A or Side B
    GBMaps(int numberOfPlayers, char boardSide);
	
    ~GBMaps();
    
	GBSquare getSquare(int row, int column);

	GBSquareStatus getSquareStatus(int row, int column);

	//return int: 1 = tile successfully added, 0 = tile not added (probably because square is unavailable)
	int addHarvestTile(int row, int column);

	//return boolean: true = tile successfully added, false = tile not added (probably because square is unavailable)
	int addPondTile(int row, int column);

};

#endif /* board_h */


