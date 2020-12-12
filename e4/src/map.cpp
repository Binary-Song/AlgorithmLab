#include "map.h"
#include <stack>
#include <cassert>
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

VertexIndex Map::find_vertex(const std::string& name)
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


void Map::dfs(VertexIndex src, VertexIndex dest
    , std::vector<bool>& visited
    , std::vector<Edge>& local_path
    , std::vector<std::vector<Edge>>& res)
{
    if (src == dest) {
        res.push_back(local_path);
        return;
    }
    visited[src] = true;
    for (auto&& e : vertex_adjacency[src].edges) {
        if (!visited[e.tail]) {
            local_path.push_back(e);
            dfs(e.tail, dest, visited, local_path, res);
            assert(local_path.back().tail == e.tail);
            local_path.pop_back();
        }
    }
    visited[src] = false;
}



std::vector<std::vector<Edge>> Map::search_paths(VertexIndex a, VertexIndex b)
{
    std::vector<std::vector<Edge>> res;
    std::vector<bool> visited(vertex_adjacency.size());
    std::vector<Edge> local_path;
    dfs(a, b, visited, local_path, res);
    return res;
}

std::vector<Edge> Map::inbound_edges(VertexIndex v)
{
    std::vector<Edge> res;
    VertexIndex i = 0;
    for (VertexIndex i = 0; i < vertex_adjacency.size();i++) {
        for (auto& e : vertex_adjacency[i].edges) {
            if (e.tail == v) {
                res.push_back(e);
            }
        }
    }
    return res;
}

std::vector<Edge> Map::outbound_edges(VertexIndex v)
{
    std::vector<Edge> res;
    VertexIndex i = 0;
    for (auto& e : vertex_adjacency[v].edges) {
        res.push_back(e);
    }
    return res;
}
