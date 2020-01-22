#include <stdio.h>
#include "board.hpp"

// Constructor
Board::Board(int id) {
    _id = id;
}

// Destructor
Board::~Board(){
    printf("Object board with ID = %d has been destructed!\n", _id);
};

// Methods
void Board::setId(int id) {
    _id = id;
}

int Board::getId() {
    return _id;
}

