// peggame.h

#ifndef PEGGAME_H
#define PEGGAME_H

#include <tuple>
#include <array>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <stack>
#include <set>

using Move = std::tuple<int, int, int, int>;
// make state an array of type bool with a size of 15
using State = std::array<bool, 15>;
// make Vertex equal to State
using Vertex = State;
// make Path a vector of vertices
using Path = std::vector<Vertex>;

class Graph
{
public:
    typename std::vector<Vertex>::const_iterator cbegin(Vertex v) const;
    typename std::vector<Vertex>::const_iterator cend() const;
private:
    // make adjacents a changable vector of vertices
    mutable std::vector<Vertex> adjacents;
};

int coord_to_idx(int r, int c);

std::ostream& operator<<(std::ostream& os, const Vertex& state);

// declare functions
Vertex doMove(const Vertex& v, const Move& m);
Path dfs(const Graph& graph, const Vertex& start, std::function<bool(const Vertex & vertex)> goalTest);
Path bfs(const Graph& graph, const Vertex& start, std::function<bool(const Vertex & vertex)> goalTest);

#endif // PEGGAME_H


