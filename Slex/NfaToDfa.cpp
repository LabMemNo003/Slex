#include "NfaToDfa.h"

#include<iostream>

using namespace std;

YY_NfaToDfa::YY_NfaToDfa(NFA nfa)
{
    DoIt(nfa);
}

void YY_NfaToDfa::DoIt(YY_SuffixFormReToNfa nfa)
{
    nodes.push_back(set<YY_NODE_ID>());
    dt.push_back(DtLine());
    
    nodes.push_back(nfa.CalculateEpsilonClosure(nfa.GetStartNodeID()));
    dt.push_back(DtLine());

    int ind = 1;
    while (true)
    {
        if (ind >= nodes.size()) break;

        set<YY_NODE_ID> curNode = nodes[ind];
        for (YY_TERMINAL t = 0; t < 128; t++)
        {
            if (t == 'x') {
                int a = 0;
            }

            set<YY_NODE_ID> tmpNode = nfa.GetNextNodeIDs(curNode, t);
            set<YY_NODE_ID> nxtNode = nfa.CalculateEpsilonClosure(tmpNode);

            int i = 0;
            while(i < nodes.size())
            {
                if (nodes[i].size() == nxtNode.size())
                {
                    bool equal = true;
                    set<YY_NODE_ID>::iterator ite1 = nodes[i].begin();
                    set<YY_NODE_ID>::iterator ite2 = nxtNode.begin();
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

    startNode = 1;

	YY_NODE_ID finalNode = nfa.GetFinalNodeID();
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].find(finalNode) != nodes[i].end()) {
            endNodes.insert(i);
        }
    }
}

YY_NODE_ID YY_NfaToDfa::GetStartNodeID()
{
    return startNode;
}

std::set<YY_NODE_ID> YY_NfaToDfa::GetFinalNodeIDs()
{
    return endNodes;
}

YY_NODE_ID YY_NfaToDfa::GetNextNodeID(YY_NODE_ID curNodeID, YY_TERMINAL terminal)
{
    return dt[curNodeID][terminal];
}

int YY_NfaToDfa::Match(std::string input)
{
    return 0;
}

void YY_NfaToDfa::OptimizeDfa()
{
}

void YY_NfaToDfa::output()
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
    for (set<YY_NODE_ID>::iterator ite = endNodes.begin();
        ite != endNodes.end(); ite++)
    {
        cout << " " << *ite;
    }
    cout << endl;
    cout << "**********END**********" << endl;
    cout << endl;
}

int YY_NfaToDfa::stateCnt()
{
    return int(nodes.size());
}

