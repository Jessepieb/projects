// ttt.h

#ifndef TTT_H
#define TTT_H

#include <tuple>
#include <array>
#include <vector>
#include <ctime>
#include <random>
#include <memory>
#include <iterator>
#include <iostream>
#include <list>


enum class Player { X, O, None };
using Move = int;
//State is our playing grid
using Board = std::array<Player, 9>;

class State {
public:
    Board board;
    int visitCount;
    double winscore; 
};

class Node {
public:
    State state;
    std::unique_ptr<Node> root;
    std::vector<Node> children;
};

class Tree {
public:
    Node root;
};

class UCB {
public:
    static double UCBvalue(int totalvisit, double nodewinscore, int nodevisit);
    static Node findBestNodeUCB(Node node);
};


// used to get a random element from a container
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

std::ostream& operator<<(std::ostream& os, const Board& state);
std::ostream& operator<<(std::ostream& os, const Player& player);

Player getCurrentPlayer(const Board& state);
Board doMove(const Board& state, const Move& m);
Player getWinner(const Board& state);
std::vector<Move> getMoves(const Board& state);


#endif // TTT_H
#pragma once
 