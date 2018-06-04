#ifndef AGENT_H
#define AGENT_H

class agent
{
	unsigned int x, y;

public:
	agent();
	agent(unsigned int x, unsigned int y);

	unsigned int getX() const;
	void setX(unsigned int new_x);

	unsigned int getY() const;
	void setY(unsigned int new_y);

	bool operator==(const agent& rhs)const;

	~agent();
};
#endif