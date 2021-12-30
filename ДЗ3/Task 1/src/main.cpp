// g++ main.cpp ListGraph.cpp MatrixGraph.cpp SetGraph.cpp ArcGraph.cpp -o main

#include <iostream>
#include <queue>
#include <stack>

#include "../include/IGraph.h"
#include "../include/ListGraph.h"
#include "../include/MatrixGraph.h"
#include "../include/ArcGraph.h"
#include "../include/SetGraph.h"

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

void dfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::stack<int> s;
    for (int vertex = 0; vertex < graph.VerticesCount(); ++vertex) {
        if (!visited[vertex]) {
            s.push(vertex);
        }
        while (!s.empty()) {
            int v = s.top();
            visited[v] = true;
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

void test1(std::istream &is, std::ostream &os) {
    IGraph* graph1 = new ListGraph(7);
    graph1->AddEdge(0, 1);
    graph1->AddEdge(1, 5);
    graph1->AddEdge(6, 0);
    graph1->AddEdge(1, 2);
    graph1->AddEdge(2, 3);
    graph1->AddEdge(3, 4);
    graph1->AddEdge(4, 2);

    os << "------ BFS (1) ------" << std::endl;
    bfs(*graph1, [](int v) {
        std::cout << v << std::endl;
    });

    IGraph* graph2 = new MatrixGraph(*graph1);
    IGraph* graph3 = new SetGraph(*graph2);
    IGraph* graph4 = new ArcGraph(*graph3);

    os << "------ BFS (4) ------" << std::endl;
    bfs(*graph4, [](int v) {
        std::cout << v << std::endl;
    });

    delete graph1;
    delete graph2;
    delete graph3;
    delete graph4;
}

void test2(std::istream &is, std::ostream &os) {
    IGraph* graph1 = new ListGraph(9);
    IGraph* graph2 = new MatrixGraph(9);
    IGraph* graph3 = new SetGraph(9);
    IGraph* graph4 = new ArcGraph(9);

    graph1->AddEdge(0, 1);
    graph1->AddEdge(1, 5);
    graph1->AddEdge(6, 0);
    graph1->AddEdge(1, 2);
    graph1->AddEdge(2, 3);
    graph1->AddEdge(3, 4);
    graph1->AddEdge(4, 2);
    graph1->AddEdge(0, 7);
    graph1->AddEdge(0, 8);

    graph2->AddEdge(0, 1);
    graph2->AddEdge(1, 5);
    graph2->AddEdge(6, 0);
    graph2->AddEdge(1, 2);
    graph2->AddEdge(2, 3);
    graph2->AddEdge(3, 4);
    graph2->AddEdge(4, 2);
    graph2->AddEdge(0, 7);
    graph2->AddEdge(0, 8);

    graph3->AddEdge(0, 1);
    graph3->AddEdge(1, 5);
    graph3->AddEdge(6, 0);
    graph3->AddEdge(1, 2);
    graph3->AddEdge(2, 3);
    graph3->AddEdge(3, 4);
    graph3->AddEdge(4, 2);
    graph3->AddEdge(0, 7);
    graph3->AddEdge(0, 8);

    graph4->AddEdge(0, 1);
    graph4->AddEdge(1, 5);
    graph4->AddEdge(6, 0);
    graph4->AddEdge(1, 2);
    graph4->AddEdge(2, 3);
    graph4->AddEdge(3, 4);
    graph4->AddEdge(4, 2);
    graph4->AddEdge(0, 7);
    graph4->AddEdge(0, 8);

    os << "--------------- ListGraph ---------------" << std::endl;
    os << "------ DFS ------" << std::endl;
    dfs(*graph1, [](int v) {
        std::cout << v << std::endl;
    });

    os << "------ BFS ------" << std::endl;
    bfs(*graph1, [](int v) {
        std::cout << v << std::endl;
    });


    os << "--------------- MatrixGraph ---------------" << std::endl;
    os << "------ DFS ------" << std::endl;
    dfs(*graph2, [](int v) {
        std::cout << v << std::endl;
    });

    os << "------ BFS ------" << std::endl;
    bfs(*graph2, [](int v) {
        std::cout << v << std::endl;
    });


    os << "--------------- SetGraph ---------------" << std::endl;
    os << "------ DFS ------" << std::endl;
    dfs(*graph3, [](int v) {
        std::cout << v << std::endl;
    });

    os << "------ BFS ------" << std::endl;
    bfs(*graph3, [](int v) {
        std::cout << v << std::endl;
    });

    
    os << "--------------- ArcGraph ---------------" << std::endl;
    os << "------ DFS ------" << std::endl;
    dfs(*graph4, [](int v) {
        std::cout << v << std::endl;
    });

    os << "------ BFS ------" << std::endl;
    bfs(*graph4, [](int v) {
        std::cout << v << std::endl;
    });

    delete graph1;
    delete graph2;
    delete graph3;
    delete graph4;
}

int main() {
    test1(std::cin, std::cout);
    test2(std::cin, std::cout);
    return 0;
}