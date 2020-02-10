// GBMapLoader.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "GBMaps.h"
#include "GBMapLoader.h"
#include <nlohmann/json.hpp>



using namespace std;
using json = nlohmann::json;

GBMapLoader::GBMapLoader(const char* inFilePath)
{
	ifstream inFileStream;
	inFileStream.open(inFilePath);
	json GBMapDoc;
	inFileStream >> GBMapDoc;
	
	auto const numberOfPlayers = GBMapDoc.find("NumberOfPlayers");
	board = new GBMaps((int)numberOfPlayers.value(), 'a');

	auto const boardJSON = GBMapDoc.find("board");
	if (boardJSON == GBMapDoc.end()) {
		cerr << "board not found";
		return;
	}

	int boardRow = -1;
	statusMap statusMap;
	resourceMap resourceMap;

	for (auto const& row : *boardJSON) {
		boardRow++;
		int boardColumn = -1;
		for (auto const& column : row) {
			boardColumn++;
			auto const GBSquare = column.find("GBSquare");
			auto const GBSquareStatus = GBSquare->find("status");
			if (statusMap[*GBSquareStatus] == GBSquareStatus::HarvestTile) {
				auto const harvestTile = GBSquare->find("resources");

				ResourceName* resourceArray = new ResourceName[4];
				int resArrCount=0;
				for (auto const& resource : *harvestTile) {
					resourceArray[resArrCount] = resourceMap[resource];
					resArrCount++;
				}
				board->addHarvestTile(boardRow, boardColumn, new HarvestTile(resourceArray[0], resourceArray[1], resourceArray[2], resourceArray[3]));
			}
		}
	}

}

GBMaps* GBMapLoader::getBoard() {
	return board;
}
