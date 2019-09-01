#ifndef RADIX_H
#define RADIX_H

#include <string>
#include <unordered_map>

struct Edge;
struct Node;

struct Edge { 
    std::string value;
    struct Node* to;
};

//each node has a unordered map of edges where the first letter is the key, 
//denote a leaf as anywhere we the code stops (ifLeaf = true)
struct Node { 
    std::unordered_map <char, Edge> subEdges;
    bool isLeaf;
};

class Radix {
    public:
    Node root;
    bool Search(std::string searchingFor, Node root, int &totalCmp);

    void Insert (std::string insertingWord, Node &root, int &totalCmp);

    void Delete(std::string deletingWord, Node &root, int &totalCmp);
};

#endif