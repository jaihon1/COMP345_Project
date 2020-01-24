#ifndef board_h
#define board_h

class GBMaps {
private:
    int* _id;
    int* _numberOfPlayers;

    
    
public:
    GBMaps(int* id, int* numberOfPlayers);
    ~GBMaps();
    
    void setId(int* id);
    void setNumberOfPlayers(int* numberOfPlayers);
    
    int getId();
    int* getIdAddress();
    int getNumberOfPlayers();
};

#endif /* board_h */


