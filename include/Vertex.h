#pragma once
#include <string>
using namespace std;

enum VStatu{
    Visited,
    UnVisite,
};
class Vertex
{
    public:
        static Vertex* create(string *filename,string *source_location,string *func_name);
        const string* get_file_name()const ;
        const string* get_source_location() const;
        void set_index(int index);
        unsigned int get_index()const ;
        const string* get_func_name() const;
        void set_statu(VStatu statu);
        VStatu get_statu()const;
        void set_parent(Vertex* parent);
        Vertex* get_parent();

    private:
        string *filename;
        string *source_location;
        string *func_name;
        unsigned int index;
        VStatu statu;
        Vertex *parent;
        Vertex(string *filename, string *source_location, string *func_name) : filename(filename), source_location(source_location), func_name(func_name) {}
};

struct Vertex_hash{
    size_t operator() (const Vertex* v) const {
        return hash<string>()(*v->get_source_location()) ^ hash<string>()(*v->get_func_name());
    }
};

struct Vertex_equal{
    bool operator() (const Vertex* v1,const Vertex* v2) const noexcept{
        return v1->get_source_location() == v2->get_source_location() && v1->get_func_name() == v2->get_func_name() && v1->get_file_name()==v2->get_file_name();
    }
};