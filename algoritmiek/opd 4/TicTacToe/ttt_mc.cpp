// ttt_mc.cpp
// Compile with: g++ -std=c++11 -o ttt_mc ttt_mc.cpp ttt.cpp

#include <iostream>
#include <algorithm>
#include <map>
#include<list>
#include "ttt.h"

unsigned const n_trials = 1000;
unsigned const mc_match = 1;
unsigned const mc_other = 1;

enum class PlayerType { Human, Computer };


Move mcMove(const State& board, const Player& player)
{
	return Move();
}


//simulation
State mcTrial(const State& board)
{
	State newboard = board;
	std::vector<Move> posMove = getMoves(newboard);
	while (posMove.size() > 0) {
		auto randMove = select_randomly(posMove.begin(), posMove.end());
		int& result = randMove[0];
		newboard = doMove(newboard, result);
		posMove = getMoves(newboard);
	}
	return newboard;
}

void mcUpdateScores(std::array<int, 9>& scores, const State& board, const Player& player)
{
}

Move getBestMove(const std::array<int, 9>& scores, const State& board)
{

	return Move();
}



int main()
{
	std::srand(std::time(0));

	std::map<Player, PlayerType> playerType;
	playerType[Player::X] = PlayerType::Human;
	playerType[Player::O] = PlayerType::Computer;

	State board = {
		Player::None, Player::None, Player::None,
		Player::None, Player::None, Player::None,
		Player::None, Player::None, Player::None };
	std::cout << board << std::endl;


	std::vector<Move> moves = getMoves(board);
	while (moves.size() > 0) {
		if (playerType[getCurrentPlayer(board)] == PlayerType::Human) {
			std::cout << "+-+-+-+" << std::endl <<
				"|0|1|2|" << std::endl <<
				"+-+-+-+" << std::endl <<
				"|3|4|5|" << std::endl <<
				"+-+-+-+" << std::endl <<
				"|6|7|8|" << std::endl <<
				"+-+-+-+" << std::endl << std::endl;
			std::cout << "Enter a move ( ";
			for (Move m : moves) std::cout << m << " ";
			std::cout << "): ";
			Move m;
			std::cin >> m;
			board = doMove(board, m);
		}
		else {
			board = mcTrial(board);
		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}
	std::cout << getWinner(board) << std::endl;

	return 0;
}

