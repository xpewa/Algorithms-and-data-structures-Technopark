#include "../include/ArcGraph.h"

ArcGraph::ArcGraph(int vertices_count) {
    vertices.resize(vertices_count);
}

ArcGraph::ArcGraph(const IGraph& graph) {
    vertices.resize(graph.VerticesCount());

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> children = graph.GetNextVertices(i);
        for (int j : children) {
            AddEdge(i, j);
        }
    }
}
	
void ArcGraph::AddEdge(int from, int to) {
    std::pair<int, int> edge = std::make_pair(from, to);
    vertices.push_back(edge);
}

int ArcGraph::VerticesCount() const {
    return vertices.size() / 2;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;

    for (auto i : vertices) {
        if (i.first == vertex) {
            res.push_back(i.second);
        }
    }
    return res;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;

    for (auto i : vertices) {
        if (i.second == vertex) {
            res.push_back(i.first);
        }
    }
    return res;
}