#ifndef board_h
#define board_h

class GBMaps {

//MUST CHANGE TO POINTERS LATER
private:
	int numberOfPlayers;

	//double pointers: one for row and one for column
	GBSquare** board;

public:
	//constructor takes number of players and whether the game is played on Side A or Side B
    GBMaps(int numberOfPlayers, char boardSide);
    ~GBMaps();
    
	GBSquare getSquare(int row, int column);

	GBSquareStatus getSquareStatus(int row, int column);

	//return boolean: true = tile successfully added, false = tile not added (probably because square is unavailable)
	boolean addHarvestTile(int row, int column);

	//return boolean: true = tile successfully added, false = tile not added (probably because square is unavailable)
	boolean addPondTile(int row, int column);

};

//Game Board is an array of GBSquare objects identified by row and column number
class GBSquare {
	GBSquareStatus status;

};

//enumerated class to give name to the status that a square could have
enum class GBSquareStatus {
	Empty, //associated square holds nothing (empty)
	HarvestTile, //associated square holds a harvest tile
	PondTile, //associated square holds a pond tile (Side B)
	Unavailable //when playing with four players the corner squares are unavailable
};

#endif /* board_h */


