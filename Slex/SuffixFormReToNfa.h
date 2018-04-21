#pragma once

#include"predefine.h"
#include"ReToSuffixFormRe.h"

#include<set>
#include<string>

//============================== PHASE 4 ==============================

typedef class SuffixFormReToNfa {
public:
    SuffixFormReToNfa(SuffixFormRe suffixFormRe);

    // You need to implement these methods.
    void DoIt(SuffixFormRe suffixFormRe);
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

}NFA;