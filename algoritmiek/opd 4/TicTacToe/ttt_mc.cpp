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

//Steps:
/*
1. Selection with UCB from tree root (getBestMove)
2. if leaf Node (No children and no terminal state), expand into possible nodes (expandNode)
3. from these nodes, take random node and playout, this results in a win, loss or tie (mcTrail)
4. up wincounter and visitcounter for node and do so recursively for it's parents (updateScored)
*/


bool inProgress(Board b) {
	Player getWin = getWinner(b);
	if (getWin == Player::None && getMoves(b).size() > 0) {
		return true;
	}
	else {
		return false;
	}
}

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

//expansion
void expandNode(Node node) {
	std::vector<Move> posmoves = getMoves(node.state.board);

	for (Move m : posmoves) {
		
		Board newboard = node.state.board;
		newboard = doMove(newboard, m);
		State s = State(newboard,0,0);
		Node newNode = Node(s,&node);
		node.children.push_back(newNode);
	}
}

//backpropagation
void mcUpdateScores(std::array<int, 9>& scores, const Board& board, const Player& player)
{
}

//selection
Move getBestMove(const std::array<int, 9>& scores, const Board& board)
{
	Node rootNode = Node(State(board, 0, 0), NULL);
	Tree tree = Tree(rootNode);
	
	unsigned i = 0;
	rootNode = tree.root;

	while (i < n_trials) {
		Node promisingNode = UCB::findBestNodeUCT(rootNode);

		if (inProgress(promisingNode.state.board)) {
			expandNode(promisingNode);
		}
		Node exploreNode;
		if (promisingNode.children.size() > 0) {
			//exploreNode = promisingNode.children[select_randomly(promisingNode.children.begin(), promisingNode.children.end())];
		}
		i++;
	}
	
	return Move();
}


double UCB::UCBvalue(int totalVisit, double nodeWinscore, int nodeVisit) {
	if (nodeVisit == 0) {
		return INT_MAX;
	}
	return ((double)nodeWinscore) / (double)nodeVisit + 1.41 * (log(totalVisit) / (double)nodeVisit);
}

Node UCB::findBestNodeUCT(Node node) {
	//const std::vector<Node>::iterator np;
	unsigned np;
	double max = -1;
	int parentvisit = node.state.visitCount;
	for (unsigned it = 0; it != node.children.size(); it++)
	{
		double result = UCB::UCBvalue(parentvisit, node.children[it].state.winscore, node.children[it].state.visitCount);
		if (result > max) { max = result; np = it; }
	};
	auto& n = node.children[np];
	return n;
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

