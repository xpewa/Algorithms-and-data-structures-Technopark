#include "../include/MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertices_count) {
    vertices.resize(vertices_count);
    for (int i = 0; i < vertices.size(); ++i) {
        vertices[i].resize(vertices_count);
    }
}

MatrixGraph::MatrixGraph(const IGraph& graph) {
    vertices.resize(graph.VerticesCount());
    for (int i = 0; i < vertices.size(); ++i) {
        vertices[i].resize(graph.VerticesCount());
    }

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> children = graph.GetNextVertices(i);
        for (int j : children) {
            AddEdge(i, j);
        }
    }
}
	
void MatrixGraph::AddEdge(int from, int to) {
    vertices[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return vertices.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < VerticesCount(); ++i) {
        if (vertices[vertex][i]) {
            res.push_back(i);
        }
    }
    return res;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < VerticesCount(); ++i) {
        if (vertices[i][vertex]) {
            res.push_back(i);
        }
    }
    return res;
}