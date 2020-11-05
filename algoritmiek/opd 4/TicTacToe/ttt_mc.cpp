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

//simulation
Board mcTrial(const Board& board)
{
	Board newboard = board;
	std::vector<Move> posMove = getMoves(newboard);
	while (posMove.size() > 0) {
		auto randMove = select_randomly(posMove.begin(), posMove.end());
		int& result = randMove[0];
		newboard = doMove(newboard, result);
		posMove = getMoves(newboard);
		std::cout << newboard << std::endl;
	}
	return newboard;
}

Move mcMove(const Board& board, const Player& player)
{
	mcTrial(board);
	return Move();
}

void mcUpdateScores(std::array<int, 9>& scores, const Board& board, const Player& player)
{
}

Move getBestMove(const std::array<int, 9>& scores, const Board& board)
{

	return Move();
}


double UCB::UCBvalue(int totalvisit, double nodewinscore, int nodevisit) {
	if (nodevisit == 0) {
		return INT_MAX;
	}
	return ((double)nodewinscore) / (double)nodevisit + 1.41 * (log(totalvisit) / (double)nodevisit);
}

Node UCB::findBestNodeUCB(Node node) {
	const Node& np;
	int parentvisit = node.state.visitCount;
	double max = 0;
	for (int i = 0; i<node.children.size(); i++)
	{
		double result = UCB::UCBvalue(parentvisit,node.children[i].state.winscore, node.children[i].state.visitCount);
		if (result > max) {
			max = result;
			np = const_cast<Node&>(node.children[i]);
		}
	};
	return np;

	return Node();
}

int main()
{
	std::srand(std::time(0));

	std::map<Player, PlayerType> playerType;
	playerType[Player::X] = PlayerType::Human;
	playerType[Player::O] = PlayerType::Computer;

	Board board = {
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
			//board = doMove(board,mcMove(board, getCurrentPlayer(board)));
			board = mcTrial(board);
		}
		//std::cout << board << std::endl;
		moves = getMoves(board);
	}
	std::cout << getWinner(board) << std::endl;

	return 0;
}

