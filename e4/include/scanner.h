#ifndef _SCANNER_H_
#define _SCANNER_H_
#include "matrix.h"
#include <iostream>
#include <vector>
#include <string>
class Scanner
{
    std::istream& s;
public:
    Scanner(std::istream& s = std::cin);
    int scan_route_count();
    std::vector<Matrix> scan_matrices(int route_count);
    std::vector<std::string> scan_stop_names(int stop_count);
};

#endif // _SCANNER_H_