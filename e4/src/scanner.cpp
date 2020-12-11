#include "scanner.h"
 
Scanner::Scanner(std::istream& s) : s(s)
{

}

std::vector<Matrix> Scanner::scan_matrices(int routes)
{
    std::vector<Matrix> result;
    for (int i = 0; i < routes;i++) {
        Matrix m;
        std::cin >> m;
        result.push_back(m);
    }
    return result;
}