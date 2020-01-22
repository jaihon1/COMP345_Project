#include <iostream>
#include "modules/board/GBMaps.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    int id = 11;
    int players = 4;
    
    GBMaps map1(&id, &players);
    
    cout << "Board ID: " << map1.getIdAddress() << endl;
    cout << "Number of Players: " << map1.getNumberOfPlayers() << endl;
    
    
    return 0;
}
