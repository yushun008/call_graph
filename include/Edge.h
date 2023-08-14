#pragma once
#include "Vertex.h"
using namespace std;

enum EdgeStatu
{
    Connected,
    Disconnected,
};

class Edge{
    public:
        static Edge *create(Vertex *start, Vertex *end, EdgeStatu Disconnected);

        Vertex* get_start_vertex() const;
        Vertex* get_end_vertex() const;
        EdgeStatu get_statu()const;
        void set_statu(EdgeStatu statu);

    private:
        Edge(Vertex* start,Vertex* end,EdgeStatu statu):start(start),end(end),statu(statu){}
        Vertex *start;
        Vertex *end;
        EdgeStatu statu;
};

struct Edge_hash{
    size_t operator() (const Edge* v) const {
        return hash<string>()(*v->get_start_vertex()->get_source_location()) ^ hash<string>()(*v->get_end_vertex()->get_func_name());
    }
};

struct Edge_equal{
    bool operator() (const Edge* v1,const Edge* v2) const noexcept{
        return v1->get_start_vertex() == v2->get_start_vertex() && v1->get_end_vertex() == v2->get_end_vertex() ;
    }
};