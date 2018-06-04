#include "qlearner.h"
#include <iostream>
#include <algorithm>
#include <limits>

qlearner::qlearner(
	unsigned int number_actions,
	unsigned int number_episodes,
	unsigned int number_steps,
	double alpha_initial,
	double alpha_final,
	double gamma,
	double epsilon):
	number_actions(number_actions),
	number_episodes(number_episodes),
	number_steps(number_steps),
	alpha_initial(alpha_initial),
	alpha_final(alpha_final),
	gamma(gamma),
	epsilon(epsilon),
	unif_dist(std::uniform_real_distribution<double>(0.0, 1.0)),
	rand_action(std::uniform_int_distribution<int>(0, number_actions - 1))
{}

double qlearner::qFunction(state game_state, DIRECTION action) {
	if (qtable.find(game_state) == qtable.end())
		qtable[game_state] = std::vector<double>(number_actions, 0);

	return qtable[game_state][action];
}

std::vector<double> qlearner::qFunction(state game_state)
{
	if (qtable.find(game_state) == qtable.end())
		qtable[game_state] = std::vector<double>(number_actions, 0);

	return qtable[game_state];
}

void qlearner::updateQTable(state curr_game_state, state next_game_state, DIRECTION action, double reward, double alpha)
{
	if (qtable.find(curr_game_state) == qtable.end())
		qtable[curr_game_state] = std::vector<double>(number_actions, 0);

	if (qtable.find(next_game_state) == qtable.end())
		qtable[next_game_state] = std::vector<double>(number_actions, 0);

	double max_next_q = *std::max_element(qtable[next_game_state].begin(), qtable[next_game_state].end());
	double curr_q = qtable[curr_game_state][action];

	qtable[curr_game_state][action] = curr_q + alpha * (reward + gamma * max_next_q - curr_q);
}

DIRECTION qlearner::chooseAction(state game_state)
{
	DIRECTION max_action = (DIRECTION)rand_action(RNG);

	if (unif_dist(RNG) < epsilon)
		return max_action;

	double max_reward = std::numeric_limits<double>::lowest();
	for (unsigned int a = 0; a < number_actions; a++) {
		if (qFunction(game_state, (DIRECTION)a) > max_reward) {
			max_reward = qFunction(game_state, (DIRECTION)a);
			max_action = (DIRECTION)a;
		}
	}

	return max_action;
}

void qlearner::qLearn(state game_state, bool verbose)
{
	for (unsigned int episode = 1; episode <= number_episodes; episode++) {
		if (verbose) {
			std::cout << "\n********** EPISODE: " << episode << " **********\n";
		}

		state curr_game_state = game_state;
		double total_reward = 0.0;
		double alpha = alpha_initial;
		double delta = (alpha_final - alpha_initial) / double(number_steps);

		unsigned int step = 1;
		for (; step <= number_steps; step++) {
			if (verbose) {
				std::cout << "\n-- Step: " << step - 1 << " --\n\n";

				curr_game_state.showCity();

				std::vector<double> Q = qFunction(curr_game_state);
				std::cout << "\nq function:\n";
				for (unsigned int i = 0; i < Q.size(); i++) {
					std::cout << " action " << i << " -> " << Q[i] << "\n";
				}
			}

			alpha += delta;
			DIRECTION action = chooseAction(curr_game_state);

			std::tuple<state, double, bool> tup = curr_game_state.moveAgent(action);

			state next_city = std::get<0>(tup);
			double reward = std::get<1>(tup);
			bool done = std::get<2>(tup);

			total_reward += reward;

			updateQTable(curr_game_state, next_city, action, reward, alpha);

			curr_game_state = next_city;

			if (done) {
				break;
			}
		}

		if (verbose) {
			std::cout << "\n-- Step: " << step << " --\n\n";

			curr_game_state.showCity();

			std::vector<double> Q = qFunction(curr_game_state);
			std::cout << "\nq function:\n";
			for (unsigned int i = 0; i < Q.size(); i++) {
				std::cout << " action " << i << " -> " << Q[i] << "\n";
			}

			std::cout << "\n>> Episode " << episode << ": total reward = " << total_reward << " <<\n";
		}
		else
			std::cout << "Episode " << episode << ": total reward = " << total_reward << "\n";
	}
}

qlearner::~qlearner()
{
}