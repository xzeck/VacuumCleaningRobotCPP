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
	unsigned int x, y;

	diple(unsigned int x, unsigned int y) : x(x), y(y) {}
	diple() : x(0), y(0) {}

	diple& operator/= (const diple& rhs)
	{
		
		x /= rhs.x; 
		y /= rhs.y;

		return *this;
	}

	diple& operator/ (const diple& rhs)
	{
		diple temp(*this);
		temp /= rhs; 
		return temp;
	}
};

class Color
{
public:
	unsigned char red; 
	unsigned char blue; 
	unsigned char green;

	Color(unsigned char r, unsigned char b, unsigned char g) 
		: red(r), blue(b), green(g) {}

	Color() : red(0), blue(0), green(0) {}
};

#endif
