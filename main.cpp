#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
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
	for (uint i = 0; i < size.x; i++)
	{
		for (uint j = 0; j < size.y; j++)
		{
			std::cout << MAP[i][j].Type << " ";
		}
		std::cout << std::endl;
	}
}

void Generate_image(std::string name, diple& resolution, diple& size)
{
	diple individual_grid_size;

	individual_grid_size = resolution / size; 

	uint** grid = new uint*[individual_grid_size.x];

	for (uint i = 0; i < individual_grid_size.x; i++)
	{
		grid[i] = new uint[individual_grid_size.y];
	}

	std::ofstream imgOut(name);

	if (!imgOut)
	{
		std::cout << "Could not open image file for writing" << std::endl;
		exit(-1);
	}

	Color Unchecked(200, 0, 0);
	Color Clean(0, 0, 200);
	Color Obstacle(200, 0, 200);
	Color Dirty(0, 200, 0);

	uint red = 0;
	uint green = 0 ;
	uint blue = 0;
 

	imgOut << "P3" << std::endl;
	imgOut << resolution.x << " " << resolution.y << std::endl;
	imgOut << 255 << std::endl;

	for (uint x = 0; x < size.x; x++)
	{
		for (uint y = 0; y < size.y; y++)
		{
			for (uint j = 0; j < individual_grid_size.y; j++)
			{
				GRIDBITS Type = MAP[x][y].Type;
				if (Type == unchecked)
				{
					red = Unchecked.red;
					green = Unchecked.green;
					blue = Unchecked.blue;

				}
				else if (Type == dirty)
				{
					red = Dirty.red;
					green = Dirty.green;
					blue = Dirty.blue;

				}
				else if (Type == clean)
				{
					red = Clean.red;
					green = Clean.green;
					blue = Clean.blue;
				}
				else if (Type == obstacle)
				{
					red = Obstacle.red;
					green = Obstacle.green;
					blue = Obstacle.blue;
				}
				for (uint i = 0; i < resolution.x; i++)
				{
						imgOut << red << " ";
						imgOut << green << " ";
						imgOut << blue << " ";
				}

			}
		}
	}
	imgOut << std::endl;

}
int main()
{
	diple size; 
	size.x = 3; 
	size.y = 3; 

	diple Resolution(300, 300);

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

	Generate_image("initial.ppm", Resolution, size);

	std::cout << std::endl;
	std::cout << std::endl;

	explore(0, 0, size);

	print_grids(size);

	
	Generate_image("final.ppm", Resolution, size);
    return 0;
}