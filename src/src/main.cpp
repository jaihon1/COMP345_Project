#include <iostream>
#include "modules/board/board.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
        
    Board board1(1, 100, 5);
    
    cout << "Board ID: " << board1.getId() << endl;
    cout << "Number of continents: " << board1.getNumberOfContinents() << endl;
    cout << "Number of countries: " << board1.getNumberOfCountries() << endl;
    
    
    return 0;
}
