//
//  loader.cpp
//  src
//
//  Created by Jaihon Qasim on 2020-01-31.
//  Copyright © 2020 Jaihon Qasim. All rights reserved.
//

#include "loader.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Loader::Loader() {
    
    
}

Loader::~Loader() {
    printf("Object loader has been destructed!\n");
}

void Loader::read(string filePath) {
    string line;
    
    ifstream file;
    file.open(filePath);
    
    if (file.is_open()) {
      while ( getline(file, line) ) {
        cout << line << '\n';
      }
      file.close();
    }

    else {
        cout << "Unable to open file" << endl;
    }
    
}
