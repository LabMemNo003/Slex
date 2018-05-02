#pragma once

#include"predefine.h"
#include"SuffixFormReToNfa.h"

#include<set>
#include<string>
#include<vector>

//============================== PHASE 5 ==============================

typedef class YY_NfaToDfa {
public:
	YY_NfaToDfa(NFA nfa);

    // You need to implement these methods.
    void DoIt(YY_SuffixFormReToNfa nfa);
	YY_NODE_ID GetStartNodeID();
    std::set<YY_NODE_ID> GetFinalNodeIDs();
	YY_NODE_ID GetNextNodeID(YY_NODE_ID curNodeID, YY_TERMINAL terminal);
    int Match(std::string input);

    // Optional
    void OptimizeDfa();

    void output();
    int stateCnt();

private:
    struct DtLine {
		YY_NODE_ID nxtNodes[128] = {};
        const YY_NODE_ID &operator[](int ind) const { return nxtNodes[ind]; }
		YY_NODE_ID &operator[](int ind) { return nxtNodes[ind]; }
    };

    std::vector<DtLine> dt;
    std::vector<std::set<YY_NODE_ID>> nodes;
	YY_NODE_ID startNode;
    std::set<YY_NODE_ID> endNodes;

}DFA;