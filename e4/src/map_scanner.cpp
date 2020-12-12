#include "map_scanner.h"
#include <string>
#include <boost/regex.hpp>
#include "map.h"
Map MapScanner::scan(std::istream& strm)
{
    using namespace boost;
    Map map;
    smatch matches;
    regex r_vertex(R"(^vertex{name:([a-zA-Z0-9]+)})");
    regex r_bus(R"(^bus{name:([a-zA-Z0-9]+),start:([a-zA-Z0-9]+)})");
    regex r_edge(R"(^edge{from:([a-zA-Z0-9]+),to:([a-zA-Z0-9]+),len:(\d+),of_bus:([a-zA-Z0-9]+)})");
    regex r_comment("//.*$");
    int lineno = 1;
    while (!strm.eof()) {
        std::string line;
        std::getline(strm, line);
        if (regex_match(line, matches, r_vertex)) {
            map.add_vertex(matches[1].str());
            std::cout << "[" << lineno << "]" <<
                " vertex added: " << matches[1].str() << "\n";
        }
        else if (regex_match(line, matches, r_bus)) {
            VertexIndex st = map.find_vertex(matches[2].str());
            map.add_bus(BusInfo(matches[1].str(), st));
            std::cout << "[" << lineno << "]"
                << " bus added: " << matches[1].str() << "\n";
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
                map.add_edge(v0, v1, EdgeAddtionalData(length, b));
                std::cout << "[" << lineno << "]" <<
                    " edge added: from " << from_stop
                    << " to " << to_stop
                    << " of bus " << bus_name
                    << " with the length of " << length
                    << "\n";
            }
            else {
                std::cout << "[" << lineno << "]" <<
                    " edge adding error\n";
            }
        }
        else if (regex_match(line, matches, r_comment)) {
        }
        lineno++;
    }
    return map;
}

/*
vertex{name:BlueStreet}
vertex{name:GreenAlley}
vertex{name:YellowPath}
vertex{name:RedStation}
bus{name:Bus173,start:BlueStreet}
edge{from:BlueStreet,to:GreenAlley,len:5,of_bus:Bus173}
edge{from:GreenAlley,to:YellowPath,len:5,of_bus:Bus173}
edge{from:YellowPath,to:RedStation,len:5,of_bus:Bus173}
*/