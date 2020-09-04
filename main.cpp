#include <iostream>
#include <vector>
#include "VCR.hpp"

Grid** MAP;
typedef unsigned int uint; 

void generate_and_initialize_map(diple& size)
{
	MAP = new Grid*[size.x];

	for (uint i = 0; i < size.x; i++) {
		MAP[i] = new Grid[size.y];
	}

	for (uint i = 0; i < size.x; i++)
	{
		for (uint j = 0; j < size.y; j++)
		{
			MAP[i][j].Type = unchecked;
		}
	}
}

void explore(uint x, uint y, diple& size)
{

	if ((x >= 0 && y >= 0) && (x < size.x && y < size.y))
	{
		if( MAP[x][y].Type == obstacle || MAP[x][y].Type == clean)
			return;
		else {

			MAP[x][y].Type = clean;
			
			explore(x + 1, y, size);
			explore(x - 1, y, size);
			explore(x, y + 1, size);
			explore(x, y - 1, size);
		}
	}
}

void assign_grid_bits(GRIDBITS type, std::vector<diple>& grids )
{
	for (diple t : grids)
	{
		MAP[t.x][t.y].Type = type;
	}
}

void print_grids(diple& size)
{
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			std::cout << MAP[i][j].Type << " ";
		}
		std::cout << std::endl;
	}
}
int main()
{
	diple size; 
	size.x = 3; 
	size.y = 3; 

	std::vector<diple> dirty_grids;
	std::vector<diple> obstacle_grids; 
	
	diple temp; 
	temp.x = 0; 
	temp.y = 0; 
	dirty_grids.push_back(temp);
	temp.x = 0; 
	temp.y = 1;
	dirty_grids.push_back(temp);

	temp.x = 1;
	temp.y = 1;
	obstacle_grids.push_back(temp);
	temp.x = 1;
	temp.y = 2;
	obstacle_grids.push_back(temp);

	generate_and_initialize_map(size);
	
	assign_grid_bits(dirty, dirty_grids);

	assign_grid_bits(obstacle, obstacle_grids);

	print_grids(size);

	std::cout << std::endl;
	std::cout << std::endl;

	explore(0, 0, size);

	print_grids(size);

    return 0;
}