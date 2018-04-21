#pragma once

#include"predefine.h"
#include"SuffixFormReToNfa.h"

#include<set>
#include<string>

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

private:

}DFA;
