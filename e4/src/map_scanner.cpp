#include "map_scanner.h"
#include <string>
#include <regex>
#include "map.h"

// 定义此宏来禁止加载信息的输出
#define SUPPRESS_LOADING_MESSAGES 
Map MapScanner::scan(std::istream& strm)
{ 
    using namespace std;
    Map map;
    smatch matches;
    regex r_vertex(R"(^vertex{name:([a-zA-Z0-9]+)})");//匹配顶点声明
    regex r_bus(R"(^bus{name:([a-zA-Z0-9]+),start:([a-zA-Z0-9]+)})");//匹配公交线路声明
    regex r_edge(R"(^edge{from:([a-zA-Z0-9]+),to:([a-zA-Z0-9]+),len:(\d+),of_bus:([a-zA-Z0-9]+)})");//匹配边声明
    regex r_comment("//.*$");//匹配注释
    int lineno = 1;
    while (!strm.eof()) {
        std::string line;
        std::getline(strm, line);
        if (regex_match(line, matches, r_vertex)) {
            map.add_vertex(matches[1].str()); // 添加顶点
#ifndef SUPPRESS_LOADING_MESSAGES
            std::cout << "[" << lineno << "]" <<
                " vertex added: " << matches[1].str() << "\n";
#endif
        }
        else if (regex_match(line, matches, r_bus)) {
            VertexIndex st = map.find_vertex(matches[2].str());
            map.add_bus(BusInfo(matches[1].str(), st)); // 添加线路
#ifndef SUPPRESS_LOADING_MESSAGES 
            std::cout << "[" << lineno << "]"
                << " bus added: " << matches[1].str() << "\n";
#endif 
        }
        else if (regex_match(line, matches, r_edge)) {
            VertexIndex v0, v1;
            BusIndex b;
            std::string from_stop = matches[1].str()
                , to_stop = matches[2].str()
                , bus_name = matches[4].str();
            int length = std::stoi(matches[3].str());

            if ((v0 = map.find_vertex(from_stop)) != -1
                && (v1 = map.find_vertex(to_stop)) != -1
                && (b = map.find_bus(bus_name)) != -1) {
                map.add_edge(v0, v1, EdgeAddtionalData(length, b)); // 添加边
#ifndef SUPPRESS_LOADING_MESSAGES
                std::cout << "[" << lineno << "]" <<
                    " edge added: from " << from_stop
                    << " to " << to_stop
                    << " of bus " << bus_name
                    << " with the length of " << length
                    << "\n";
#endif  
            }
            else {
#ifndef SUPPRESS_LOADING_MESSAGES 
                std::cout << "[" << lineno << "]" <<
                    " edge adding error\n";
#endif   
            }
        }
        else if (regex_match(line, matches, r_comment)) {
        }
        lineno++;
    }
    return map;
}
 