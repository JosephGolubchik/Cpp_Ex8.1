#pragma once
#include <iostream>
#include "IllegalCharException.h"
using namespace std;

class Point{
    public:
    int x;
    int y;
    char data;
    
    Point(){
        data = '.';
    }
    
    Point(char c){
        this->data = c;
    }
    
    Point(int x,int y){
        this->x = x;
        this->y = y;
        this->data = '.';
    }
    
    Point(const Point & p)
    {
        this->x = p.x;
        this->y = p.y;
        this->data = p.data;
    }
    
    Point operator=(const char c);
    Point& operator=(const Point& p);
    
    friend ostream& operator<<(ostream& os, Point& p) {  
        os << p.data;
        return os; 
    }
    operator char();
};

bool operator == (Point const &, char const &);
// char operator=(char c, Point& p);



    




