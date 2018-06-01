#pragma once

#include "Point.h"
#include <sstream>
#include <string>
using namespace std;

class IllegalCoordinateException {
	int x;
	int y;
public:
	IllegalCoordinateException(int x, int y): x(x),y(y) {}
	string theCoordinate() const { 
	std::ostringstream s;
    s << x << "," << y;
    return s.str();
		
	}
};

