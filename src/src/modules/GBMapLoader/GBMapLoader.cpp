// GBMapLoader.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "../board/GBMaps.h"
#include "GBMapLoader.h"
#include <nlohmann/json.hpp>




using namespace std;
using json = nlohmann::json;

GBMapLoader::GBMapLoader(const char* inFilePath)
{
	ifstream inFileStream;
	inFileStream.open(inFilePath);

	//Document Object Model - human readable model of an instance of a GBMap object
	json GBMapDoc;

	//can dump the input file stream directly into the DOM
	inFileStream >> GBMapDoc;
	
	//statement initializes the number of players based on the integer associated with the key "Number of players" within the JSON document
	auto const numberOfPlayers = GBMapDoc.find("NumberOfPlayers");
	board = new GBMaps((int)numberOfPlayers.value(), 'a');

	//TODO: add more checks that json is valid
	//if statement checks that a board object is present
	auto const boardJSON = GBMapDoc.find("board");
	if (boardJSON == GBMapDoc.end()) {
		cerr << "board not found";
		return;
	}

	int boardRow = -1;
	
	statusMap statusMap;
	resourceMap resourceMap;

	//for statement loops through each row of the board object
	for (auto const& row : *boardJSON) {
		boardRow++;
		int boardColumn = -1;
		for (auto const& column : row) {
			boardColumn++;

			auto const GBSquare = column.find("GBSquare");

			//DOM returns a string therefore GBSquareStatus is a string
			auto const GBSquareStatus = GBSquare->find("status");

			//statusMap converts the GBSquareStatus String to an enum for the comparison
			if (statusMap[*GBSquareStatus] == GBSquareStatus::HarvestTile) {
				auto const harvestTile = GBSquare->find("resources");

				ResourceName* resourceArray = new ResourceName[4];
				int resArrCount=0;
				for (auto const& resource : *harvestTile) {

					//resourceMap converts the resource string to an enum in order to assign the resource to the resource array which holds enums
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
