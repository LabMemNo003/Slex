#include "NfaToDfa.h"
#include <stdio.h>
#include <iostream>

using namespace std;

template <class T>
class InkNode {
public:
	T Data;//������������
	InkNode <T> *Next = NULL;//�������ָ����ָ����һ�����

	InkNode <T>(T data, InkNode <T> *next) {//���캯��������
		Data = data;
		Next = next;
	}

	InkNode <T>() {
		Next = NULL;
	}
};

//�ڽӱ�ڵ�����
struct StateNode {
	int CurrentState;//��ʾ��ǰ�ڵ��״̬�ı��
	set<NODE_ID> state;
};

struct TableNode {
	int CurrentState;
	int Terminal;
	set <NODE_ID> state;
	InkNode <StateNode> *childnode;
};

//����������
template <class T>
class InkList {
private:
	InkNode <T> *Head = NULL;
	InkNode <T> *Tail = NULL;
public:
	InkList();
	~InkList();
	bool clear();
	bool append(T datain);
	bool Stateoutput();
	bool output();
	bool rank(int mode);
	bool HeadNodedestroy();
	InkNode <T>*&  getHead();
	InkNode <T>*&  getTail();
	bool NFATableListdestroy();
};

template <class T>
InkList <T>::InkList() {
	Head = Tail = new InkNode <T>;
}

template <class T>
InkList <T>::~InkList() {
	clear();
}


template <class T>
bool InkList <T>::clear() {
	while (Head->Next != NULL) {
		InkNode <T> *temp = Head->Next;
		Head->Next = temp->Next;
		delete temp;
	}
	return true;
}

template <class T>
bool InkList <T>::append(T datain) {
	T datatemp = datain;
	InkNode <T> *nextnode = new InkNode(datatemp, null);//����Ҫ����ĩβ��������
	InkNode <T> *findtail = Head;//�������ͷ�����
	while (findtail->Next != null) fintdail = findtail->Next;//Ѱ���б�β��
	findtail->next = nextnode;
	return true;
}

template <class T>
bool InkList <T>::Stateoutput() {
	InkNode <T> *output = Head->Next;
	while (output != NULL) {
		cout << output->Data.CurrentState << endl;
		output = output->Next;
	}
}

template <class T>
bool InkList <T>::output() {
	InkNode <T> *output = Head->Next;
	while (output != NULL) {
		cout << output->Data << endl;
		output = output->Next;
	}
	return true;
}

template <class T>
InkNode <T>*& InkList<T>::getHead() {
	return Head;
}

template <class T>
InkNode <T>*& InkList<T>::getTail() {
	return Tail;
}

NfaToDfa::NfaToDfa(NFA nfa)
{
    DoIt(nfa);
}

void NfaToDfa::DoIt(SuffixFormReToNfa nfa)
{
	InkList<TableNode> DFADriveTable;//A list to record dfa's dirve table
	InkList<StateNode> DFAStateList;//A list to record dfa's state
	set<NODE_ID> FinalSet;
	bool different = true;
	int row = 0;
	/*--------------------------Step1: make first node for DFAStateList-----------------------------*/
	StateNode statenode;
	statenode.CurrentState = 1;
	statenode.state = nfa.CalculateEpsilonClosure(nfa.GetStartNodeID());
	InkNode<StateNode> *tempstatenodes = new InkNode<StateNode>(statenode, NULL);
	tempstatenodes = DFAStateList.getHead()->Next;
	DFAStateList.getTail() = tempstatenodes;
	/*always insert the new node at the end of the list,so we need to care the tail node*/

	/*----------------Step2:travel the DFAStateList to find every new state---------------------------*/
	InkNode<StateNode> *movestatenode = DFAStateList.getHead()->Next;//use to move to different point,single direct
	while (movestatenode != NULL) {
		for (int i = 0; i < 128; i++) {
			set<NODE_ID> newstate = nfa.CalculateEpsilonClosure(nfa.GetNextNodeIDs(movestatenode->Data.CurrentState, i));//get a state set,that's maybe a new state
			InkNode<StateNode> *tempstatenode = DFAStateList.getHead()->Next;//check the state whether is a new state,always from the first node
			while (tempstatenode != NULL) {
				set<NODE_ID>::iterator TravelNode = tempstatenode->Data.state.begin();//node's set number
				set<NODE_ID>::iterator TravelNewState = newstate.begin();//set from closure	
				while (TravelNode != tempstatenode->Data.state.end() && TravelNewState != newstate.end()) {
					if (*TravelNode != *TravelNewState) {
						different = false;
						break;
					}
					TravelNewState++;
					TravelNode++;
				}
				if (TravelNode != tempstatenode->Data.state.end() || TravelNewState != newstate.end()) {
					different = false;
				}

				if (different) {//the newstate is a new state, so we need to add this state to StateList
					StateNode data;
					data.CurrentState = tempstatenode->Data.CurrentState++;
					data.state = newstate;
					InkNode<StateNode> *newstatenode = new InkNode<StateNode>(data, NULL);
					DFAStateList.getTail()->Next = newstatenode;
					DFAStateList.getTail() = newstatenode;

					/*-------------------------------------FinalSet-------------------------------------------*/
					for (set<NODE_ID>::iterator TravelNewState = newstate.begin(); TravelNewState != newstate.end(); TravelNewState++) {
						if (*TravelNewState == nfa.GetFinalNodeID()) {//get final state
							FinalSet.insert(newstatenode->Data.CurrentState);
							break;
						}
					}

					different = false;
				}
				tempstatenode = tempstatenode->Next;
			}
			/*------------------add new state to DFADirveTable---------------------------*/
			StateNode statedata;
			statedata.CurrentState = tempstatenode->Data.CurrentState;
			statedata.state = newstate;
			InkNode<StateNode> *newstatedata = new InkNode<StateNode>(statedata, NULL);

			TableNode tabledata;
			tabledata.CurrentState = movestatenode->Data.CurrentState;
			tabledata.Terminal = i;
			tabledata.state = movestatenode->Data.state;
			tabledata.childnode = newstatedata;
			InkNode<TableNode> *temptabledirve = new InkNode<TableNode>(tabledata, NULL);

			DFADriveTable.getTail()->Next = temptabledirve;
			DFADriveTable.getTail() = temptabledirve;
		}
		movestatenode = movestatenode->Next;
	}
	FINALSET = FinalSet;
	/*-------------------------------------DFA Table------------------------------------------------------------*/
	InkNode<TableNode> *newmovetablenode = DFADriveTable.getHead()->Next;
	InkNode<StateNode> *newmovestatenode = DFAStateList.getHead()->Next;
	
	while (newmovestatenode != NULL) {
		row++;
		newmovestatenode = newmovestatenode->Next;
	}
	DriveTable = new int*[row];
	for (int i = 0; i < row; i++) {
		DriveTable[i] = new int[128];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 128; j++) {
			DriveTable[i][j] = -1;
		}
	}
	while (newmovetablenode != NULL) {
		DriveTable[newmovetablenode->Data.CurrentState - 1][newmovetablenode->Data.Terminal] = newmovetablenode->Data.CurrentState;//current from 0 so we need let current minus 1
		newmovetablenode = newmovetablenode->Next;
	}

	StateNumber = row;
}

NODE_ID NfaToDfa::GetStartNodeID()
{
    return 1;//first current's id
}

std::set<NODE_ID> NfaToDfa::GetFinalNodeIDs()
{
    return std::set<NODE_ID>(FINALSET);
}

NODE_ID NfaToDfa::GetNextNodeID(NODE_ID curNodeID, TERMINAL terminal)
{
    return DriveTable[curNodeID-1][terminal];
}

int NfaToDfa::Match(std::string input)
{
	int nextstate = 0;
	int length = 0;
	int templength = 0;

	for (int i = 0; input[i] != '/0'; i++) {

		if (nextstate == -1)
			return -1;//��ǰ�Ƴ�
		templength++;
		nextstate = DriveTable[nextstate][input[i]];


		for (set<NODE_ID>::iterator travel = FINALSET.begin(); travel != FINALSET.end(); travel++) {
			if (*travel == nextstate) {
				if (length < templength) {
					length = templength;
				}
			}
		}
	}
	return length;
}

int NfaToDfa::GetDriveTable(NODE_ID curNodeID, TERMINAL terminal) {
	return DriveTable[curNodeID - 1][terminal];
}

set<NODE_ID> NfaToDfa::GetFinalSet() {
	return set<NODE_ID>(FINALSET);
}

int NfaToDfa::GetStateNumber() {
	return StateNumber;
}
void NfaToDfa::OptimizeDfa()
{
}
