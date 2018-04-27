#pragma once

#include"predefine.h"
#include"ReToSuffixFormRe.h"

#include<set>
#include<string>
#include <map>
#include <iostream>
using namespace std;
//============================== PHASE 4 ==============================

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

typedef class SuffixFormReToNfa {
public:
    Graph NFAGraph;
    SuffixFormReToNfa(std::vector<SYMBOL> suffixFormRe);
    
    // You need to implement these methods.
    Graph DoIt(std::vector<SYMBOL> suffixFormRe) ;
    
    NODE_ID GetStartNodeID();
    NODE_ID GetFinalNodeID();
    Node* locateNode(NODE_ID nodeID);  //added
    std::set<NODE_ID> CalculateEpsilonClosure(NODE_ID nodeID);
    std::set<NODE_ID> CalculateEpsilonClosure(std::set<NODE_ID> nodeIDs);
    std::set<NODE_ID> GetNextNodeIDs(NODE_ID curNodeID, TERMINAL terminal);
    std::set<NODE_ID> GetNextNodeIDs(std::set<NODE_ID> curNodeIDs, TERMINAL terminal);
    int Match(std::string input);
    void output() {
        for (int i = 0; i < this->NFAGraph.list.size(); i++) {
            Node* p = this->NFAGraph.list[i];
            cout << "ID: " << p->ID << endl;
            if (p->links.size() == 0) {
                cout << "empty list of Node No." << p->ID << endl;
            }
            else {
                for (int j = 0; j < p->links.size(); j++) {
                    cout << " links: " << p->links[j]->terminal << ": " << p->links[j]->next->ID << endl;
                }
            }
            cout << endl;
        }
    }
    // Optional
    void OptimizeNfa();

private:

}NFA;