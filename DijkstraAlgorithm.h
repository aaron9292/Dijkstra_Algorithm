//
// Created by aaron on 11/26/2020.
//

#ifndef DIJKSTRA_ALGORITHM_BASE_DIJKSTRAALGORITHM_H
#define DIJKSTRA_ALGORITHM_BASE_DIJKSTRAALGORITHM_H
#include "Vertex.h"
#include "Graph.h"
#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class DijkstraAlgorithm {
public:
    DijkstraAlgorithm(Graph* g);
    void runAlgorithm(Vertex* vertex);
    int getShortestDistance(Vertex* vertex);
    string getPathTo(Vertex* end);
private:
    Graph* graph;
    unordered_map<Vertex*, int> distance;
    unordered_map<Vertex*, Vertex*> predecessor;
};


#endif //DIJKSTRA_ALGORITHM_BASE_DIJKSTRAALGORITHM_H
