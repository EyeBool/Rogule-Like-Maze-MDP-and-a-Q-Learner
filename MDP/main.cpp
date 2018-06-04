#include <iostream>
#include <vector>

#include "environment.h"
#include "agent.h"
#include "state.h"
#include "qlearner.h"

int main() {
	// setup game

	std::vector<std::vector<CELL>> grid = {
		{ROBOT, EMPTY, EMPTY, EMPTY},
		{PIT, PIT, PIT, EMPTY},
		{EMPTY, DIAMOND, PIT, EMPTY},
		{EMPTY, PIT, PIT, EMPTY},
		{EMPTY, EMPTY, EMPTY, EMPTY}
	};
	environment city = environment(grid);

	agent robot(0, 0);
	
	state game(city, robot);

	std::cout << "Starting position:\n\n";
	game.showCity();

	std::cout << "\nAction enum map:\n"
		<< " 0 -> UP\n"
		<< " 1 -> DOWN\n"
		<< " 2 -> LEFT\n"
		<< " 3 -> RIGHT\n";

	// start qlearning

	unsigned int number_actions = 4;
	unsigned int number_episodes = 2000;
	unsigned int number_steps = 100;
	double alpha_initial = 1.0;
	double alpha_final = 0.02;
	double gamma = 1.0;
	double epsilon = 0.1;

	std::cout << "\nStarting q-learning with:"
		<< "\n number episodes: " << number_episodes
		<< "\n number steps/episode: " << number_steps
		<< "\n initial alpha: " << alpha_initial
		<< "\n final alpha: " << alpha_final
		<< "\n gamma: " << gamma
		<< "\n epsilon (pr. of taking random action): " << epsilon
		<< std::endl;

	qlearner ql(number_actions, number_episodes, number_steps, alpha_initial, alpha_final, gamma, epsilon);
	ql.qLearn(game, true);

	getchar();

	return 0;
}