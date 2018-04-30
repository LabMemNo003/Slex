#pragma once

#include"predefine.h"
#include"NfaToDfa.h"

#include<set>
#include<string>

//============================== PHASE 6 ==============================

typedef class DfaToDriveTable {
public:
    DfaToDriveTable(DFA dfa);

    // You need to implement these methods.
    void DoIt(NfaToDfa dfa);
    NODE_ID GetStartNodeID();
    std::set<NODE_ID> GetFinalNodeIDs();
    NODE_ID GetNextNodeID(NODE_ID curNodeID, TERMINAL terminal);
    int Match(std::string input);

private:

}DriveTable;