#ifndef _ADJACENCY_LIST_H_
#define _ADJACENCY_LIST_H_

#include <list> 
#include <vector>
#include <string>
/// 顶点索引
using VertexIndex = int;
/// 公交线路索引
using BusIndex = int;

/// 边的额外数据
struct EdgeAddtionalData
{
    /// 长度
    double length = -1;
    /// 属于哪个公交
    BusIndex bus_index = -1;

    EdgeAddtionalData() {};
    EdgeAddtionalData(double length, BusIndex bus_index) :length(length), bus_index(bus_index) {}
};

/// 顶点的额外数据
struct VertexAddtionalData
{
    /// 顶点（车站）的名字
    std::string name;
    VertexAddtionalData() {}
    VertexAddtionalData(const std::string& name) :name(name) {}
};

/// 边
struct Edge
{
    /// 尾点的索引
    VertexIndex tail;
    /// 额外数据
    EdgeAddtionalData data;
    Edge(VertexIndex tail, EdgeAddtionalData data) : tail(tail), data(data) {}
};

/// 顶点
struct Vertex
{
    /// 所有以它为起始点的边
    std::list<Edge> edges;
    VertexAddtionalData data;
    Vertex() {}
    Vertex(const std::string& name) :data(VertexAddtionalData(name)) {}
    Vertex(const VertexAddtionalData& data) :data(data) {}
};

/// 公交线路信息
struct BusInfo
{
    /// 公交车名称
    std::string name;
    /// 公交车起始站
    VertexIndex start;
    BusInfo() {}
    BusInfo(const std::string& name, VertexIndex start) :name(name), start(start) {}
};

/// 地图
class Map
{
    /// 邻接链表
    std::vector<Vertex> vertex_adjacency;
    /// 所有公交线路
    std::vector<BusInfo> buses;

    /// 深度优先搜索
    void dfs(VertexIndex src, VertexIndex dest
        , std::vector<bool>& visited
        , std::vector<Edge>& local_path
        , std::vector<std::vector<Edge>>& res);
public:
    /// 添加顶点
    VertexIndex add_vertex(std::string name);
    /// 添加边
    void add_edge(VertexIndex vstart, VertexIndex vend, EdgeAddtionalData edge_data);
    /// 添加公交线
    BusIndex add_bus(BusInfo info);
    /// 根据名字找公交线
    BusIndex find_bus(const std::string& bus_name);
    /// 根据名字找顶点（公交站）
    VertexIndex find_vertex(const std::string& name);
    /// 根据索引取得公交信息
    BusInfo get_bus_info(BusIndex i);
    /// 根据索引取得顶点（公交站）信息
    VertexAddtionalData get_vertex_data(VertexIndex i);
    /// 沿着公交线找到所有顶点
    std::vector<VertexIndex> track_down_bus(BusIndex bus);
    /// 找两点之间的所有路径
    std::vector<std::vector<Edge>> search_paths(VertexIndex a, VertexIndex b);
    /// 尾为该顶点的边
    std::vector<Edge> inbound_edges(VertexIndex v);
    /// 头为该顶点的边
    std::vector<Edge> outbound_edges(VertexIndex v); 
};
#endif // _ADJACENCY_LIST_H_