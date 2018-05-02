#pragma once

#include"predefine.h"
#include"NfaToDfa.h"

#include<set>
#include<string>

//============================== PHASE 6 ==============================

typedef class YY_DfaToDriveTable {
public:
	YY_DfaToDriveTable(DFA dfa);

    // You need to implement these methods.
    void DoIt(YY_NfaToDfa dfa);
	YY_NODE_ID GetStartNodeID();
    std::set<YY_NODE_ID> GetFinalNodeIDs();
	YY_NODE_ID GetNextNodeID(YY_NODE_ID curNodeID, YY_TERMINAL terminal);
    int Match(std::string input);

    void output();

private:
    int stateCnt;
	YY_NODE_ID **dt;
	YY_NODE_ID startNode;
    bool *isEndNode;

}DriveTable;