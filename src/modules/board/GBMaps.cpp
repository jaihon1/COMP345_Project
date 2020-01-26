#include <stdio.h>
#include "GBMaps.hpp"

// Constructor
GBMaps::GBMaps(int* id, int* numberOfPlayers) {
    _id = id;
    _numberOfPlayers = numberOfPlayers;
}

// Destructor
GBMaps::~GBMaps(){
    printf("Object board with ID = %p has been destructed!\n", _id);
};

// Methods
void GBMaps::setId(int* id) {
    _id = id;
}

void GBMaps::setNumberOfPlayers(int* numberOfPlayers) {
    _numberOfPlayers = numberOfPlayers;
}

int GBMaps::getId() {
    return *_id;
}

int* GBMaps::getIdAddress() {
    return _id;
}

int GBMaps::getNumberOfPlayers() {
    return *_numberOfPlayers;
}


