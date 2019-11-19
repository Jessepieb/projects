// search.cpp
// Compile with: g++ search.cpp -o search

#include "search.h"
#include <queue>
typename std::vector<Vertex>::const_iterator Graph::cbegin(Vertex v) const
{
    currentVertex = v;
    return adjacents[v].cbegin();
}

typename std::vector<Vertex>::const_iterator Graph::cend() const
{
    return adjacents[currentVertex].cend();
}

Graph::GraphMap Graph::adjacents = { 
        { 'S', { 'A', 'B' } },
        { 'A', { 'B', 'D', 'S' } },
        { 'B', { 'S', 'A', 'C' } },
        { 'C', { 'B', 'E' } },
        { 'D', { 'A', 'G' } },
        { 'E', { 'C' } },
        { 'G', { 'D' } }
}; 

Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
    std::stack<Path> queue;
    std::set<Vertex> visited;
    Path path;
    
    queue.push(path);
    while (!queue.empty()) {
        path = queue.top();
        
        Vertex last;
        if (path.size() == 0) {
            last = start;
        } else {
            last = path.back();
        }
		if (goalTest(last))
            return path; // path is a vector of Vertices
     
        if (visited.find(last) == visited.end()) {
            visited.insert(last);
            for (auto it = graph.cbegin(last); it != graph.cend(); it++) { // extend path with new Vertex
                Path n = path;
                n.push_back(*it);
                queue.push(n);
            }
        }
    }
    return Path(); // return empty path
}

//TO DO
Path bfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
	std::queue<Path> queue;
	std::set<Vertex> visited;
	Path path;

	queue.push(path);

	while (!queue.empty())
	{
		path = queue.front();
		queue.pop();

		Vertex last;
		if (path.size() == 0) {
			last = start;
		}
		else
		{
			last = path.back();
		}

		if (goalTest(last))
		{
			return path;
		}

		//std::cout << last << std::endl;
		if (visited.find(last) == visited.end())
		{
			//std::cout << last;
			visited.insert(last);
			for (auto it = graph.cbegin(last); it < graph.cend(); it++)
			{
				//std::cout  << '-' << *it ;
				Path n = path;
				n.push_back(*it);
				queue.push(n);	
			}
			//std::cout << std::endl;
		}
	}
	return Path();
}

int main() 
{
    Graph graph;

    Vertex start = 'S';
    Vertex goal = 'G';

	//calculate path
    //Path path = dfs(graph, start, [&](Vertex v) { return (v == goal); });
    Path path = bfs(graph, start, [&](Vertex v) { return (v == goal); });
	std::cout << start;
	//print path
    for (auto it = path.cbegin(); it != path.cend(); it++)
    {
        std::cout << '-' << *it;
    }
	std::cout << std::endl;

    return 0;
}
