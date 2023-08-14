#include "Vertex.h"

Vertex* Vertex::create(string *filename,string *source_location,string *func_name){
    return new Vertex(filename, source_location, func_name);
}
const string* Vertex::get_file_name()const {
    return filename;
}
const string* Vertex::get_source_location() const{
    return source_location;
}
void Vertex::set_index(int index){
    this->index = index;
}
unsigned int Vertex::get_index()const {
    return index;
}
const string* Vertex::get_func_name() const{
    return func_name;
}
void Vertex::set_statu(VStatu statu){
    this->statu = statu;
}
VStatu Vertex::get_statu()const{
    return statu;
}
void Vertex::set_parent(Vertex* parent){
    this->parent = parent;
}
Vertex* Vertex::get_parent(){
    return parent;
}