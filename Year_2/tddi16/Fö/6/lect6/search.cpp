struct Node {
	vector<int> edges;
	bool visited = false;
	int previous;
};

vector<Node> graph;
// end DECL

bool dfs(int from, int to) {
	if (from == to)
		return true;

	for (int x : graph[from].edges) {
		if (!graph[x].visited) {
			graph[x].visited = true;
			if (dfs(x, to))
				return true;
		}
	}
	return false;
}
// end DFS


bool bfs(int from, int to) {
	queue<int> q; q.push(from);
	graph[from].visited = true;
	while (!q.empty()) {
		int current = q.top(); q.pop();
		for (int x : graph[current].edges) {
			if (x == to) return true;
			// om x inte redan är besökt, markera
			// den som besökt och lägg på kö
		}
	}
	return false;
}
// end BFS


bool dijkstra(int from, int to) {
	priority_queue<...> q; q.push(from);
	while (!q.empty()) {
		int current = q.top(); q.pop();
		if (graph[current].visited) continue;
		graph[current].visited = true;
		if (current == to) return true;
		for (int x : graph[current].edges) {
			// Uppdatera x och lägg på kön om bättre
		}
	}
	return false;
}
// end DIJKSTRA
