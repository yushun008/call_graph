#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <string.h>
#include "Edge.h"
using namespace std;



class CallPath{
    public:
        static CallPath* create();
        void insert_vertex(Vertex* v);
        vector<Vertex *> get_call_path() const;

    private:
        CallPath(){}
        vector<Vertex *> call_path;
};



class CallGraph
{
public:
    static CallGraph *create();

    Vertex *find_vertex(Vertex *vertex);
    void insert_edge(Edge *edge);
    void set_adjacency();
    Edge *find_edge(Edge *edge);
    Edge *find_edge(Vertex* start,Vertex* end);

    void create_call_paths(Vertex *start, Vertex *end, vector<CallPath *> &call_paths);

    void create_call_paths(Vertex *start, vector<CallPath *> &call_paths);

private:
    unordered_set<Vertex *, Vertex_hash, Vertex_equal> verteices;
    vector<Vertex *> ordered_verteices;
    unordered_set<Edge *, Edge_hash, Edge_equal> edges;
    unsigned short **adjacency;
    CallGraph()
    {
    }
    ~CallGraph()
    {
        free(adjacency);
    }
    void insert_vertex(Vertex *vertex);
    void alloc_adjacency(int number_of_vertex);
    vector<Vertex *> get_follows(Vertex *start);
    void final_recursion(Vertex *start, vector<CallPath *> &call_paths);
    void clean_statu();
};
