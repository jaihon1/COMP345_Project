#include <stdio.h>
#include "board.hpp"

// Constructor
Board::Board(int id, int numCountries, int numContinents) {
    _id = id;
    _numOfCountries = numCountries;
    _numOfContinents = numContinents;
}

// Destructor
Board::~Board(){
    printf("Object board with ID = %d has been destructed!\n", _id);
};

// Methods
void Board::setNumberOfCountries(int num) {
    _numOfCountries = num;
}

void Board::setNumberOfContinents(int num) {
    _numOfContinents = num;
}

int Board::getId() {
    return _id;
}

int Board::getNumberOfCountries() {
    return _numOfCountries;
}

int Board::getNumberOfContinents() {
    return _numOfContinents;
}
