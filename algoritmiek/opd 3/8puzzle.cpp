// 8puzzle.cpp
// Compile with: g++ 8puzzle.cpp -o 8puzzle

#include "8puzzle.h"

const int size = 5;

typename std::vector<Vertex>::const_iterator Graph::cbegin(Vertex v) const
{
    adjacents.clear();

    for (int r=0; r<size; r++) {
		for (int c=0; c<size; c++) {
			std::cout << r << "-" << c << "\n";

			
			if (v[r][c] == 1) {
                if (c < 3 && v[r][c+1] == 1 && v[r][c+2] == 0) adjacents.push_back(doMove(v,Move::r)); 
				if (c>2 &&v[r][c - 1] == 1 && v[r][c - 2] == 0) adjacents.push_back(doMove(v, Move::l));


                if (r< 3 && v[r+1][c] == 1 && v[r+2][c] == 0) adjacents.push_back(doMove(v,Move::ld));
				if (r < 3 && v[r+1][c+1] == 1 && v[r+2][c+2] == 0) adjacents.push_back(doMove(v, Move::rd));

				if (r> 2 && c>=2 && v[r - 1][c-1] == 1 && v[r - 2][c-2] == 0) adjacents.push_back(doMove(v, Move::lu));
				if (r> 2 && v[r-1][c] == 1 && v[r-2][c] == 0) adjacents.push_back(doMove(v, Move::ru));
				
            }
        }
    }
	std::cout << "\n";
    return adjacents.cbegin();
}

typename std::vector<Vertex>::const_iterator Graph::cend() const
{
    return adjacents.cend();
}

Vertex doMove(const Vertex &v, const Move &m)
{
    bool done=false;
    Vertex n = v;

    for (int r=0; r<size && !done; r++) {
        for (int c=0; c<size && !done; c++) {
            if (v[r][c] == 1) {
                switch(m) {
					case Move::r: std::swap(n[r][c + 2], n[r][c]); n[r][c + 1] == 0; done = true; break;
					

					case Move::ld: std::swap(n[r][c], n[r + 2][c]); n[r + 1][c] == 0; done = true; break;
					case Move::rd: std::swap(n[r][c], n[r + 2][c + 2]); n[r + 1][c + 1] == 0; done = true; break;

					case Move::lu: std::swap(n[r][c], n[r - 2][c - 2]); n[r - 1][c - 1] == 0; done = true; break;
					case Move::ru: std::swap(n[r][c], n[r-2][c]); 
						n[r - 1][c] == 0; done = true; break;
					case Move::l: std::swap(n[r][c - 2], n[r][c]); n[r][c - 1] == 0; done = true; break;

                }
            }
        }
    }
    return n;
}

std::ostream &operator<<(std::ostream &os, const Vertex &state)
{
    for (int r=0; r<size; r++) {
        for (int c=0; c<size; c++) {
            if (state[r][c] == 0 || state[r][c] == 1) 
			{
		os << state[r][c];
            } else {
                os << " ";
            }
        }
        os << std::endl;
    }
    return os;
}

Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
    std::stack<Path> queue;
    std::set<Vertex> visited;
    Path path;
    
    queue.push(path);
    while (!queue.empty()) {
        path = queue.top();
        queue.pop();
        
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
    return Path();
}
#include <list>
Path bfs(const Graph& graph, const Vertex& start, std::function<bool(const Vertex& vertex)> goalTest)
{
	std::list<Path> queue;
	std::set<Vertex> visited;
	Path path;

	queue.push_front(path);

	while (!queue.empty()) {

		path = queue.front();
		queue.pop_front();

		Vertex last;

		if (path.size() == 0)
		{
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

		if (visited.find(last) == visited.end()) {
			visited.insert(last);
			for (auto it = graph.cbegin(last); it != graph.cend(); it++) {
				Path n = path;
				n.push_back(*it);
				queue.push_back(n);
			}
		}
	}
	return Path();
}

int main() 
{
    Graph graph;

    Vertex start = {{
		{{0,2,2,2,2}},
        {{1,1,2,2,2}},
        {{1,1,1,2,2}},
		{{1,1,1,1,2}},
		{{1,1,1,1,1}}
    }};

    Vertex goal = {{
        {{0,2,2,2,2}},
        {{0,0,2,2,2}},
        {{0,0,0,2,2}},
		{{0,0,0,0,2}},
		{{0,0,1,0,0}}
    }};

    Path path = bfs(graph, start, [&](Vertex v) { return (v == goal); });

    std::cout << start << std::endl;
    for (auto it = path.cbegin(); it != path.cend(); it++)
    {
        std::cout << *it << std::endl;
	}
    return 0;
}

