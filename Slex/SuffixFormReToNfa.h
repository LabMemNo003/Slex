#pragma once

#include"predefine.h"
#include"ReToSuffixFormRe.h"

#include<set>
#include<string>
#include <map>
#include <iostream>

//============================== PHASE 4 ==============================

namespace SuffixFromReToNfa {
    class Link;
    class Node {
    public:
        NODE_ID ID;
        std::vector<Link*> links;
        void setId(NODE_ID id) { this->ID = id; }
    };

    class Link {
    public:
        TERMINAL terminal;
        Node* next;
    };

    class Graph {
    public:
        Node* start;
        Node* end;
        std::vector<Node*> list;
        Graph() {  };
        Graph createGraph(int id1, int id2, TERMINAL t);
    };
};

typedef class SuffixFormReToNfa {
public:
    SuffixFormReToNfa(std::vector<SYMBOL> suffixFormRe);
    
    // You need to implement these methods.
    void DoIt(std::vector<SYMBOL> suffixFormRe) ;
    NODE_ID GetStartNodeID();
    NODE_ID GetFinalNodeID();
    std::set<NODE_ID> CalculateEpsilonClosure(NODE_ID nodeID);
    std::set<NODE_ID> CalculateEpsilonClosure(std::set<NODE_ID> nodeIDs);
    std::set<NODE_ID> GetNextNodeIDs(NODE_ID curNodeID, TERMINAL terminal);
    std::set<NODE_ID> GetNextNodeIDs(std::set<NODE_ID> curNodeIDs, TERMINAL terminal);
    int Match(std::string input);

    // Optional
    void OptimizeNfa();

    void output();
    SuffixFromReToNfa::Node* locateNode(NODE_ID nodeID);

private:
    SuffixFromReToNfa::Graph NFAGraph;

}NFA;