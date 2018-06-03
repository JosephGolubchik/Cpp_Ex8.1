#include "Board.h"
#include "Point.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sys/stat.h>
#include <unistd.h>
#include <string>
using namespace std;


string Board::draw(int imgSize){
    int i = 1;
    string filename = "";
    filename += to_string(i);
    filename += ".ppm";

    
    while ( fileExists(filename) ){
        i++;
        filename.clear();
        filename = "";
        filename += to_string(i);
        filename += ".ppm";
    }
    
    ofstream img (filename);
    
    int **finalMat = new int*[imgSize];
    for(int i = 0; i < imgSize; ++i) {
        finalMat[i] = new int[imgSize];
    }
    
    createBoard(finalMat, imgSize);
    
    img << "P3" << endl;
    img << imgSize << " " << imgSize << endl;
    img << 255 << endl;
    
    for (int y = 0; y < imgSize; y++) {
        for (int x = 0; x < imgSize; x++) {
            if (finalMat[y][x] == 1) 
                img << "160 160 160" << endl;
            else if (finalMat[y][x] == 2) 
                img << "77 122 245" << endl;
            else if (finalMat[y][x] == 3) 
                img << "245 77 77" << endl;
            else
                img << "255 255 255" << endl; 
        }
    }
    
    for(int i = 0; i < imgSize; i++)
        delete[] finalMat[i];
    delete[] finalMat;
    
    return filename;
}

void Board::createBoard(int** finalMat, int imgSize){
    int gSize = imgSize/size;
    int** matX = makeX(imgSize);
    int** matO = makeO(imgSize);
    int** matWhite = makeWhite(imgSize);

    
    for (int i = 0; i < size; i++) { /// Go over grids
        
        for (int j = 0; j < size; j++) {
            
            for (int y = 0; y < gSize; y++) { /// Go over rows
            
                for (int x = 0; x < gSize; x++) { /// Go over columns
                    if (board_Matrix[i][j].data == 'X') {
                        if (matX[y][x] == 1){
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 1;
                        }
                        else if (matX[y][x] == 2){
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 2;
                        }
                        else {
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 0;
                        }
                    }
                    else if (board_Matrix[i][j].data == 'O') {
                        if (matO[y][x] == 1){
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 1;
                        }
                        else if (matO[y][x] == 3){
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 3;
                        }
                        else {
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 0;
                        }
                    }
                    else if (board_Matrix[i][j].data == '.') {
                        finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 0;
                    }
                    if (y == gSize - 1 || x == gSize - 1 || y == 0 || x == 0){
                        finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 1;
                    }
                }
            }
            
            
        }
    
    }
    
    for(int i = 0; i < imgSize; i++) {
        delete[] matX[i];
        delete[] matO[i];
        delete[] matWhite[i];
    }
        
    delete[] matX;
    delete[] matO;
    delete[] matWhite;
    
}

int** Board::makeX(int imgSize){
    
    // Create matrix to contain pixels of X img
    int matSize = imgSize / size;
    int **mat = new int*[matSize];
    for(int i = 0; i < matSize; ++i) {
        mat[i] = new int[matSize];
    }
    
    int diff = matSize/30;
    int margin = (int)(matSize/7); 
    
    // Fill matrix
    for (int y = margin; y < matSize - margin; y++) {
        for (int x = margin ; x < matSize - margin; x++){
            if(y <= x + diff && y >= x - diff){
                mat[y][x] = 2;
            }
            else if(y <= matSize - x + diff && y >= matSize - x - diff){
                mat[y][x] = 2;
            }
            else {
                mat[y][x] = 0;
            }
        }
    }
    
    return mat;
    
    
    
}

int** Board::makeO(int imgSize){
    
    // Create matrix to contain pixels of O img
    int matSize = imgSize / size;
    int **mat = new int*[matSize];
    for(int i = 0; i < matSize; ++i) {
        mat[i] = new int[matSize];
    }
    
    int diff = matSize/40;
    int margin = (int)(matSize/8); 
    int radius = matSize/2 - margin;
    
    // Fill matrix
    for (int y = 0; y < matSize; y++) {
        for (int x = 0; x < matSize; x++){
            if (floor(sqrt((x-matSize/2)*(x-matSize/2) + (y-matSize/2)*(y-matSize/2))) >= radius - diff 
                && floor(sqrt((x-matSize/2)*(x-matSize/2) + (y-matSize/2)*(y-matSize/2))) <= radius + diff) {
                 mat[y][x] = 3;
            }
            else {
                 mat[y][x] = 0;
            }
        }
        
    }
    
    return mat;
    
}

int** Board::makeWhite(int imgSize){
    
    // Create matrix to contain white square
    int matSize = imgSize / size;
    int **mat = new int*[matSize];
    for(int i = 0; i < matSize; ++i) {
        mat[i] = new int[matSize];
    }
    
    // Fill matrix
    for (int y = 0; y < matSize; y++) {
        for (int x = 0; x < matSize; x++){
            mat[y][x] = 0;
        }
        
    }
    
    return mat;
    
}

bool fileExists (const string& filename) {
    ifstream f(filename.c_str());
    return f.good();
}

Board& Board::operator=(const char w){
    if(w == '.'|| w == 'O' || w == 'X'){
        for (int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++){
                board_Matrix[i][j].data = w;
            }
        }
    }
    else{
        throw IllegalCharException(w);
    }
    return *this;
}

Board& Board::operator=(const Board& b){
    board_Matrix.clear();
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

    return *this;
}


bool Board::operator == (Board const & r){
    if(size != r.size) return false;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(board_Matrix[i][j].data != r.board_Matrix[i][j].data) return false;
        }
    }
    return true;
}


ostream& operator<<(ostream& os, Board const& b) {  
     for (int i = 0; i < b.size; i++) {
        for(int j=0; j<b.size; j++){
            os << b.board_Matrix[i][j].data;
        }
        os << endl;
      }
    return os;  
}

istream& operator>>(istream & is, Board& b) {  
        string s;
        is >> s;
        b.size = s.length();
        
        for (int i = 0; i < b.size; i++) {
            vector< Point > temp;
            b.board_Matrix.push_back(temp);
            
            for (int j = 0; j < b.size; j++){
                Point p = {i,j};
                b.board_Matrix[i].push_back(p);
            }
        }
        
        for (int i = 0; i < b.size; i++) {
            b.board_Matrix[0][i].data = s[i];
        }
        
        for (int j = 1; j < b.size; j++) {
            is >> s;
            for (int i = 0; i < b.size; i++) {
                b.board_Matrix[j][i].data = s[i];
            }
        }
        return is;  
    }

Point& Board::operator[](Point p){
    if(p.x < 0 || p.x >= size || p.y < 0 || p.y >= size){
        throw IllegalCoordinateException(p.x, p.y);
    }
    else{
        return board_Matrix[p.x][p.y];
    }

}

const Point& Board::operator[](Point p) const{
    if(p.x < 0 || p.x >= size || p.y < 0 || p.y >= size){
        throw IllegalCoordinateException(p.x, p.y);
    }
    else{
        return board_Matrix[p.x][p.y];
    }

}

void Board::clear(){
    // board_Matrix.clear()
}

Board::~Board(){
// 	clear();
}


