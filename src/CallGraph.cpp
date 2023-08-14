#include "CallGraph.h"

using namespace std;
CallPath* CallPath::create(){
    return new CallPath();
}
void CallPath::insert_vertex(Vertex* v){
    call_path.emplace_back(v);
}
vector<Vertex*> CallPath::get_call_path()const{
    return call_path;
}

CallGraph *CallGraph::create()
{
    return new CallGraph();
}

void CallGraph::insert_vertex(Vertex *vertex)
{
    if(!verteices.insert(vertex).second)
        vertex->set_index(verteices.size() - 1);
}
Vertex *CallGraph::find_vertex(Vertex *vertex)
{
    if (auto result = verteices.find(vertex); result != verteices.end())
    {
        delete vertex;
        return *result;
    }
    else
    {
        insert_vertex(vertex);
        return vertex;
    }
}

void CallGraph::insert_edge(Edge *edge)
{
    edges.insert(edge);
    Vertex* start = edge->get_start_vertex();
    Vertex* end = edge->get_end_vertex();
    insert_vertex(start);
    insert_vertex(end);
}

void CallGraph::set_adjacency()
{
    int number_of_vertex = verteices.size();
    alloc_adjacency(number_of_vertex);
    for (auto edge : edges)
    {
        Vertex *start = edge->get_start_vertex();
        Vertex *end = edge->get_end_vertex();
        int start_index = start->get_index();
        int end_index = end->get_index();
        adjacency[start_index][end_index] = 1;
    }
    for(auto vertex:verteices){
        if(vertex->get_index()>=ordered_verteices.size()){
            ordered_verteices.resize(vertex->get_index()+1, 0x0);
        }
        ordered_verteices[vertex->get_index()]= vertex;
    }
}

Edge *CallGraph::find_edge(Edge *edge)
{
    if (auto result = edges.find(edge); result != edges.end())
    {
        delete edge;
        return *result;
    }
    else
    {
        insert_edge(edge);
        return edge;
    }
}

Edge* CallGraph::find_edge(Vertex* start,Vertex* end){
    Edge *edge = Edge::create(start, end,Disconnected);
    return *edges.find(edge);
}

void CallGraph::create_call_paths(Vertex* start,Vertex* end,vector<CallPath*>& call_paths){
    if(start == end){
        final_recursion(start, call_paths);
        return;
    }
    vector<Vertex *> follows = get_follows(start);
    start->set_statu(VStatu::Visited);
    for (auto iter = follows.begin(); iter != follows.end(); iter++)
    {
        if((*iter)->get_statu() == Visited){
            Edge *visitEdge = find_edge(start, (*iter));
            if (visitEdge->get_statu() == Connected){
                CallPath *path = CallPath::create();
                for (auto call_path : call_paths)
                {
                    vector<Vertex *> connect_path = call_path->get_call_path();
                    bool condition = false;
                    for (int i = 0; i < connect_path.size(); i++)
                    {
                        if(connect_path[i] == start){
                            condition = true;
                        }
                        if(condition){
                            path->insert_vertex(connect_path[i]);
                        }
                    }
                }
                while(start!=nullptr){
                    path->insert_vertex(start->get_parent());
                    start = start->get_parent();
                }
                call_paths.emplace_back(path);
            }else{
                continue;
            }
        }else{
            (*iter)->set_statu(VStatu::Visited);
            (*iter)->set_parent(start);
            create_call_paths((*iter), end, call_paths);
        }
    }
}

void CallGraph::create_call_paths(Vertex* start,vector<CallPath*> &call_paths){
    vector<Vertex *> follows = get_follows(start);
    if(follows.size() == 0){
        final_recursion(start, call_paths);
        return;
    }
    start->set_statu(VStatu::Visited);
    bool condition = false;
    for (auto iter = follows.begin(); iter != follows.end(); iter++)
    {
        if((*iter)->get_statu() ==VStatu::Visited){
            Edge *visitEdge = find_edge(start, (*iter));
            if (visitEdge->get_statu() == Connected){
                CallPath *path = CallPath::create();
                for (auto call_path : call_paths)
                {
                    vector<Vertex *> connect_path = call_path->get_call_path();
                    bool condition = false;
                    for (int i = 0; i < connect_path.size(); i++)
                    {
                        if(connect_path[i] == start){
                            condition = true;
                        }
                        if(condition){
                            path->insert_vertex(connect_path[i]);
                        }
                    }
                }
                while(start!=nullptr){
                    path->insert_vertex(start->get_parent());
                    start = start->get_parent();
                }
                call_paths.emplace_back(path);
            }else{
                continue;
            }
        }else{
            condition = true;
            (*iter)->set_statu(VStatu::Visited);
            (*iter)->set_parent(start);
            create_call_paths((*iter),call_paths);
        }
    }
    if(!condition){
        final_recursion(start, call_paths);
        return;
    }
}

void CallGraph::alloc_adjacency(int number_of_vertex)
{

    adjacency = (unsigned short **)malloc(sizeof(unsigned short *) * number_of_vertex);
    if (adjacency == nullptr)
    {
        perror("not enough memmory!");
        exit(1);
    }
    for (int i = 0; i < number_of_vertex; i++)
    {
        adjacency[i] = (unsigned short *)malloc(sizeof(unsigned short) * number_of_vertex);
        if (adjacency[i] == nullptr)
        {
            perror("not enough memmory!");
            exit(1);
        }
        memset(adjacency[i], 0, sizeof(unsigned short) * number_of_vertex);
    }
}

vector<Vertex*> CallGraph::get_follows(Vertex* start){
    int index = start->get_index();
    vector<Vertex *> follows;
    for (int i = 0; i < verteices.size();i++){
        if(adjacency[index][i]==1){
            follows.emplace_back(ordered_verteices[index]);
        }
    }
    return follows;
}

void CallGraph::final_recursion(Vertex* start,vector<CallPath*>& call_paths){
        CallPath *call_path = CallPath::create();
        call_path->insert_vertex(start);
        while (start!= nullptr)
        {
            Edge *connected_edge = find_edge(start->get_parent(), start);
            if (connected_edge == *edges.end())
            {
                perror("find edge error!");
                exit(1);
            }
            connected_edge->set_statu(EdgeStatu::Connected);
            start = start->get_parent();
            call_path->insert_vertex(start);
        };
        call_paths.emplace_back(call_path);
        return;
}

void CallGraph::clean_statu(){
        for (int i = 0; i < ordered_verteices.size();i++){
            ordered_verteices[i]->set_statu(VStatu::UnVisite);
        }
        for (auto iter = edges.begin(); iter != edges.end();iter++){
            (*iter)->set_statu(EdgeStatu::Disconnected);
        }
}
