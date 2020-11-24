// ttt_ab.cpp
// Compile with: g++ -std=c++11 -o ttt_ab ttt_ab.cpp ttt.cpp

#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include "ttt.h"

enum class PlayerType { Human, Computer };

int evalLine(int first, int second, int third,const Player &player, State board){
	int score = 0;											//Deze methode het ik gevonden in een tutorial online. De scores werken goed, maar ik heb het wat compacter gemaakt door de if-statements
	//1e vak												//in te korten. Dat maakt het wel wat ingewikkeld. Elke mogelijke lijn wordt doorlopen en vakje voor vakje bekeken.
	if (board[first] == player) { score++; }				//Elke move is een aantal punten waard zolang er geen moves van de tegenstander in deze lijn zitten, 1 move is een 1 punt waard, 2 moves in 1 lijn is 10 punten waard, 3 is 100 waard.
	else if (board[first] != Player::None) { score--;}
	//2e vak
	if (board[second] == player) {
		if (score == 1) { score = 10;}
		else if (score == -1) { return 0;}
		else { score = 1;}
	}
	else if (board[second] != Player::None) {
		if (score == -1) { score = -10; }
		else if (score == 1) { return 0; }
		else { score = -1;}
	}
	//3e vak
		if (board[third] == player) {
		if (score > 0) { score *= 10;}
		else if (score < 0) { return 0; }
		else {score = 1;}
	}
	else if (board[third] != Player::None) {
		if (score < 0) { score *= 10; }
		else if (score > 1) { return 0; }
		else { score = -1; }
	}
	return score;
}
int eval(const State &board, const Player &player)
{
	int score = 0;
	//alle mogelijke winnende lijnen 
	score += evalLine(0, 1, 2, player, board);
	score += evalLine(3, 4, 5, player, board);
	score += evalLine(6, 7, 8, player, board);
	score += evalLine(0, 3, 6, player, board);
	score += evalLine(1, 4, 7, player, board);
	score += evalLine(2, 5, 8, player, board);
	score += evalLine(0, 4, 8, player, board);
	score += evalLine(2, 4, 6, player, board);
	return score;
}

std::array<int,2> alphaBeta(const State &board, int ply, int alpha, int beta)
{
	Move mv = -1;
	int score = 0;
	if (ply == 0) {	return std::array<int, 2> {mv, eval(board, getCurrentPlayer(board))};}

	std::vector<Move> moves = getMoves(board);
	if (moves.size() == 0) { return std::array<int, 2> {mv, eval(board, getCurrentPlayer(board))}; }

	std::array<int, 2> best{mv,alpha};
	for (Move &move : moves) {
		State testBoard = doMove(board, move);
		std::array<int,2> me = alphaBeta(testBoard, ply - 1, -beta, -alpha);

		if (-me[1] > alpha) {
			alpha = -me[1];
			best = std::array<int, 2> {move, alpha};
		}
		if (alpha >= beta)
			break;
	}
	return best;
}

int main()
{
	std::srand(std::time(0));

	std::map<Player,PlayerType> playerType;
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
			for (Move m: moves) std::cout << m << " ";
			std::cout << "): ";
			Move m;
			std::cin >> m;
			board = doMove(board, m);
		} else {
			board = doMove(board, alphaBeta(board, 5,INT_MIN +1,INT_MAX -1)[0]);
		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}

	return 0;
}

