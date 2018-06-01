#pragma once

class IllegalCharException {
	char c;
public:
	IllegalCharException(char c): c(c) {}
	char theChar() const { return c; }
};