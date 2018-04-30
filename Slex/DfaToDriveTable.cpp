#include "DfaToDriveTable.h"

using namespace std;

DfaToDriveTable::DfaToDriveTable(DFA dfa)
{
    DoIt(dfa);
}

void DfaToDriveTable::DoIt(NfaToDfa dfa)
{
}

NODE_ID DfaToDriveTable::GetStartNodeID()
{
    return NODE_ID();
}

std::set<NODE_ID> DfaToDriveTable::GetFinalNodeIDs()
{
    return std::set<NODE_ID>();
}

NODE_ID DfaToDriveTable::GetNextNodeID(NODE_ID curNodeID, TERMINAL terminal)
{
    return NODE_ID();
}

int DfaToDriveTable::Match(std::string input)
{
    return 0;
}
