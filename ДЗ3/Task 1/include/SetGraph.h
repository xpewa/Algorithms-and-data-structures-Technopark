#pragma once

#include <unordered_set>

#include "IGraph.h"

class SetGraph : public IGraph {
public:
    SetGraph(int vertices_count);
    SetGraph(const IGraph& graph);

    ~SetGraph() = default;
	
	// Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

	int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::unordered_set<int>> vertices;
};