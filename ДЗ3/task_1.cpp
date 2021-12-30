#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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

/*
//нерекурсивно
void dfs_aux(const IGraph& graph, int vertex,
             std::vector<bool>& visited, void (*callback)(int v)) {
    if (!visited[vertex]) {
        visited[vertex] = 1;
        callback(vertex);
    }

    std::vector<int> children = graph.GetNextVertices(vertex);
        for (int i = 0; i < children.size(); ++i) {
            if (!visited[children[i]]) {
                visited[children[i]] = 1;
                callback(children[i]);
            }
        }
}

void dfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int vertex = 0; vertex < graph.VerticesCount(); ++vertex) {
        dfs_aux(graph, vertex, visited, callback);
    }
}
*/


void dfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::stack<int> s;
    for (int vertex = 0; vertex < graph.VerticesCount(); ++vertex) {
        if (!visited[vertex]) {
            s.push(vertex);
        }
        while (!s.empty()) {
            int v = s.top();
            visited[vertex] = true;
            s.pop();
            callback(v);

            std::vector<int> children = graph.GetNextVertices(v);
            for (auto& child : children) {
                if (!visited[child]) {
                    s.push(child);
                }
            }
        }
    }
}


void bfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> q;
    for (int vertex = 0; vertex < graph.VerticesCount(); ++vertex) {
        if (!visited[vertex]) {
            visited[vertex] = true;
            q.push(vertex);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                callback(v);
                std::vector<int> children = graph.GetNextVertices(v);
                for (auto& child : children) {
                    if (!visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }
        }
    }
}


void run(std::istream &is, std::ostream &os) {
    IGraph* graph = new ListGraph(9);
    graph->AddEdge(0, 1);
    graph->AddEdge(1, 5);
    graph->AddEdge(6, 0);
    graph->AddEdge(1, 2);
    graph->AddEdge(2, 3);
    graph->AddEdge(3, 4);
    graph->AddEdge(4, 2);
    graph->AddEdge(0, 7);
    graph->AddEdge(0, 8);

    os << "------ DFS ------" << std::endl;
    dfs(*graph, [](int v) {
        std::cout << v << std::endl;
    });

    os << "------ BFS ------" << std::endl;
    bfs(*graph, [](int v) {
        std::cout << v << std::endl;
    });

    delete graph;
}

int main() {
    run(std::cin, std::cout);
    return 0;
}
