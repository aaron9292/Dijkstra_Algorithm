//
// Created by aaron on 11/26/2020.
//

#include "DijkstraAlgorithm.h"

using namespace std;

DijkstraAlgorithm::DijkstraAlgorithm(Graph* g){
    graph = g;
    unordered_map<Vertex*, int> distance;
    unordered_map<Vertex*, Vertex*> predecessor;
}

void DijkstraAlgorithm::runAlgorithm(Vertex* source){ //runs dijkstra algorithm
    vector<Vertex*> vertices = graph->getVertices();

    for(int i = 0; i < vertices.size(); i++){
        if(vertices.at(i) == source){
            distance.insert(make_pair(vertices.at(i), 0));
            predecessor.insert(make_pair(vertices.at(i), source));
        }else{
            distance.insert(make_pair(vertices.at(i), INT_MAX));
            predecessor.insert(make_pair(vertices.at(i), source));
        }
    }

    int shortest;
    while(!vertices.empty()){
        shortest = INT_MAX;
        for(auto& x: distance){
            if(x.second < shortest){
                if((find(vertices.begin(), vertices.end(), x.first) != vertices.end())){
                    shortest = x.second;
                }
            }
        }

        Vertex* smallest;
        for(auto& x: distance){
            if(x.second == shortest){
                smallest = x.first;
                vertices.erase(find(vertices.begin(), vertices.end(), x.first));
            }
        }

        vector<Vertex*> adjacent;
        smallest->getAdjacentVertices(adjacent);

        for(int i = 0; i < adjacent.size(); i++){
            if(distance[smallest] + smallest->getEdgeWeight(adjacent.at(i)) < distance[adjacent.at(i)] && distance[smallest] + smallest->getEdgeWeight(adjacent.at(i)) > 0){
                distance[adjacent.at(i)] = distance[smallest] + smallest->getEdgeWeight(adjacent.at(i));
                predecessor[adjacent.at(i)] = smallest;
            }
        }
    }
}

int DijkstraAlgorithm::getShortestDistance(Vertex* vertex){ //gets vertex's distance
    int shortest = INT_MAX;
    for(auto& x: distance){
        if(x.second < shortest && x.first == vertex){
            shortest = x.second;
        }
    }
    return shortest;
}

string DijkstraAlgorithm::getPathTo(Vertex* end){ //works backward from end vertex back to source
    vector<string> path;
    string k = "";

    auto p = predecessor.find(end);
    auto d = distance.find(end);

    if(d->second == INT_MAX){
        return k;
    }else{
        path.push_back(p->first->getName());

        while(p->first->getName() != p->second->getName()){
            path.push_back(p->second->getName());
            p = predecessor.find(p->second);
        }

        if(path.size() > 1){
            for(int i = path.size() - 1; i >= 0; i--){
                if(i == 0){
                    k += path.at(i);
                }else{
                    k += path.at(i) + "-";
                }
            }
        }else{
            k = path.at(0);
        }
    }

    return k;
}

