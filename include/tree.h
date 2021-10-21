#ifndef TREE_H
#define TREE_H

// TODO this
#include <vector>

// tree for element representation
template <typename T>
class Tree {
public:
    std::vector<Tree*> children;
    T element;
    
    Tree(T element) : element(element) { }

    ~Tree() {
        for (auto &&e : children) {
            delete e;
        }
    }

    Tree<T>* addChild(T element) {
        children.push_back(new Tree(element));
        return children.back();
    }
};


#endif