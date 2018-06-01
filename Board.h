#pragma once
#include <iostream>
#include <vector>
#include "Point.h"
#include "IllegalCoordinateException.h"
#include "IllegalCharException.h"
using namespace std;

class Board {
    public:
    int size;
    vector< vector<Point> > board_Matrix;

    Board() {
        size = 0;
    }

    Board(int size){
        this->size = size;
        
        for (int i = 0; i < size; i++) {
            vector< Point > temp;
            board_Matrix.push_back(temp);
            
            for (int j = 0; j < size; j++){
                Point coor = {i,j};
                board_Matrix[i].push_back(coor);
                board_Matrix[i][j].data = '.';
            }
        }
        
    }
    
    Board(const Board& b){
        size = b.size;

        for (int i = 0; i < size; i++) {
            vector< Point > temp;
            board_Matrix.push_back(temp);
            
            for (int j = 0; j < size; j++){
                Point p = {i,j};
                board_Matrix[i].push_back(p);
                board_Matrix[i][j].data=b.board_Matrix[i][j].data;
            }
        }
    }
    
    string draw(int imgSize);
    void createBoard(int** finalMat, int imgSize);
    int** makeX(int imgSize);
    int** makeO(int imgSize);
    int** makeWhite(int imgSize);
    Board& operator=(const char w);
    Board& operator=(const Board& b);
    friend ostream& operator<<(ostream& os, Board const& b);
    friend istream& operator>>(istream & is, Board& b);
    int getIndex(int x,int y);
    Point& operator[](Point p);
    const Point& operator[](Point p) const;
    bool operator == (Board const & r);
    void clear();
    ~Board();
};

    bool fileExists (const string& filename);
