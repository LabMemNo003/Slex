#include "DfaToDriveTable.h"
#include <iostream>
using namespace std;
DfaToDriveTable::DfaToDriveTable(DFA dfa)
{
    DoIt(dfa);
}

void DfaToDriveTable::DoIt(NfaToDfa dfa)
{
    /*-------------------------------Copy DriveTable--------------------------------------------------*/

	DriveTable = new int*[dfa.GetStateNumber()];
	for (int i = 0; i < dfa.GetStateNumber(); i++) {
		DriveTable[i] = new int[128];
	}

	for (int i = 0; i < dfa.GetStateNumber(); i++) {
		for (int j = 0; j < 128; j++) {
			DriveTable[i][j] = dfa.GetDriveTable(i, j);
		}
	}
	/*
	for (int i = 0; i < dfa.GetStateNumber(); i++) {
		for (int j = 0; j < 128; j++) {
			cout << DriveTable[i][j] << " ";
		}
		cout << endl;
	}
	*/
	/*-------------------------------Copy FinalSet----------------------------------------------------*/

	FinalSet = dfa.GetFinalSet();
}

NODE_ID DfaToDriveTable::GetStartNodeID()
{
    return 1;
}

std::set<NODE_ID> DfaToDriveTable::GetFinalNodeIDs()
{
    return std::set<NODE_ID>(FinalSet);
}

NODE_ID DfaToDriveTable::GetNextNodeID(NODE_ID curNodeID, TERMINAL terminal)
{
	return DriveTable[curNodeID-1][terminal];
}

int DfaToDriveTable::Match(std::string input)
{
	int nextstate = 0;
	int length = 0;
	int templength = 0;

	for (int i = 0; input[i] != '/0'; i++) {

		if (nextstate == -1)
			return length;//ÌáÇ°ÍË³ö
		templength++;
		nextstate = DriveTable[nextstate][(int)input[i]];
	
	    for (set<NODE_ID>::iterator travel = FinalSet.begin(); travel != FinalSet.end(); travel++) {
		    if (*travel == nextstate) {
				if (length < templength) {
					length = templength;
				}
		    }
	    }
    }
    return length;
}
