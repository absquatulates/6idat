#include <queue>

class Point {
public:
	int x, y;
	// ...
	bool operator==(Point const& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
};

bool map[width][height];
// end DECL

bool bfs(Point from, Point to) {
	std::queue<Point> q; q.push(from);
	bool visited[width][height] = false;
	visited[from.x][from.y] = true;
	while (!q.empty()) {
		Point current = q.top(); q.pop();
		for (Point x : current.neighbors()) {
			if (x == current) return true;
			// Om 'x' ej besökt, markera och lägg på kö.
		}
	}
	return false;
}
// end BFS
