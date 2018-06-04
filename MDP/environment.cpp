#include "environment.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const CELL& cell)
{
	switch (cell) {
	case PIT:
		os << "x";
		break;
	case DIAMOND:
		os << "*";
		break;
	case ROBOT:
		os << "r";
		break;
	case EMPTY:
		os << "_";
	}
	return os;
}


environment::environment(std::vector<std::vector<CELL>> grid) : grid(grid) {}

void environment::show() const
{
	for (std::vector<CELL> row : grid) {
		std::cout << " ";
		for (CELL cell : row) {
			std::cout << cell;
		}
		std::cout << std::endl;
	}
}

unsigned int environment::height() const
{
	return (unsigned int)grid.size();
}

unsigned int environment::width() const
{
	return (unsigned int)grid[0].size();
}

CELL environment::getCell(unsigned int x, unsigned int y) const
{
	if (x >= width())
		throw std::invalid_argument("Invalid x position.");

	if (y >= height())
		throw std::invalid_argument("Invalid y position.");

	return grid[y][x];
}

void environment::setCell(unsigned int x, unsigned int y, CELL cell)
{
	if (x >= width())
		throw std::invalid_argument("Invalid x position.");

	if (y >= height())
		throw std::invalid_argument("Invalid y position.");

	grid[y][x] = cell;
}

bool environment::operator==(const environment & rhs) const
{
	return grid == rhs.grid;
}


environment::~environment()
{
}