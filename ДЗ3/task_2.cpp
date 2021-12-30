#include <iostream>
#include <vector>
#include <queue>

struct IGraph {
    virtual ~IGraph() {}
	
	// Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int vertices_count) {
        vertices.resize(vertices_count);
    }
    ListGraph(const IGraph& graph) {}

    ~ListGraph() {}
	
	// Добавление ребра от from к to.
    void AddEdge(int from, int to) override {
        vertices[from].push_back(to);
    }

	int VerticesCount() const  override {
        return vertices.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        std::vector<int> result(vertices[vertex].begin(), vertices[vertex].end());
        return result;
    }
    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> result;

        for (int parent = 0; parent < vertices.size(); ++parent) {
            for (auto& child : vertices[parent]) {
                if (child == vertex) {
                    result.push_back(parent);
                    break;
                }
            }
        }

        return result;
    }
private:
    std::vector<std::vector<int>> vertices;
};


int count_shortest_way(IGraph& graph, int from, int to) {
    std::vector<int> paths_count(graph.VerticesCount(), 0);
    paths_count[from] = 1;
    std::vector<int> dist(graph.VerticesCount(), 0);

    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> q;
    int vertex = from;
    visited[vertex] = true;
    q.push(vertex);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        std::vector<int> children = graph.GetNextVertices(v);
        for (auto& next : children) {
            if ((dist[next] == 0) || (dist[next] > dist[v] + 1)) {
                dist[next] = dist[v] + 1;
                paths_count[next] = paths_count[v];
            }
            else if (dist[next] == dist[v] + 1) {
                paths_count[next] += paths_count[v];
            }
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    return paths_count[to];
}

void run(std::istream &is, std::ostream &os) {
    int v, n;
    is >> v >> n;
    IGraph* graph = new ListGraph(v);
    int u, w;
    for (int i = 0; i < n; ++i) {
        is >> u >> w;
        graph->AddEdge(u, w);
        graph->AddEdge(w, u);
    }

    is >> u >> w;

    os << count_shortest_way(*graph, u, w);
    
    delete graph;
}

int main() {
    run(std::cin, std::cout);
    return 0;
}