#include <iostream>
#include "modules/board/GBMaps.hpp"
#include "modules/loader/loader.hpp"
#include "modules/player/player.hpp"

using namespace std;

#include <fstream>

int main(int argc, const char * argv[]) {
    
    int id = 11;
    int players = 4;
    
    GBMaps map1(&id, &players);
    Loader myLoader;
    
    
//    ofstream myfile ("/Users/dzhay/Github/COMP345_Project/src/jirt.txt");
//    if (myfile.is_open())
//    {
//      myfile << "This is a line.\n";
//      myfile << "This is another line.\n";
//      myfile.close();
//    }
//    else cout << "Unable to open file";

    
    myLoader.read("/Users/dzhay/Github/COMP345_Project/src/test.txt");
//    
//    cout << "Board ID: " << map1.getIdAddress() << endl;
//    cout << "Number of Players: " << map1.getNumberOfPlayers() << endl;
        
    
    return 0;
}
