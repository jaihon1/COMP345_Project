#include <stdio.h>
#include "GBMaps.hpp"

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
		//hard code 3 pleayer game along horizontal axis (as opposed to letting players choose orientation)
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
		board = NULL;
		break;
	}

}

void GBMaps::initializeBoard() {
	
	board = new GBSquareArrayPtr[*rows];
	
	for (int i = 0; i < *rows; i++) {
		board[i] = new GBSquare[*columns];

		//inner loop to initialize GBSquares
		for (int j = 0; j < *columns; j++) {
			board[i][j].status = GBSquareStatus::Empty;
		}
	}
}
