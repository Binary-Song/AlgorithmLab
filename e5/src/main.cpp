#include "binary_tree.h" 
#include <stdio.h>
int main(int argc, char** argv)
{    
    BinarySearchTree<char> bst;

    printf("hi world\n");
    char ch;
    while ((ch = getchar()) != EOF) {
        bst.insert(ch);
    }

    bst.inject_into_stream(std::cout);
}