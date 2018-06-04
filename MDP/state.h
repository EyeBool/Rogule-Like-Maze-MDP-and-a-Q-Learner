#ifndef STATE_H
#define STATE_H

#include "environment.h"
#include "agent.h"
#include <tuple>

enum DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class state
{
	environment city;
	agent robot;

public:
	state(environment city, agent robot);
	state(environment city, unsigned int x, unsigned int y);
	state(environment city);

	void showCity() const;

	unsigned int getCityWidth() const;
	unsigned int getCityHeight() const;
	CELL getCityCell(unsigned int x, unsigned int y) const;

	unsigned int getRobotX() const;
	unsigned int getRobotY() const;

	std::tuple<state, double, bool> moveAgent(DIRECTION direction);

	bool operator==(const state& rhs) const;

	~state();
};

namespace std {

	template <>
	struct hash<state>
	{
		std::size_t operator()(const state& s) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			size_t h = 5381;

			h = ((h << 5) + h) + (size_t)s.getRobotX();
			h = ((h << 5) + h) + (size_t)s.getRobotY();

			for (unsigned int row = 0; row < s.getCityWidth(); row++) {
				for (unsigned int col = 0; col < s.getCityHeight(); col++) {
					h = ((h << 5) + h) + (size_t)s.getCityCell(row, col);
				}
			}

			return h;
		}
	};
}

#endif