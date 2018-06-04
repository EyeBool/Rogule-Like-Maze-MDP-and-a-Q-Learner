#ifndef QLEARNER_H
#define QLEARNER_H

#include "state.h"
#include <unordered_map>
#include <vector>
#include <random>

class qlearner
{
	unsigned int number_actions;
	unsigned int number_episodes;
	unsigned int number_steps;
	double alpha_initial;
	double alpha_final;
	double gamma;
	double epsilon;
	std::unordered_map<state, std::vector<double>> qtable;

	std::default_random_engine RNG;
	std::uniform_real_distribution<double> unif_dist;
	std::uniform_int_distribution<int> rand_action;

public:
	qlearner(
		unsigned int number_actions,
		unsigned int number_episodes,
		unsigned int number_steps,
		double alpha_initial,
		double alpha_final,
		double gamma,
		double epsilon
	);

	double qFunction(state game_state, DIRECTION action);
	std::vector<double> qFunction(state game_state);
	void updateQTable(state curr_game_state, state next_game_state, DIRECTION action, double reward, double alpha);

	DIRECTION chooseAction(state game_state);

	void qLearn(state game_state, bool verbose=true);


	~qlearner();
};
#endif