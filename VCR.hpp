#pragma once
#ifndef VCR_hpp
#define VCR_hpp 
enum GRIDBITS { clean, dirty, obstacle, unchecked = -1 };

class Grid {
public:
	unsigned int x;
	unsigned int y;
	GRIDBITS Type;

	Grid(unsigned int x, unsigned int y, GRIDBITS type) : x(x), y(y), Type(type) {}
	Grid() : x(0), y(0), Type(unchecked) {}
};

class diple {
public:
	int x, y;
};

#endif
