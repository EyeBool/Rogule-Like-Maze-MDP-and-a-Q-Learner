#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>

enum CELL {
	PIT,
	DIAMOND,
	ROBOT,
	EMPTY
};

std::ostream& operator<<(std::ostream& os, const CELL& cell);

class environment
{
	std::vector<std::vector<CELL>> grid;

public:

	environment(std::vector<std::vector<CELL>> grid);

	void show() const;

	unsigned int width() const;
	unsigned int height() const;

	CELL getCell(unsigned int x, unsigned int y) const;
	void setCell(unsigned int x, unsigned int y, CELL cell);

	bool operator==(const environment& rhs)const;

	~environment();
};

#endif