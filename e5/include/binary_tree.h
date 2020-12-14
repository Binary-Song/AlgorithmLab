#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <iostream>

template<typename T>
struct BinarySearchTree
{
private:

    struct BSTNode
    {
        BSTNode* lchild = nullptr;
        BSTNode* rchild = nullptr;
        T data;
        int total = 1;

        BSTNode() = default;
        BSTNode(T data) : data(data) {}

        ~BSTNode()
        {
            delete lchild;
            delete rchild;
        } 
    };

    BSTNode* root = nullptr;

    void insert(T new_data, BSTNode*& target)
    {
        if (!target) {
            target = new BSTNode(new_data);
        }
        else if (new_data < target->data) {
            insert(new_data, target->lchild);
        }
        else if (new_data > target->data) {
            insert(new_data, target->rchild);
        }
        else {
            target->total += 1;
        }
    }

    static void inject_into_stream(std::ostream& strm, const BSTNode* root)
    {
        if (!root) return;
        strm << root->data << ":" << root->total << std::endl;
        inject_into_stream(strm, root->lchild);
        inject_into_stream(strm, root->rchild);
        return;
    }

public:
    BinarySearchTree() {}
    
    ~BinarySearchTree()
    {
        delete root;
    }
    
    void insert(T new_data)
    {
        insert(new_data, root);
    }

    void inject_into_stream(std::ostream& strm)
    {
        inject_into_stream(strm, root);
        return;
    }
};


#endif // _BINARY_TREE_H_