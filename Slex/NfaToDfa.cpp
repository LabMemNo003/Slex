#include "NfaToDfa.h"

#include<iostream>

using namespace std;

NfaToDfa::NfaToDfa(NFA nfa)
{
    DoIt(nfa);
}

void NfaToDfa::DoIt(SuffixFormReToNfa nfa)
{
    nodes.push_back(set<NODE_ID>());
    dt.push_back(DtLine());
    
    nodes.push_back(nfa.CalculateEpsilonClosure(nfa.GetStartNodeID()));
    dt.push_back(DtLine());

    int ind = 1;
    while (true)
    {
        if (ind >= nodes.size()) break;

        set<NODE_ID> curNode = nodes[ind];
        for (TERMINAL t = 0; t < 128; t++)
        {
            set<NODE_ID> tmpNode = nfa.GetNextNodeIDs(curNode, t);
            set<NODE_ID> nxtNode = nfa.CalculateEpsilonClosure(tmpNode);

            int i = 0;
            while(i < nodes.size())
            {
                if (nodes[i].size() == nxtNode.size())
                {
                    bool equal = true;
                    set<NODE_ID>::iterator ite1 = nodes[i].begin();
                    set<NODE_ID>::iterator ite2 = nxtNode.begin();
                    while (ite2 != nxtNode.end())
                    {
                        if ((*ite1) != (*ite2)) {
                            equal = false;
                            break;
                        }

                        ite1++;
                        ite2++;
                    }
                    if (equal) break;
                }

                i++;
            }

            if (i == nodes.size())
            {
                nodes.push_back(nxtNode);
                dt.push_back(DtLine());
            }
            dt[ind][t] = i;
        }

        ind++;
    }

    NODE_ID finalNode = nfa.GetFinalNodeID();
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].find(finalNode) != nodes[i].end()) {
            endNodes.insert(i);
        }
    }
}

NODE_ID NfaToDfa::GetStartNodeID()
{
    return 1;
}

std::set<NODE_ID> NfaToDfa::GetFinalNodeIDs()
{
    return endNodes;
}

NODE_ID NfaToDfa::GetNextNodeID(NODE_ID curNodeID, TERMINAL terminal)
{
    return dt[curNodeID][terminal];
}

int NfaToDfa::Match(std::string input)
{
    return 0;
}

void NfaToDfa::OptimizeDfa()
{
}

void NfaToDfa::output()
{
    cout << "**********DFA**********" << endl;
    for (int i = 0; i < nodes.size(); i++)
    {
        cout << "ID: " << i << endl;
        for (int j = 0; j < 128; j++)
        {
            if (dt[i][j])
            {
                cout << "Links: " << j << " --> " << dt[i][j] << endl;
            }
        }
        cout << endl;
    }
    cout << "StartID: " << 1 << endl;
    cout << "EndID:";
    for (set<NODE_ID>::iterator ite = endNodes.begin();
        ite != endNodes.end(); ite++)
    {
        cout << " " << *ite;
    }
    cout << endl;
    cout << "**********END**********" << endl;
    cout << endl;
}

