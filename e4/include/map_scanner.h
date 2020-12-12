#ifndef _MAP_SCANNER_H_
#define _MAP_SCANNER_H_
#include <iostream>
#include "map.h"
/// 从文件流读取地图
class MapScanner
{
public:
    Map scan(std::istream& s);
}; 
#endif // _MAP_SCANNER_H_