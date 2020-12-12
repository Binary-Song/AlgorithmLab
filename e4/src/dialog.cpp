#include "dialog.h"
#include "map_scanner.h"
#include <iostream>
#include <fstream>

Dialog::Dialog(const char* file_name)
{
    std::cout << "Loading map from " << file_name << std::endl;
    MapScanner scanner;
    map = scanner.scan(std::ifstream(R"(D:\Projects\AlgorithmLab\e4\test_data.txt)"));
    std::cout << "Map loaded!" << std::endl;
}

Dialog::Dialog(const Map& map) :map(map) {}

void Dialog::begin_dialog()
{
    int number = 0;
    while (true) {
        std::cout << "Hi, what do you want me to do?" << std::endl;
        std::cout << "1: Show bus route." << std::endl;
        std::cout << "2: Find paths from A to B." << std::endl;
        std::cout << "3: Show bus stop info." << std::endl;
        std::cout << "0: Exit." << std::endl;
        std::cout << "Enter a number:" << std::endl;
        std::cout << ">>> ";
        std::cin >> number;
        if (number == 0) {
            return;
        }
        else if (number == 1) {
            query_bus();
        }
        else if (number == 2) {
            query_path();
        }
        else if (number == 3) {
            query_stop();
        }
        std::cout << std::endl;
    }
}

void Dialog::query_bus()
{
    std::string bus_name;
    std::cout << "Which bus? Tell me its name:" << std::endl;
    std::cout << ">>> ";
    std::cin >> bus_name;
    BusIndex bi = map.find_bus(bus_name);
    if (bi != -1) {
        std::vector<VertexIndex> path = map.track_down_bus(bi);
        for (int i = 0; i < path.size(); i++) {
            if (i != 0) {
                std::cout << " -> ";
            }
            std::cout << map.get_vertex_data(path[i]).name;
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No such bus." << std::endl;
    }
}

void Dialog::query_path()
{
    std::string a, b;
    std::cout << "Enter A and B:" << std::endl;
    std::cout << ">>> ";
    std::cin >> a >> b;
    VertexIndex ai, bi;
    if ((ai = map.find_vertex(a)) != -1 &&
        (bi = map.find_vertex(b)) != -1) {
        auto paths = map.search_paths(ai, bi);
        if (paths.size() == 0)
            std::cout << "Not reachable." << std::endl;
        else {
            int pi = 1;
            for (auto&& path : paths) {
                std::cout << "Path " << pi++ << ": " << std::endl;

                std::cout << map.get_vertex_data(ai).name << " ";
                for (auto&& e : path) {
                    auto bus_name = map.get_bus_info(e.data.bus_index).name;
                    auto stop_name = map.get_vertex_data(e.tail).name;
                    std::cout << "  >"
                        << bus_name << ">  "
                        << stop_name;
                }
                std::cout << std::endl;
            }
        }
    }
    else {
        std::cout << "No such stops." << std::endl;
    }
}

void Dialog::query_stop()
{
    std::string stop_name;
    std::cout << "Which stop? Tell me its name:" << std::endl;
    std::cout << ">>> ";
    std::cin >> stop_name;

    VertexIndex vi = map.find_vertex(stop_name);
    auto inbounds = map.inbound_edges(vi);
    auto outbounds = map.outbound_edges(vi);

    std::cout << "Inbound bus routes:";
    for (Edge e : inbounds) {
        auto bus_name = map.get_bus_info(e.data.bus_index).name;
        std::cout << bus_name << "  ";
    }
    std::cout << std::endl;

    std::cout << "Outbound bus routes:";
    for (Edge e : outbounds) {
        auto bus_name = map.get_bus_info(e.data.bus_index).name;
        std::cout << bus_name << "  ";
    }
    std::cout << std::endl;
}
