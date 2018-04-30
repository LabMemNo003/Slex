#pragma once

#include"predefine.h"
#include"SuffixFormReToNfa.h"

#include<set>
#include<string>
#include<vector>

//============================== PHASE 5 ==============================

typedef class NfaToDfa {
public:
    NfaToDfa(NFA nfa);

    // You need to implement these methods.
    void DoIt(SuffixFormReToNfa nfa);
    NODE_ID GetStartNodeID();
    std::set<NODE_ID> GetFinalNodeIDs();
    NODE_ID GetNextNodeID(NODE_ID curNodeID, TERMINAL terminal);
    int Match(std::string input);

    // Optional
    void OptimizeDfa();

    void output();

private:
    struct DtLine {
        NODE_ID nxtNodes[128] = {};
        const NODE_ID &operator[](int ind) const { return nxtNodes[ind]; }
        NODE_ID &operator[](int ind) { return nxtNodes[ind]; }
    };

    std::vector<DtLine> dt;
    std::vector<std::set<NODE_ID>> nodes;
    std::set<NODE_ID> endNodes;

}DFA;