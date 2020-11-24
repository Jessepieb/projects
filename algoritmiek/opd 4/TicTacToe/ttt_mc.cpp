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
4. up wincounter and visitcounter for node and do so recursively for it's parents (updateScores)
*/


bool inProgress(Board& b) {
	Player getWin = getWinner(b);
	if (getMoves(b).size() > 0 && getWin == Player::None) {
		return true;
	}
	else {
		return false;
	}
}
Node selectPromNode(Node& rootnode) {
	Node node = rootnode;
	while (node.children.size() != 0) {
		node = UCB::findBestNodeUCT(node);
	}
	return node;
}
void expandNode(Node& node) {
	std::vector<Move> posmoves = getMoves(node.state.board);

	for (Move m : posmoves) {

		Board newboard = node.state.board;
		newboard = doMove(newboard, m);
		State s = State(newboard, m);
		Node newNode = Node(s, &node);
		node.children.push_back(newNode);
	}
}
Board mcTrial(const Board& board)
{
	Board newboard = board;
	std::vector<Move> posMove = getMoves(newboard);
	while (inProgress(newboard)) {
		auto randMove = select_randomly(posMove.begin(), posMove.end());
		int& result = randMove[0];
		newboard = doMove(newboard, result);
		posMove = getMoves(newboard);
		//std::cout << newboard << std::endl;
	}
	return newboard;
}
void backpropagation(Node n, Board b) {
	Node* tempNode = &n;
	while (tempNode != nullptr) {
		tempNode->state.visitCount++;
		if (getWinner(b) == Player::X) {
			tempNode->state.addScore(1);
		}
		tempNode = tempNode->parent;
	}
};


Move mcMove(const Board& board, const Player& player)
{
	
	mcTrial(board);
	return Move();
}

//void mcUpdateScores(std::array<int, 9>& scores, const Board& board, const Player& player)
//{
//}



Node getBestChildNode(Node& parentNode) {
	int max = 0;
	Node bestNode = parentNode;
	for (size_t i = 0; i < parentNode.children.size(); i++)
	{
		if (parentNode.children[i].state.visitCount > max) {
			max = parentNode.children[i].state.visitCount;
			bestNode = parentNode.children[i];
		}
	}
	return bestNode;
}

double UCB::UCBvalue(int totalVisit, double nodeWinscore, int nodeVisit) {
	if (nodeVisit == 0) {
		return INT_MAX;
	}
	return ((double)nodeWinscore) / (double)nodeVisit + 1.41 * (log(totalVisit) / (double)nodeVisit);
}

Move getBestMove(const Board& board)
{
	Tree tree = Tree(Node(State(board, NULL), NULL));

	unsigned i = 0;
	Node* rootNode = &tree.root;

	while (i < n_trials) {
		Node promisingNode = selectPromNode(*rootNode);

		if (inProgress(promisingNode.state.board)) {
			expandNode(promisingNode);
		}
		Node exploreNode = promisingNode;
		if (exploreNode.children.size() > 0) {
			auto iter = select_randomly(exploreNode.children.begin(), exploreNode.children.end());
			exploreNode = *iter;
		}
		Board playout = mcTrial(exploreNode.state.board);
		backpropagation(exploreNode, playout);
		i++;
	}

	Node Bestnode = getBestChildNode(*rootNode);

	return Bestnode.state.move;
}


Node UCB::findBestNodeUCT(Node node) {
	Node newNode = node;
	double max = -1;
	int parentvisit = node.state.visitCount;
		for (std::vector<Node>::iterator it = node.children.begin(); it != node.children.end(); ++it)
		{
			double result = UCB::UCBvalue(parentvisit, it->state.winscore, it->state.visitCount);
			if (result > max) { max = result; newNode = (std::vector<Node>::iterator::value_type) * it; }
		}
	return newNode;
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
			board = doMove(board,getBestMove(board));
		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}
	std::cout << getWinner(board) << std::endl;

	return 0;
}

