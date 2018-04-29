#pragma once

#include"predefine.h"
#include"ReToSuffixFormRe.h"

#include<set>
#include<string>

//============================== PHASE 4 ==============================

typedef class SuffixFormReToNfa {
public:
    SuffixFormReToNfa(std::vector<SYMBOL> suffixFormRe);
    
    // You need to implement these methods.
    void DoIt(std::vector<SYMBOL> suffixFormRe);
    NODE_ID GetStartNodeID();
    NODE_ID GetFinalNodeID();
    std::set<NODE_ID> CalculateEpsilonClosure(NODE_ID nodeID);
    std::set<NODE_ID> CalculateEpsilonClosure(std::set<NODE_ID> nodeIDs);
    std::set<NODE_ID> GetNextNodeIDs(NODE_ID curNodeID, TERMINAL terminal);
    std::set<NODE_ID> GetNextNodeIDs(std::set<NODE_ID> curNodeIDs, TERMINAL terminal);
    int Match(std::string input);

    // Optional
    void OptimizeNfa();

private:
    struct Link;
    struct Node {
        NODE_ID ID;
        std::vector<Link*> fromLinks;
        std::vector<Link*> nextLinks;
    };
    struct Link {
        TERMINAL terminal;
        Node* fromNode;
        Node* nextNode;
    };
    struct Graph {
        Node* startNode;
        Node* endNode;
        std::vector<Node*> nodeList;
        std::vector<Link*> linkList;
    };

    Graph *createGraph(TERMINAL t);
    Graph *unionGraph(Graph *pg1, Graph *pg2);
    Graph *concatenateGraph(Graph *pg1, Graph *pg2);
    Graph *kleeneClosure(Graph *pg);
    void deleteGraph(Graph *pg);
    void setGraphID(Graph *pg);

    Graph *pNfaGraph;

}NFA;