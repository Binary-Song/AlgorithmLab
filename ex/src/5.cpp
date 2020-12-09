#include <vector>
#include <algorithm>
std::vector<int> random_vector(size_t size)
{
    std::vector<int> v(size);
    for (size_t i = 0; i < size; i++) {
        v[i] = rand() % 10 - 5;
    }
    return v;
}

void print_vector(const char* name, const std::vector<int>& v)
{
    printf("[%s]:", name);
    for (auto&& i : v) {
        printf("%d ", i);
    }
    putchar('\n');
}

#pragma region 5
// #include <vector>  
// #include <stdio.h>
// using namespace std;

// void delete_intersect1(vector<int>& A, vector<int> B, vector<int> C)
// {
//     int pi = 0, i = 0, j = 0, k = 0;
//     while (i < A.size() && j < B.size() && k < C.size()) {
//         if (B[j] == C[k]) {
//             while (i < A.size() && A[i] < B[j]) {
//                 A[pi] = A[i];
//                 pi++;
//                 i++;
//             }
//             if (i < A.size() && A[i] >= B[j]) {
//                 i++;j++;k++;
//             }
//         }
//         else if (B[j] > C[k])k++;
//         else j++;
//     }
//     while (i < A.size()) {
//         A[pi] = A[i];
//         pi++;
//         i++;
//     }
// }

// int binary_search(vector<int> A, int x)
// {
//     int l = 0, r = A.size() - 1;
//     while (l <= r) {
//         int m = (l + r) / 2;
//         if (A[m] == x)  return m;
//         else if (A[m] < x) l = m + 1;
//         else r = m - 1;
//     }
//     return -1;
// }

// void delete_intersect2(vector<int>& A, vector<int> B, vector<int> C)
// {
//     int i = 0, j = 0;
//     for (;i < A.size();i++) {
//         if (!(binary_search(B, A[i]) != -1 && binary_search(C, A[i]) != -1)) {
//             A[j++] = A[i];
//         }
//     }
//     A.resize(j);
// }



// int main()
// {
//     for (size_t i = 0; i < 5; i++) {
//         vector<int> A1 = random_vector(20);
//         vector<int> A2(A1);
//         vector<int> B = random_vector(20);
//         vector<int> C = random_vector(20);
//         print_vector("A1", A1);
//         print_vector("B", B);
//         print_vector("C", C);
//         delete_intersect2(A1, B, C);
//         print_vector("A2", A1);
//     }
// }
#pragma endregion
#pragma region 6
void rearrange(std::vector<int>& v)
{
    int j = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] < 0) {
            std::swap(v[i], v[j++]);
        }
    }
}

int main()
{
    for (size_t i = 0; i < 10; i++) {
        std::vector<int> v = random_vector(10);
        print_vector("bef",v); 
        rearrange(v);
        print_vector("aft",v);
    }
}
#pragma endregion