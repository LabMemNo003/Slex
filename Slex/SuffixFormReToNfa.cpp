#include "SuffixFormReToNfa.h"

SuffixFormReToNfa::SuffixFormReToNfa(SuffixFormRe suffixFormRe)
{
    DoIt(suffixFormRe);
}

void SuffixFormReToNfa::DoIt(SuffixFormRe suffixFormRe)
{
}

NODE_ID SuffixFormReToNfa::GetStartNodeID()
{
    return NODE_ID();
}

NODE_ID SuffixFormReToNfa::GetFinalNodeID()
{
    return NODE_ID();
}

std::set<NODE_ID> SuffixFormReToNfa::CalculateEpsilonClosure(NODE_ID nodeID)
{
    return std::set<NODE_ID>();
}

std::set<NODE_ID> SuffixFormReToNfa::CalculateEpsilonClosure(std::set<NODE_ID> nodeIDs)
{
    return std::set<NODE_ID>();
}

std::set<NODE_ID> SuffixFormReToNfa::GetNextNodeIDs(NODE_ID curNodeID, TERMINAL terminal)
{
    return std::set<NODE_ID>();
}

std::set<NODE_ID> SuffixFormReToNfa::GetNextNodeIDs(std::set<NODE_ID> curNodeIDs, TERMINAL terminal)
{
    return std::set<NODE_ID>();
}

int SuffixFormReToNfa::Match(std::string input)
{
    return 0;
}

void SuffixFormReToNfa::OptimizeNfa()
{
}
