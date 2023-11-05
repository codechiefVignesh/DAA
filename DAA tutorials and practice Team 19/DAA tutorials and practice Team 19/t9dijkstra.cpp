#include <bits/stdc++.h>
using namespace std;

class Node {
public:
	int vertex_num;
	vector<pair<int, int>> children;
	Node(int vertex_num) {
		this->vertex_num = vertex_num;
	}
	void add_child(int v_num, int length) {
		pair<int, int> p;
		p.first = v_num;
		p.second = length;
		children.push_back(p);
	}
};

vector<int> find_shortest_path(vector<Node*> G, int source, vector<int>& path) {
	vector<int> dist(G.size());
	bool visited[G.size()];
	for(int i = 0; i < G.size(); i++) {
		visited[i] = false;
		path[i] = -1;
		dist[i] = INT_MAX;
	}
	dist[source] = 0;
	path[source] = -1;
	int current = source;
	unordered_set<int> st;
	while(true) {
		visited[current] = true;
		for(int i = 0; i < G[current]->children.size(); i++) {
			int vertex = G[current]->children[i].first;
			if(visited[vertex]) continue;
			st.insert(vertex);
			int newdist = dist[current] + G[current]->children[i].second;
			if(newdist < dist[vertex]) {
				dist[vertex] = newdist;
				path[vertex] = current;
			}
		}
		st.erase(current);
		if(st.empty()) break;
		int min_dist = INT_MAX;
		int index = 0;
		for(int a: st) {
			if(dist[a] < min_dist) {
				min_dist = dist[a];
				index = a;
			}
		}
		current = index;
	}
	return dist;
}

int main() {
	vector<Node*> G;
	int n, source, num_edges;
    cout << "Enter no.of vertices: ";
    cin >> n;
    cout << "Enter no.of edges: ";
    cin >> num_edges;
	for(int i = 0; i < n; i++) {
		Node* newnode = new Node(i);
		G.push_back(newnode);
	}
    for(int i = 0; i < num_edges; i++) {
        int v1, v2, w;
        cout << "Enter edge " << i + 1 << ": ";
        cin >> v1 >> v2;
        cout << "Enter weight of edge " << v1 << " to " << v2 << ": ";
        cin >> w;
        G[v1]->add_child(v2, w);
    }
    cout << "Enter source vertex: ";
    cin >> source;
	vector<int> path(G.size());
	vector<int> shortest_paths = find_shortest_path(G, source, path);
	for(int i = 0; i < shortest_paths.size(); i++) {
		if(shortest_paths[i] == INT_MAX) {
			cout << source << " and " << i << " are not connected" << endl;
			continue;
		}
		cout << source << " to "<< i << ": " << shortest_paths[i] << endl;
	}
	return 0;
}