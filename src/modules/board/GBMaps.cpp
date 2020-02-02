#include <stdio.h>
#include "GBMaps.hpp"

GBSquare::GBSquare() {
	status = GBSquareStatus::Empty;
	tilePtr = NULL;
}

GBSquare::~GBSquare() {
	delete tilePtr;
}

/*TODO (for Board B):
-implement helper function to initialize Board B
-create helper function to randomly distribute pond tiles on designated square
-create helper function to randomly distribute harvest tiles on designated squares
-create helper function to randomly distribute building tiles on designated squares
*/
GBMaps::GBMaps(int numberOfPlayers, char boardSide)
{
	switch (numberOfPlayers) {
	case 2:
		rows = new int(5);
		columns = new int(5);
		break;

	case 3:
		//hard code 3 player game along vertical axis (as opposed to letting players choose orientation)
		rows = new int(7);
		columns = new int(5);
		break;

	case 4:
		rows = new int(7);
		columns = new int(7);
		break;

	default:
		//if an invalid number of players are given then a "null" board is created
		rows = NULL;
		columns = NULL;
		board = NULL;
		return;
	}
	
	//board is a single row of pointers. 
	//Each index in the row points to another array of objects (this is the column)
	board = new GBSquare * [*rows];

	//loop assigns "column" array (of GBSquare objects) to each index of the row array
	for (int i = 0; i < *rows; i++) {
		board[i] = new GBSquare[*columns];

		//inner loop to initialize GBSquares
		for (int j = 0; j < *columns; j++) {
			board[i][j].status = GBSquareStatus::Empty;
		}
	}

	if (boardSide == 'b') {
		intializeBoardB(numberOfPlayers);
	}
	else {
		initializeBoardA(numberOfPlayers);
	}


}

GBMaps::~GBMaps()
{
	for (int i = 0; i < *rows; i++) {
		delete[] board[i];
	}
	delete board;
}

void GBMaps::initializeBoardA(int numberOfPlayers) {
	switch (numberOfPlayers) {
	case 2:

		board[0][0].status = GBSquareStatus::HarvestTile;
		board[0][4].status = GBSquareStatus::HarvestTile;
		board[4][0].status = GBSquareStatus::HarvestTile;
		board[4][4].status = GBSquareStatus::HarvestTile;
		break;

	case 3:

		board[0][1].status = GBSquareStatus::HarvestTile;
		board[0][5].status = GBSquareStatus::HarvestTile;
		board[4][1].status = GBSquareStatus::HarvestTile;
		board[4][5].status = GBSquareStatus::HarvestTile;
		break;

	case 4:

		board[0][0].status = GBSquareStatus::Unavailable;
		board[0][6].status = GBSquareStatus::Unavailable;
		board[6][0].status = GBSquareStatus::Unavailable;
		board[6][6].status = GBSquareStatus::Unavailable;

		board[1][1].status = GBSquareStatus::HarvestTile;
		board[1][5].status = GBSquareStatus::HarvestTile;
		board[5][1].status = GBSquareStatus::HarvestTile;
		board[5][5].status = GBSquareStatus::HarvestTile;
		break;
	}
}

void GBMaps::intializeBoardB(int numberOfPlayers) {

}



GBSquare GBMaps::getSquare(int row, int column)
{
	return board[row][column];
}

GBSquareStatus GBMaps::getSquareStatus(int row, int column)
{
	return board[row][column].status;
}

int GBMaps::addHarvestTile(int row, int column, HarvestTile* inHarvestTilePtr)
{
	//check if game board square is empty to add tile
	if (board[row][column].status == GBSquareStatus::Empty) {
		board[row][column].status = GBSquareStatus::HarvestTile;
		board[row][column].tilePtr = inHarvestTilePtr;
		return 1;
	}
	return 0;
}

HarvestTile* GBMaps::getHarvestTile(int row, int column)
{
	HarvestTile* harvestTilePtr = (HarvestTile*)board[row][column].tilePtr;
	return harvestTilePtr;
}

int GBMaps::addPondTile(int row, int column)
{
	//check if game board square is empty to add tile
	if (board[row][column].status == GBSquareStatus::Empty) {
		board[row][column].status = GBSquareStatus::PondTile;
		return 1;
	}
	return 0;
}


