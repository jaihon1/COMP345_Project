#ifndef board_h
#define board_h

class Board {
private:
    int _id;
    int _numOfCountries;
    int _numOfContinents;
    
    
public:
    Board(int id, int numberOfCountries, int numberOfContinents);
    ~Board();
    
    void setNumberOfCountries(int num);
    void setNumberOfContinents(int num);
    
    
    int getNumberOfCountries();
    int getNumberOfContinents();
};

#endif /* board_h */


