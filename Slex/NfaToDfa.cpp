#include "NfaToDfa.h"

NfaToDfa::NfaToDfa(NFA nfa)
{
    DoIt(nfa);
}

void NfaToDfa::DoIt(SuffixFormReToNfa nfa)
{
}

NODE_ID NfaToDfa::GetStartNodeID()
{
    return NODE_ID();
}

std::set<NODE_ID> NfaToDfa::GetFinalNodeIDs()
{
    return std::set<NODE_ID>();
}

NODE_ID NfaToDfa::GetNextNodeID(NODE_ID curNodeID, TERMINAL terminal)
{
    return NODE_ID();
}

int NfaToDfa::Match(std::string input)
{
    return 0;
}

void NfaToDfa::OptimizeDfa()
{
}
