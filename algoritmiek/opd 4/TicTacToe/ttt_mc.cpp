// ttt_mc.cpp
// Compile with: g++ -std=c++11 -o ttt_mc ttt_mc.cpp ttt.cpp

#include <iostream>
#include <algorithm>
#include <map>
#include <iterator>
#include "ttt.h"

unsigned const n_trials = 2500;
unsigned const mc_match = 1;
unsigned const mc_other = 1;

enum class PlayerType { Human, Computer };

State mcTrial(const State& board)
{
	State b = board;
	while (getMoves(b).size() > 0) {
		std::vector<Move> posMoves = getMoves(b);
		auto randMove = select_randomly(posMoves.begin(), posMoves.end());
		b = doMove(b, *randMove);
		if (getWinner(b) != Player::None) {
			break;
		}
	}
	return b;
}

void mcUpdateScores(std::array<int, 9>& scores, const State& board, const Player& player)
{
	if (getWinner(board) == player) {
		for (int i = 0; i < board.size(); i++)
		{
			if (board[i] == player)scores[i] += mc_match;
			else if (board[i] != Player::None)scores[i] -= mc_other;
		}
	}
	else if (getWinner(board) != player)
	{
		for (int i = 0; i < board.size(); i++)
		{
			if (board[i] == player) scores[i] -= mc_match;
			else if (board[i] != Player::None) scores[i] += mc_other;
		}
	}

}

Move getBestMove(const std::array<int, 9>& scores, const State& board)
{
	std::vector<Move> possibleMoves = getMoves(board);
	std::vector<Move> bestMove{ 0 };
	if (possibleMoves.size() == 1) {
		return possibleMoves[0];
	}

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		if (scores[possibleMoves[i]] > scores[bestMove[0]]) {
			bestMove.clear();
			bestMove.push_back(possibleMoves[i]);
		}
		else if (scores[possibleMoves[i]] == bestMove[0]) {
			bestMove.push_back(possibleMoves[i]);
		}
	}
	return *select_randomly(bestMove.begin(), bestMove.end());
}

Move mcMove(const State& board, const Player& player)
{
	std::array<int, 9> boardScores{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i <  n_trials; i++)
	{
		State trail = board;
		trail = mcTrial(trail);
		mcUpdateScores(boardScores, trail, getCurrentPlayer(trail));
	}
	return getBestMove(boardScores, board);
}

int main()
{
	std::srand(std::time(0));

	std::map<Player, PlayerType> playerType;
	playerType[Player::O] = PlayerType::Human;
	playerType[Player::X] = PlayerType::Computer;

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
			board = doMove(board, mcMove(board, getCurrentPlayer(board)));

		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}

	return 0;
}
