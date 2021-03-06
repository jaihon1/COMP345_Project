// GBMapLoader.cpp : Defines the functions for the static library.
//
#define NDEBUG

#include "pch.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../board/GBMaps.h"
#include "../tile/Dictionary.h"
#include "GBMapLoader.h"

using namespace std;
using json = nlohmann::json;

GBMapLoader::GBMapLoader(const char* inFilePath, Scoring* sc)
{
	//Document Object Model - human readable model of an instance of a GBMap object
	json GBMapDoc;
	board = nullptr;
	
	try {
		ifstream inFileStream;
		inFileStream.open(inFilePath);

		//check io state flag - checks file exists
		if (inFileStream.rdstate() != ios_base::goodbit) {
			cerr << "error: unable to open file.  Check file address." << endl << endl;
			return;
		}

		//can dump the input file stream directly into the DOM
		inFileStream >> GBMapDoc;

		//statement initializes the number of players based on the integer associated with the key "Number of players" within the JSON document
		auto const numberOfPlayers = GBMapDoc.find("NumberOfPlayers");

		// if Nlohmann "find" method is unable to retrieve a key then it returns an iterator object at "end"
		if (numberOfPlayers == GBMapDoc.end()) {
			cerr << "error: NumberOfPlayers attribute is missing" << endl << endl;
			return;
		}

		board = new GBMaps((int)numberOfPlayers.value(), 'a', sc);

		//if statement checks that a board object is present
		auto const boardJSON = GBMapDoc.find("board");

		// if Nlohmann "find" method is unable to retrieve a key then it returns an iterator object at "end"
		if (boardJSON == GBMapDoc.end()) {
			cerr << "error: board not found"<<endl << endl;
			delete board;
			board = nullptr;
			return;
		}

		if (boardJSON->size() != 7) {
			cerr << "error: incorrect number of rows" << endl << endl;
			delete board;
			board = nullptr;
			return;
		}

		int boardRow = -1;

		statusMap statusMap;
		resourceMap resourceMap;

		//for statement loops through each row of the board object
		for (auto const& row : *boardJSON) {

			boardRow++;

			if (row.size() != 7) {
				cerr << "error: row " << boardRow << " has an incorrect number of columns" << endl << endl;
				delete board;
				board = nullptr;
				return;
			}

			int boardColumn = -1;
			for (auto const& column : row) {
				boardColumn++;

				auto const GBSquare = column.find("GBSquare");

				// if Nlohmann "find" method is unable to retrieve a key then it returns an iterator object at "end"
				if (GBSquare == column.end()) {
					cerr << "error: GBSquare attribute is missing at column " << boardColumn << endl << endl;
					delete board;
					board = nullptr;
					return;
				}

				//DOM returns a string therefore GBSquareStatus is a string
				auto const GBSquareStatus = GBSquare->find("status");

				// if Nlohmann "find" method is unable to retrieve a key then it returns an iterator object at "end"
				if (GBSquareStatus == GBSquare->end()) {
					cerr << "error: GBSquare \"status\" attribute is missing" << endl << endl;
					delete board;
					board = nullptr;
					return;
				}

				//statusMap converts the GBSquareStatus String to an enum for the comparison
				if (statusMap[*GBSquareStatus] == GBSquareStatus::HarvestTile) {
					auto const harvestTile = GBSquare->find("resources");

					if (harvestTile == GBSquare->end()) {
						cerr << "error: GBSquare \"resources\" attribute is missing" << endl << endl;
						delete board;
						board = nullptr;
						return;
					}

					ResourceName* resourceArray = new ResourceName[4];
					int resArrCount = 0;
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
	catch (json::exception& e) {
		delete board;
		board = nullptr;
		cerr << "error: " << e.what() << endl << endl;
	}
	// catch statement seems redundant in case state flag not set (not sure what causes an exception)
	catch (const ifstream::failure& e) {
		cerr << "error: " << e.what() << " failure to open/read file" << endl << endl;
		return;
	}
}


GBMaps* GBMapLoader::getBoard() {
	return board;
}

void GBMapSaver::save(GBMaps* inBoard, const char* inFilePath) {
	outFile.open(inFilePath);
	//declare Document Object Model (JSON data type which is a map object among other things)
	json dom;

	//within my DOM (a JSON object) I create JSON objects (nested in my DOM) which are key-value pairs
	//in the following statement/s I create key-value pairs.
	//I create the JSON object with the string "Number of Player" as my key and assign it the actual number of players as the value
	dom["NumberOfPlayers"] = inBoard->getNumberOfPlayers();

	//board is a 2D array in which each element of the row array, holds another array that form the columns.
	//create a JSON array (rows)
	nlohmann::basic_json<> jsonRows = json::array();

	for (int i = 0; i < inBoard->getRows(); i++) {

		//create a JSON array (columns, which are nested as elements of the row)
		nlohmann::basic_json<> jsonColumns = json::array();

		//within each column element, I add key-value pairs that represent each square of the game board.
		for (int j = 0; j < inBoard->getColumns(); j++) {

			switch (inBoard->getSquareStatus(i, j)) {

			case GBSquareStatus::Empty:

				//the value of the GBSquare key is itself another key-value pair that reperesnts the status of the GBSquare on the game board
				//push.back method that adds the JSON object at the end of the array
				jsonColumns.push_back({ { "GBSquare", {{"status", "Empty"}} } });
				break;
			case GBSquareStatus::Unavailable:
				jsonColumns.push_back({ { "GBSquare", {{"status", "Unavailable"}}} });
				break;
			case GBSquareStatus::PondTile:
				jsonColumns.push_back({ { "GBSquare", {{"status", "PondTile"}}} });
				break;
				//TODO: must implement for board b
			case GBSquareStatus::BuildingTile:
				jsonColumns.push_back({ { "GBSquare", {{"status", "BuildingTile"}}} });
				break;
			case GBSquareStatus::HarvestTile:
				HarvestTile* tempHarvestTile = inBoard->getHarvestTile(i, j);

				//create a JSON array for the resources on the Harvest Tile
				nlohmann::basic_json<> jsonResourcesArr = {
					HarvestTile::ResourceNameToString(tempHarvestTile->getResource(ResourceLocation::topLeft)),
					HarvestTile::ResourceNameToString(tempHarvestTile->getResource(ResourceLocation::topRight)),
					HarvestTile::ResourceNameToString(tempHarvestTile->getResource(ResourceLocation::bottomLeft)),
					HarvestTile::ResourceNameToString(tempHarvestTile->getResource(ResourceLocation::bottomRight)) };

				//the key-value pair of a GBSquare with a Harvest Tile has a value which is a JSON list object that I use to pair the Status-HarvestTile key-value with the resources-resource array JSON object
				json listOfPairs = json::object({ {"status", "HarvestTile"}, {"resources", jsonResourcesArr} });
				jsonColumns.push_back({ { "GBSquare", listOfPairs} });
				break;

			}

		}
		jsonRows.push_back(jsonColumns);
	}

	//I create JSON object with the string "board" as the key and assign it the JSON Object jsonRows as its value.
	dom["board"] = jsonRows;
	//dump method generates formated output for easier reading and the the integer passed represents the indent amount for each nesting level
	outFile << dom.dump(2);
	outFile.close();
}