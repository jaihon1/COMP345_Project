#include <stdio.h>
#include "GBMaps.hpp"

//preprocessor directives for test main
#include <iostream>
using namespace std;

GBSquare::GBSquare() {
	status = GBSquareStatus::Empty;
	harvestTilePtr = NULL;
}

GBSquare::~GBSquare() {
	delete harvestTilePtr;
}

//TODO: add helper function to initialize board B
GBMaps::GBMaps(int numberOfPlayers, char boardSide)
{ 
	//TODO: enter if statement on each case for Board B option
	switch (numberOfPlayers) {
	case 2: 
		rows = new int(5);
		columns = new int(5);
		initializeBoard();

		board[0][0].status = GBSquareStatus::HarvestTile;
		board[0][4].status = GBSquareStatus::HarvestTile;
		board[4][0].status = GBSquareStatus::HarvestTile;
		board[4][4].status = GBSquareStatus::HarvestTile;
		break;

	case 3:
		//hard code 3 player game along horizontal axis (as opposed to letting players choose orientation)
		rows = new int(5);
		columns = new int(7);
		initializeBoard();

		board[0][1].status = GBSquareStatus::HarvestTile;
		board[0][5].status = GBSquareStatus::HarvestTile;
		board[4][1].status = GBSquareStatus::HarvestTile;
		board[4][5].status = GBSquareStatus::HarvestTile;
		break;

	case 4:
		rows = new int(7);
		columns = new int(7);
		initializeBoard();

		board[0][0].status = GBSquareStatus::Unavailable;
		board[0][6].status = GBSquareStatus::Unavailable;
		board[6][0].status = GBSquareStatus::Unavailable;
		board[6][6].status = GBSquareStatus::Unavailable;

		board[1][1].status = GBSquareStatus::HarvestTile;
		board[1][5].status = GBSquareStatus::HarvestTile;
		board[5][1].status = GBSquareStatus::HarvestTile;
		board[5][5].status = GBSquareStatus::HarvestTile;
		break;

	default:
		//if an invalid number of players are given then a "null" board is created
		rows = NULL;
		columns = NULL;
		board = NULL;
		break;
	}

}

GBMaps::~GBMaps()
{
	for (int i = 0; i < *rows; i++) {
		delete[] board[i];
	}
	delete board;
}

void GBMaps::initializeBoard() {

	//board is a single row of pointers. 
	//Each index in the row points to another array of objects (this is the column)
	board = new GBSquareArrayPtr[*rows];

	//loop assigns "column" array (of GBSquare objects) to each index of the row array
	for (int i = 0; i < *rows; i++) {
		board[i] = new GBSquare[*columns];

		//inner loop to initialize GBSquares
		for (int j = 0; j < *columns; j++) {
			board[i][j].status = GBSquareStatus::Empty;
		}
	}
}

GBSquare GBMaps::getSquare(int row, int column)
{
	return board[row][column];
}

GBSquareStatus GBMaps::getSquareStatus(int row, int column)
{
	return board[row][column].status;
}

//TODO: complete definition to actually add HarvestTile
int GBMaps::addHarvestTile(int row, int column, HarvestTile* inHarvestTilePtr)
{
	//check if game board square is empty to add tile
	if (board[row][column].status == GBSquareStatus::Empty) {
		board[row][column].status = GBSquareStatus::HarvestTile;
		board[row][column].harvestTilePtr = inHarvestTilePtr;
		return 1;
	}
	return 0;
}

HarvestTile* GBMaps::getHarvestTile(int row, int column)
{
	return board[row][column].harvestTilePtr;
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

//main method for class testing
int main() {

	GBMaps* gameBoard = new GBMaps(2, 'a');
	delete gameBoard;

	return 0;
}
