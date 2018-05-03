#pragma once

#include"predefine.h"
#include"ReToSuffixFormRe.h"

#include<set>
#include<string>

//============================== PHASE 4 ==============================

typedef class YY_SuffixFormReToNfa {
public:
	YY_SuffixFormReToNfa(std::vector<YY_SYMBOL> suffixFormRe);
    
    // You need to implement these methods.
    void DoIt(std::vector<YY_SYMBOL> suffixFormRe);
	YY_NODE_ID GetStartNodeID();
	YY_NODE_ID GetFinalNodeID();
    std::set<YY_NODE_ID> CalculateEpsilonClosure(YY_NODE_ID nodeID);
    std::set<YY_NODE_ID> CalculateEpsilonClosure(std::set<YY_NODE_ID> nodeIDs);
    std::set<YY_NODE_ID> GetNextNodeIDs(YY_NODE_ID curNodeID, YY_TERMINAL terminal);
    std::set<YY_NODE_ID> GetNextNodeIDs(std::set<YY_NODE_ID> curNodeIDs, YY_TERMINAL terminal);
    int Match(std::string input);

    // Optional
    void OptimizeNfa();

    void output();

private:
    struct Link;
    struct Node {
		YY_NODE_ID ID;
        std::vector<Link*> fromLinks;
        std::vector<Link*> nextLinks;
    };
    struct Link {
		YY_TERMINAL terminal;
        Node* fromNode;
        Node* nextNode;
    };
    struct Graph {
        Node* startNode;
        Node* endNode;
        std::vector<Node*> nodeList;
        std::vector<Link*> linkList;
    };

    Graph *createGraph(YY_TERMINAL t);
    Graph *unionGraph(Graph *pg1, Graph *pg2);
    Graph *concatenateGraph(Graph *pg1, Graph *pg2);
    Graph *kleeneClosure(Graph *pg);
    void deleteGraph(Graph *pg);
    void setGraphID(Graph *pg);

    Graph *pNfaGraph;

}NFA;