#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "function.h"
using namespace std;

Graph::Graph(int n)
{
    this->numberOfVertices = n;
    this->adjacencyList = (Vertex**)malloc(sizeof(Vertex*)*n);
    this->vertexInfo = (int*) malloc(sizeof(int)*n);
    for(int i = 0; i < n; i ++){
        // the i would be vertex's index
        // 頭頭
        this->adjacencyList[i] = new Vertex(i);
        this->vertexInfo[i] = -1;
    }
}

void Graph::addEdge(int source, int destination)
{
    // 蓋在source下面
    Vertex *head = this->adjacencyList[source];
    Vertex *child = new Vertex(destination);
    child->nextVertex = head->nextVertex;
    head->nextVertex = child;
    
}

bool Graph::dfs(int vertex)
{
    // deal with people relative with this vertex
    Vertex *relative = this->adjacencyList[vertex]->nextVertex;
    int *log = this->vertexInfo;
    while( relative != nullptr){
        if(log[relative->index] == -1)
            log[relative->index] = !log[vertex];
        else if(log[relative->index] == log[vertex])
            return false;
        relative = relative->nextVertex;
    }
    return true;
}

bool Graph::solver()
{
    int size = this->numberOfVertices;
    int *log = this->vertexInfo;
    for(int i = 0; i < size; i ++){
        // this is a uncolor person, then color it
        if(log[i] == -1){
            log[i] = 0;
        }
        if( dfs(i) == false )
            return false;
    }
    return true;
}

Graph ::~Graph()
{
}