//
//  player.hpp
//  src
//
//  Created by Jaihon Qasim on 2020-01-31.
//  Copyright © 2020 Jaihon Qasim. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>

class Player {
private:



public:
    Player();
    ~Player();
    
    
    // Must be changed to return a Village Board type
    int getVillageBoard();
    int setVillageBoard(int villageBoard);

    // Must be changed to return and input HarvestTile type
    int getHarvestTiles();
    int addHarvesTile(int harvestTile);
    int removeHarvestTile(int harvestTile);
    
    // Must be changed to return and input Building type
    int getBuildings();
    int resetBuildings();
    int addBuilding(int bulding);
    
    // Methods for the driver
    int placeHarvestTile(int harvestTile);
    void drawBuilding();
    void drawHarvestTile();
    void ressourceTracker();
    void buildVillage();
    void calculateResource();
    
    
    
    
};

#endif /* player_hpp */
