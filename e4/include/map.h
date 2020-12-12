#ifndef _ADJACENCY_LIST_H_
#define _ADJACENCY_LIST_H_

#include <list> 
#include <vector>
#include <string>
using VertexIndex = int;
using BusIndex = int;

struct EdgeAddtionalData
{
    double length = -1;
    BusIndex bus_index = -1;

    EdgeAddtionalData() {};
    EdgeAddtionalData(double length, BusIndex bus_index) :length(length), bus_index(bus_index) {}
};

struct VertexAddtionalData
{
    std::string name;
    VertexAddtionalData() {}
    VertexAddtionalData(const std::string& name) :name(name) {}
};

struct Edge
{
    VertexIndex tail;
    EdgeAddtionalData data;
    Edge(VertexIndex tail, EdgeAddtionalData data) : tail(tail), data(data) {}
};

struct Vertex
{
    std::list<Edge> edges;
    VertexAddtionalData data;
    Vertex() {}
    Vertex(const std::string& name) :data(VertexAddtionalData(name)) {}
    Vertex(const VertexAddtionalData& data) :data(data) {}
};

struct BusInfo
{
    std::string name;
    VertexIndex start;
    BusInfo() {}
    BusInfo(const std::string& name, VertexIndex start) :name(name), start(start) {}
};

class Map
{
    std::vector<Vertex> vertex_adjacency;
    std::vector<BusInfo> buses;
public:
    VertexIndex add_vertex(std::string name);
    void add_edge(VertexIndex vstart, VertexIndex vend, EdgeAddtionalData edge_data);
    BusIndex add_bus(BusInfo info);
    BusIndex find_bus(const std::string& bus_name);
    VertexIndex find_vertex(std::string name);
    BusInfo get_bus_info(BusIndex i);
    VertexAddtionalData get_vertex_data(VertexIndex i);
    std::vector<VertexIndex> track_down_bus(BusIndex bus);
};
#endif // _ADJACENCY_LIST_H_