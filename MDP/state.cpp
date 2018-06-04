#include "state.h"
#include <stdexcept>
#include <algorithm>

state::state(environment init_city, agent init_robot) : city(init_city), robot(init_robot) {
	if (init_robot.getX() >= init_city.width())
		throw std::invalid_argument("Out of bounds x position.");

	if (init_robot.getY() >= init_city.height())
		throw std::invalid_argument("Out of bounds y position.");
}

state::state(environment init_city, unsigned int x, unsigned int y) : city(init_city) {
	if (x >= init_city.width())
		throw std::invalid_argument("Out of bounds x position.");

	if (y >= init_city.height())
		throw std::invalid_argument("Out of bounds y position.");

	robot = agent(x, y);
}

state::state(environment city) : state(city, 0u, 0u) {}

void state::showCity() const
{
	city.show();
}

unsigned int state::getCityWidth() const
{
	return city.width();
}

unsigned int state::getCityHeight() const
{
	return city.height();
}

CELL state::getCityCell(unsigned int x, unsigned int y) const
{
	return city.getCell(x, y);
}

unsigned int state::getRobotX() const
{
	return robot.getX();
}

unsigned int state::getRobotY() const
{
	return robot.getY();
}

std::tuple<state, double, bool> state::moveAgent(DIRECTION direction)
{
	// new state

	environment new_city = city;
	agent new_robot = robot;
	double reward;
	bool done;

	// update car position

	switch (direction) {
	case UP:
		if (robot.getY() > 0)
			new_robot.setY(robot.getY() - 1);
		break;
	case DOWN:
		if (robot.getY() < city.height() - 1)
			new_robot.setY(robot.getY() + 1);
		break;
	case LEFT:
		if (robot.getX() > 0)
			new_robot.setX(robot.getX() - 1);
		break;
	case RIGHT:
		if (robot.getX() < city.width() - 1)
			new_robot.setX(robot.getX() + 1);
	}

	// update city

	CELL cell = city.getCell(new_robot.getX(), new_robot.getY());

	switch (cell) {
	case PIT:
		reward = -1000.0;
		done = true;
		new_city.setCell(robot.getX(), robot.getY(), EMPTY);
		new_city.setCell(new_robot.getX(), new_robot.getY(), ROBOT);
		break;
	case DIAMOND:
		reward = 1000.0;
		done = true;
		new_city.setCell(robot.getX(), robot.getY(), EMPTY);
		new_city.setCell(new_robot.getX(), new_robot.getY(), ROBOT);
		break;
	case ROBOT:
		reward = -10.0;
		done = false;
		break;
	case EMPTY:
		reward = -1.0;
		done = false;
		new_city.setCell(robot.getX(), robot.getY(), EMPTY);
		new_city.setCell(new_robot.getX(), new_robot.getY(), ROBOT);
	}

	// return new state + reward

	state new_state = state(new_city, new_robot);

	return std::tuple<state, double, bool>(new_state, reward, done);
}

bool state::operator==(const state & rhs) const
{
	return (city == rhs.city) && (robot == rhs.robot);
}

state::~state() {}