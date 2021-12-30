#include "../include/SetGraph.h"

SetGraph::SetGraph(int vertices_count) {
    vertices.resize(vertices_count);
}

SetGraph::SetGraph(const IGraph& graph) {
    vertices.resize(graph.VerticesCount());

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> children = graph.GetNextVertices(i);
        for (int j : children) {
            AddEdge(i, j);
        }
    }
}
	
void SetGraph::AddEdge(int from, int to) {
    vertices[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return vertices.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;

    for (auto& child : vertices[vertex]) {
        res.push_back(child);
    }
    return res;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;

    for (int i = 0; i < VerticesCount(); ++i) {
        if (vertices[i].find(vertex) != vertices[i].end()) {
            res.push_back(i);
        }
    }
    return res;
}