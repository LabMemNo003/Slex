#include "DfaToDriveTable.h"

#include<iostream>

using namespace std;

DfaToDriveTable::DfaToDriveTable(DFA dfa)
{
    DoIt(dfa);
}

void DfaToDriveTable::DoIt(NfaToDfa dfa)
{
    stateCnt = dfa.stateCnt();

    dt = new NODE_ID*[stateCnt];
    for (int i = 0; i < stateCnt; i++)
        dt[i] = new NODE_ID[128];

    for (int i = 0; i < stateCnt; i++) {
        for (int j = 0; j < 128; j++) {
            dt[i][j] = dfa.GetNextNodeID(i, j);
        }
    }

    startNode = dfa.GetStartNodeID();
    
    isEndNode = new bool[stateCnt]();
    set<NODE_ID> endNodes = dfa.GetFinalNodeIDs();
    for (set<NODE_ID>::iterator ite = endNodes.begin();
        ite != endNodes.end(); ite++)
        isEndNode[*ite] = true;
}

NODE_ID DfaToDriveTable::GetStartNodeID()
{
    return startNode;
}

std::set<NODE_ID> DfaToDriveTable::GetFinalNodeIDs()
{
    set<NODE_ID> endNodes;
    for (NODE_ID i = 0; i < stateCnt; i++) {
        if (isEndNode[i]) {
            endNodes.insert(i);
        }
    }
    return endNodes;
}

NODE_ID DfaToDriveTable::GetNextNodeID(NODE_ID curNodeID, TERMINAL terminal)
{
    return dt[curNodeID][terminal];
}

int DfaToDriveTable::Match(std::string input)
{
    int res = 0;
    NODE_ID state = startNode;

    int i = 0;
    int len = int(input.length());
    while (i < len) {
        state = dt[state][input[i]];
        if (isEndNode[state]) {
            res = i + 1;
        }
        else if (state == 0) {
            break;
        }
        i++;
    }
    
    return res;
}

void DfaToDriveTable::output()
{
    cout << "++++++++++DFA++++++++++" << endl;
    for (int i = 0; i < stateCnt; i++)
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
    for (int i = 0; i < stateCnt; i++)
    {
        if (isEndNode[i] == true)
            cout << " " << i;
    }
    cout << endl;
    cout << "++++++++++END++++++++++" << endl;
    cout << endl;
}
