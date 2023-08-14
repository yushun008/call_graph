#include "Edge.h"

Edge* Edge::create(Vertex* start,Vertex* end,EdgeStatu Disconnected){
    return new Edge(start, end,Disconnected);
}

Vertex* Edge::get_start_vertex() const{
    return start;
}
Vertex* Edge::get_end_vertex() const{
    return end;
}
EdgeStatu Edge::get_statu()const{
    return statu;
}
void Edge::set_statu(EdgeStatu statu){
    this->statu = statu;
}
