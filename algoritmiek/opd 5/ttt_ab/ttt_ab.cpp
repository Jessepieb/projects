// ttt_ab.cpp
// Compile with: g++ -std=c++11 -o ttt_ab ttt_ab.cpp ttt.cpp

#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include "ttt.h"
#include "ttt_ab.h"

enum class PlayerType { Human, Computer };

int evalLine(int first, int second, int third, const Player player, State board) {
	int score = 0;
	//1e vak
	if (board[first] == player) { score++; }
	else if (board[first] != Player::None) { score--; }
	//2e vak
	if (board[second] == player) {
		if (score == 1) { score = 10; }
		else if (score == -1) { return 0; }
		else { score = 1; }
	}
	else if (board[second] != Player::None) {
		if (score == -1) { score = -10; }
		else if (score == 1) { return 0; }
		else { score = -1; }
	}
	//3e vak
	if (board[third] == player) {
		if (score > 0) { score *= 10; }
		else if (score < 0) { return 0; }
		else { score = 1; }
	}
	else if (board[third] != Player::None) {
		if (score < 0) { score *= 10; }
		else if (score > 1) { return 0; }
		else { score = -1; }
	}
	return score;
}


int eval(const State& board, const Player& player)
{
	int score = 0;

	for (int i = 0; i < 3; i++)
	{
		score += evalLine(i * 3, (i * 3) + 1, (i * 3) + 2, player, board);
		score += evalLine(i, (i + 3), (6 + i), player, board);
	}
	score += evalLine(0, 4, 8, player, board);
	score += evalLine(2, 4, 6, player, board);

	return score;
}

std::array<int, 2> alphaBeta(const State& board, int ply, int alpha, int beta)
{
	Move mv = -1;
	int score = 0;
	if (ply == 0) {return std::array<int, 2> {mv, eval(board, getCurrentPlayer(board))};}

	std::vector<Move>posmoves = getMoves(board);
	if (posmoves.size() == 0) {return std::array<int, 2> {mv, eval(board, getCurrentPlayer(board))};}


	std::array<int, 2> best{ mv, alpha};
	for (Move& move : posmoves) {
		State newboard = doMove(board, move);
		std::array<int, 2> ab = alphaBeta(newboard, ply - 1, -beta, -alpha);

		if (-ab[1] > alpha) {
			alpha = -ab[1];
			best = std::array<int, 2>{move, alpha};
		}

		if (alpha >= beta) {
			break;
		}
	}
	return best;
}

int main()
{
	std::srand(std::time(0));

	std::map<Player, PlayerType> playerType;
	playerType[Player::X] = PlayerType::Computer;
	playerType[Player::O] = PlayerType::Human;

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
			board = doMove(board, alphaBeta(board, 5, INT_MIN +1, INT_MAX -1)[0]);
		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}

	return 0;
}

