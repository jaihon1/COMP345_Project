#ifndef board_h
#define board_h

class Board {
private:
    int _id;

    
    
public:
    Board(int id);
    ~Board();
    
    void setId(int id);
    
    int getId();
};

#endif /* board_h */


