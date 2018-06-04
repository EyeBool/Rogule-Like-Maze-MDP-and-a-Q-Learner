#include "agent.h"

agent::agent(unsigned int x, unsigned int y) : x(x), y(y) {}

unsigned int agent::getX() const
{
	return x;
}
void agent::setX(unsigned int new_x)
{
	x = new_x;
}
unsigned int agent::getY() const
{
	return y;
}
void agent::setY(unsigned int new_y)
{
	y = new_y;
}
bool agent::operator==(const agent & rhs) const
{
	return (x == rhs.x) && (y == rhs.y);
}
agent::agent() : agent(0u, 0u) {}

agent::~agent() {}
