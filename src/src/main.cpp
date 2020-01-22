#include <iostream>
#include "modules/board/board.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
        
    Board board1(11);
    
    cout << "Board ID: " << board1.getId() << endl;
    
    
    return 0;
}
