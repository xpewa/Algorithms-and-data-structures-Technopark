#pragma once

#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    MatrixGraph(int vertices_count);
    MatrixGraph(const IGraph& graph);

    ~MatrixGraph() = default;
	
	// Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

	int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<bool>> vertices;
};