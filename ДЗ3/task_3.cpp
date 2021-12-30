#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <climits>

struct IGraph {
    virtual ~IGraph() {}
	
	// Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, int time) = 0;

	virtual int VerticesCount() const  = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int vertices_count) {
        vertices.resize(vertices_count);
    }
    ListGraph(const IGraph& graph) {}

    ~ListGraph() {}
	
	// Добавление ребра от from к to.
    void AddEdge(int from, int to, int time) override {
        vertices[from].push_back(std::pair<int, int>(to, time));
    }

	int VerticesCount() const  override {
        return vertices.size();
    }

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override {
        std::vector<std::pair<int, int>> result(vertices[vertex]);
        return result;
    }
private:
    std::vector<std::vector<std::pair<int, int>>> vertices;
};

bool relax(int from, int to, int time, std::vector<int>& dist) {
    if (dist[to] > dist[from] + time) {
        dist[to] = dist[from] + time;
        return true;
    }
    return false;
}

int dijkstra(IGraph& graph, int from, int to) {
    std::vector<int> dist(graph.VerticesCount(), INT_MAX);
    dist[from] = 0;
    std::set<std::pair<int, int>> q;

    q.emplace(0, from);
    while (!q.empty()) {
        std::pair<int, int> v = *q.begin();
        std::vector<std::pair<int, int>> children = graph.GetNextVertices(v.second);
        for (auto& next : children) {
            if (dist[next.first] > dist[v.second] + next.second) {
                auto vertexQueue = q.find(std::pair<int, int>(dist[next.first], next.first));
                if (vertexQueue != q.end()) {
                    q.erase(vertexQueue);
                }
                dist[next.first] = dist[v.second] + next.second;
                q.insert(std::pair<int, int>(dist[next.first], next.first));
            }
        }
        q.erase(q.find(v));
    }
    return dist[to];
}


void run(std::istream &is, std::ostream &os) {
    int N, M;
    is >> N >> M;
    IGraph* graph = new ListGraph(N);
    int from, to, time;
    for (int i = 0; i < M; ++i) {
        is >> from >> to >> time;
        graph->AddEdge(from, to, time);
        graph->AddEdge(to, from, time);
    }

    is >> from >> to;

    os << dijkstra(*graph, from, to);
    
    delete graph;
}

int main() {
    run(std::cin, std::cout);
    return 0;
}