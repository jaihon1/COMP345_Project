#include <stdio.h>
#include "GBMaps.h"

GBSquare::GBSquare() {
	status = GBSquareStatus::Empty;
	tilePtr = NULL;
}

GBSquare::~GBSquare() {
	delete tilePtr;
}

//TODO: save board function (using binary file?)
/*TODO (for Board B):
-implement helper function to initialize Board B
-create helper function to randomly distribute pond tiles on designated square
-create helper function to randomly distribute harvest tiles on designated squares
-create helper function to randomly distribute building tiles on designated squares
*/
GBMaps::GBMaps(int inNumberOfPlayers, char boardSide)
{
	numberOfPlayers = new int(inNumberOfPlayers);
	//board is a single row of pointers. 
	//Each index in the row points to another array of objects (this is the column)
	board = new GBSquare* [*rows];

	//loop assigns "column" array (of GBSquare objects) to each index of the row array
	for (int i = 0; i < *rows; i++) {
		board[i] = new GBSquare[*columns];

		//inner loop to initialize GBSquares
		for (int j = 0; j < *columns; j++) {
			board[i][j].status = GBSquareStatus::Empty;
		}
	}

	if (boardSide == 'b') {
		intializeBoardB(*numberOfPlayers);
	}
	else {
		initializeBoardA(*numberOfPlayers);
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
	
	//default resource tiles
	addHarvestTile(1, 1, new HarvestTile(ResourceName::Rock, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Lumber));
	addHarvestTile(1, 5, new HarvestTile(ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat, ResourceName::Lumber));
	addHarvestTile(5, 1, new HarvestTile(ResourceName::Rock, ResourceName::Rock, ResourceName::Lumber, ResourceName::Wheat));
	addHarvestTile(5, 5, new HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Sheep, ResourceName::Wheat));

	switch (numberOfPlayers) {
	case 2:

		//top and bottom row on a 7x7 map is unavailable for a two person game as well as the first and last columns
		for (int i = 0; i < 6; i++) {
			board[0][i].status = GBSquareStatus::Unavailable;
			board[6][i].status = GBSquareStatus::Unavailable;
			board[i][0].status = GBSquareStatus::Unavailable;
			board[i][6].status = GBSquareStatus::Unavailable;
		}
		break;

	case 3:

		//first and last column are unavailable for a three person game on a 7x7 map
		for (int i = 0; i < 6; i++) {
			board[i][0].status = GBSquareStatus::Unavailable;
			board[i][6].status = GBSquareStatus::Unavailable;
		}
		break;

	case 4:
		board[0][0].status = GBSquareStatus::Unavailable;
		board[0][6].status = GBSquareStatus::Unavailable;
		board[6][0].status = GBSquareStatus::Unavailable;
		board[6][6].status = GBSquareStatus::Unavailable;
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

int GBMaps::map(int index)
{
	int row = index/28;
	int column = (index%14)/2;
	int test;
	//HarvestTile temp = *getHarvestTile(row, column);

	int pos = index % 28;
	if (pos > 14)
		pos = pos % 2 + 2;
	else
		pos = pos % 2;
	//std::cout << row << " " << column << " " << index << " " <<pos << std::endl;
	//std::cin >> test;
	int result = static_cast<int>((*getHarvestTile(row, column)).getResource(static_cast<ResourceLocation>(pos)));
	return result;
}

int GBMaps::addHarvestTile(int row, int column, HarvestTile* inHarvestTilePtr, Scoring &sc)
{
	//check if game board square is empty to add tile
	if (board[row][column].status == GBSquareStatus::Empty) {
		board[row][column].status = GBSquareStatus::HarvestTile;
		board[row][column].tilePtr = inHarvestTilePtr;

		int board_length = 14;
		int max_tile = 196;

		sc.reset_res();
		int topleft = row * 28 + column * 2;
		ptrdiff_t index[4] = { topleft, topleft+1, topleft+14, topleft+15 };

		for (int i = 0; i < 4; i++)
		{
			int next = index[i] - 1;
			if ((index[i] %board_length != 0) && (board[next/28][(next%14) / 2].status != GBSquareStatus::Empty) && (map(index[i]) == map(next)))
				sc.addEdge(index[i], next);
			next = index[i] + 1;
			if (((index[i] + 1) % board_length != 0) && (board[next/28][(next%14) / 2].status != GBSquareStatus::Empty) && (map(index[i]) == map(next)))
				sc.addEdge(index[i], next);
			next = index[i] - board_length;
			if ((index[i] >= board_length) && (board[next/28][(next%14) / 2].status != GBSquareStatus::Empty)&& (map(index[i]) == map(next)))
				sc.addEdge(index[i], next);
			next = index[i] + board_length;
			if ((index[i]< max_tile - board_length) && (board[next/28][(next%14) / 2].status != GBSquareStatus::Empty) && (map(index[i]) == map(next)))
				sc.addEdge(index[i], next);
		}		
		static int res[4] = { 
			static_cast<int>((*inHarvestTilePtr).getResource(ResourceLocation::topLeft)),
			static_cast<int>((*inHarvestTilePtr).getResource(ResourceLocation::topRight)),
			static_cast<int>((*inHarvestTilePtr).getResource(ResourceLocation::bottomLeft)),
			static_cast<int>((*inHarvestTilePtr).getResource(ResourceLocation::bottomRight)) };
		sc.update_res(index, res);

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

int GBMaps::getRows()
{
	return *rows;
}

int GBMaps::getColumns()
{
	return *columns;
}


