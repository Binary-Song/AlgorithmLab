#include "map.h"

VertexIndex Map::add_vertex(std::string name)
{
    vertex_adjacency.push_back(Vertex(name));
    return vertex_adjacency.size() - 1;
}

void Map::add_edge(VertexIndex vstart, VertexIndex vend, EdgeAddtionalData edge_data)
{
    vertex_adjacency[vstart].edges.push_back(Edge(vend, edge_data));
}

BusIndex Map::add_bus(BusInfo info)
{
    buses.push_back(info);
    return buses.size() - 1;
}

BusIndex Map::find_bus(const std::string& bus_name)
{
    for (int i = 0; i < buses.size(); i++)
        if (buses[i].name == bus_name)
            return i;
    return -1;
}

VertexIndex Map::find_vertex(std::string name)
{
    for (int i = 0; i < vertex_adjacency.size(); i++)
        if (vertex_adjacency[i].data.name == name)
            return i;
    return -1;
}

BusInfo Map::get_bus_info(BusIndex i)
{
    return buses[i];
}

std::vector<VertexIndex> Map::track_down_bus(BusIndex bi)
{
    VertexIndex vi = get_bus_info(bi).start;
    std::vector<VertexIndex> res{ vi };
    bool found_next = true;
    while (found_next) {
        found_next = false;
        for (auto e : vertex_adjacency[vi].edges) {
            if (e.data.bus_index == bi) {
                found_next = true;
                vi = e.tail;
                res.push_back(vi);
                break;
            }
        }
    }
    return res;
}

VertexAddtionalData Map::get_vertex_data(VertexIndex i)
{
    return vertex_adjacency[i].data;
}
