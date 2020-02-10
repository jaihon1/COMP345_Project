#include <stdio.h>
#include "VGMaps.hpp"

VGMaps::VGMaps()
{
	village_board = new VGSquare*[*rows]; 

	for (int i = 0, i < *rows; i++)
	{
		village_board[i] = new VGSquare*[*columns]; 

		//initialized the current 2D array
		for (int j = 0; j < *columns; j++)
		{
			village_board[i][j].VGstatus = VGSlotStatus::Empty;
		}
	}

}

VGMaps::~VGMaps()
{
	for (int i = 0; i < *rows; i++)
	{
		delete[] village_board[i]; 
	}
	delete village_board;
}

VGMaps::getStatus(int row, int column)
{
	return village_board[row][column].VGstatus; 
}