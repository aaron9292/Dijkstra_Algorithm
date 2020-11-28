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

void DijkstraAlgorithm::runAlgorithm(Vertex* source){
    vector<Vertex*> vertices = graph->getVertices(); //gets list of all vertices

    distance.insert(make_pair(source, 0));
    predecessor.insert(make_pair(source, nullptr));
    for(int i = 1; i < vertices.size(); i++){ //inserts all pairs into distance and predecessor
        if(vertices.at(i) != source){
            distance.insert(make_pair(vertices.at(i), INT_MAX));
            predecessor.insert(make_pair(vertices.at(i), nullptr));
        }
    }

    int shortest = INT_MAX;

    int runs = 1;
    while(runs != 0){
        for(auto& x: distance){ //gets number of shortest distance
            if(x.second < shortest){
                shortest = x.second;
            }
        }

        Vertex* smallest;
        for(auto& x: distance){ //finds vertex with the smallest distance
            if(x.second == shortest){
                smallest = x.first; //make smallest the vertex with shortest distance
                vertices.erase(find(vertices.begin(), vertices.end(), x.first)); //pops vertices with the shortest value
            }
        }

        vector<Vertex*> adjacent; //gets list of adjacent vertices from the current smallest vertex
        smallest->getAdjacentVertices(adjacent);

        /*for(int i = 0; i < adjacent.size(); i++){
            if(distance.at(smallest) + smallest->getEdgeWeight(adjacent.at(i)) < distance.at(adjacent.at(i))){
                auto d = distance.find(adjacent.at(i));
                auto p = predecessor.find(adjacent.at(i));

                d->second = distance.at(smallest) + smallest->getEdgeWeight(adjacent.at(i));
                p->second = smallest;
            }
        }*/

        runs--;
    }
}

int DijkstraAlgorithm::getShortestDistance(Vertex* end){
    int shortest = INT_MAX;
    for(auto& x: distance){ //gets number of shortest distance
        if(x.second < shortest && x.first == end){
            shortest = x.second;
        }
    }
    return shortest;
}

string DijkstraAlgorithm::getPathTo(Vertex* end){
    vector<string> path;
    string k = "";

    auto p = predecessor.find(end);

    while(p->second != nullptr){
        path.push_back(p->second->getName());
        p = predecessor.find(p->second);
    }

    for(int i = path.size() - 1; i > 0; i++){
        k += path.at(i) + " ";
    }

    return k;
}

