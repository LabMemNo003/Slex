#include "NfaToDfa.h"
#include <stdio.h>
#include <iostream>

using namespace std;

template <class T>
class InkNode {
public:
	T Data;//链表结点数据域
	InkNode <T> *Next = NULL;//链表结点的指针域，指向下一个结点

	InkNode <T>(T data, InkNode <T> *next) {//构造函数的声明
		Data = data;
		Next = next;
	}

	InkNode <T>() {
		Next = NULL;
	}
};

//邻接表节点声明
struct StateNode {
	int CurrentState;//表示当前节点的状态的编号
	set<NODE_ID> state;
};

struct TableNode {
	int CurrentState;
	int Terminal;
	set <NODE_ID> state;
	InkNode <StateNode> *childnode;
};

//链表类声明
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
	InkNode <T>*&  getHead();
	InkNode <T>*&  getTail();
};

template <class T>
InkList <T>::InkList() {
	Head = 	Tail = new InkNode <T>;
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
	InkNode <T> *nextnode = new InkNode(datatemp, null);//创建要加入末尾的链表结点
	InkNode <T> *findtail = Head;//获得链表头部结点
	while (findtail->Next != null) fintdail = findtail->Next;//寻找列表尾部
	findtail->next = nextnode;
	return true;
}

template <class T>
bool InkList <T>::Stateoutput() {
	InkNode <T> *output = Head->Next;
	while (output != NULL) {
		//cout << output->Data.CurrentState << endl;
		output = output->Next;
	}
}

template <class T>
bool InkList <T>::output() {
	InkNode <T> *output = Head->Next;
	while (output != NULL) {
		//cout << output->Data << endl;
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
	bool different = false;
	int row = 0;
	int samelength = 0;
	int length = 0;
	int curNode = 0;
	/*--------------------------Step1: make first node for DFAStateList-----------------------------*/
	StateNode statenode;
	statenode.CurrentState = 0;
	statenode.state = nfa.CalculateEpsilonClosure(nfa.GetStartNodeID());
	//cout << nfa.GetStartNodeID();
	
	InkNode<StateNode> *tempstatenodes = new InkNode<StateNode>(statenode, NULL);

	DFAStateList.getHead()->Next = tempstatenodes;
	DFAStateList.getTail() = tempstatenodes;

	/*always insert the new node at the end of the list,so we need to care the tail node*/

	/*----------------Step2:travel the DFAStateList to find every new state---------------------------*/
	InkNode<StateNode> *movestatenode = DFAStateList.getHead()->Next;//use to move to different point,single direct

	while (movestatenode != NULL) {
		cout << movestatenode->Data.CurrentState;
		for (int i = 0; i < 128; i++) {
			set<NODE_ID> newstate = nfa.CalculateEpsilonClosure(nfa.GetNextNodeIDs(movestatenode->Data.state, i));//get a state set,that's maybe a new state
					/*-------------------Check The StateList----------------------------------*/
			
			if (!newstate.empty()) {
				InkNode<StateNode> *tempstatenode = DFAStateList.getHead()->Next;//check the state whether is a new state,always from the first node
				while (tempstatenode != NULL) {
					set<NODE_ID>::iterator TravelNode = tempstatenode->Data.state.begin();//node's set number
					set<NODE_ID>::iterator TravelNewState = newstate.begin();//set from closure	

					while (TravelNode != tempstatenode->Data.state.end() && TravelNewState != newstate.end()) {
						if (*TravelNode == *TravelNewState) {
							samelength++;
						}
						length++;
						TravelNewState++;
						TravelNode++;
					}
					
					//长度不同
					if ((TravelNode == tempstatenode->Data.state.end() && TravelNewState != newstate.end()) || (TravelNode != tempstatenode->Data.state.end() && TravelNewState == newstate.end())) {
						different = true;
					}

					if (TravelNode == tempstatenode->Data.state.end() && TravelNewState == newstate.end()) {
						if (samelength != length) {
							different = true;
						}
						else {
							different = false;
							curNode = tempstatenode->Data.CurrentState;
							break;
						}
					}

					samelength = 0;	length = 0;
					tempstatenode = tempstatenode->Next;
				}
				/*--------------------------------Add New State to StateList---------------------------------------*/
				if (different) {//the newstate is a new state, so we need to add this state to StateList
					StateNode data;
					data.CurrentState = DFAStateList.getTail()->Data.CurrentState + 1;
					data.state = newstate;
					InkNode<StateNode> *neweststatenode = new InkNode<StateNode>(data, NULL);
					DFAStateList.getTail()->Next = neweststatenode;
					DFAStateList.getTail() = neweststatenode;

					/*-------------------------------------FinalSet-------------------------------------------*/
					for (set<NODE_ID>::iterator TravelNewState = newstate.begin(); TravelNewState != newstate.end(); TravelNewState++) {
						if (*TravelNewState == nfa.GetFinalNodeID()) {//get final state
							FinalSet.insert(neweststatenode->Data.CurrentState);
							break;
						}
					}
				}
				/*------------------add new state to DFADirveTable---------------------------*/
				StateNode statedata;
				if (different) {
					statedata.CurrentState = DFAStateList.getTail()->Data.CurrentState;
					different = false;
				}
				else{
					statedata.CurrentState = curNode;
					different = false;
				}

				statedata.state = newstate;
				InkNode<StateNode> *newstatedata = new InkNode<StateNode>(statedata, NULL);

				TableNode tabledata;
				tabledata.CurrentState = movestatenode->Data.CurrentState;
				tabledata.Terminal = i;
				tabledata.state = movestatenode->Data.state;
				tabledata.childnode = newstatedata;
				InkNode<TableNode> *temptabledrive = new InkNode<TableNode>(tabledata, NULL);

				temptabledrive->Next = DFADriveTable.getHead()->Next;
				DFADriveTable.getHead()->Next = temptabledrive;
			}
			else {
				/*------------------add new state to DFADirveTable---------------------------*/
				StateNode statedata;
				statedata.CurrentState = -1;
				InkNode<StateNode> *newstatedata = new InkNode<StateNode>(statedata, NULL);

				TableNode tabledata;
				tabledata.CurrentState = movestatenode->Data.CurrentState;
				tabledata.Terminal = i;
				tabledata.state = movestatenode->Data.state;
				tabledata.childnode = newstatedata;
				InkNode<TableNode> *temptabledrive = new InkNode<TableNode>(tabledata, NULL);

				temptabledrive->Next = DFADriveTable.getHead()->Next;
				DFADriveTable.getHead()->Next = temptabledrive;
			}
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
	
	/*while (newmovetablenode != NULL) {
		cout << "当前状态：" << newmovetablenode->Data.CurrentState << "通过" << newmovetablenode->Data.Terminal << "可达" << newmovetablenode->Data.childnode->Data.CurrentState << endl;
		newmovetablenode = newmovetablenode->Next;
	}*/
	cout << row;
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
		DriveTable[newmovetablenode->Data.CurrentState][newmovetablenode->Data.Terminal] = newmovetablenode->Data.childnode->Data.CurrentState;//current from 0 so we need let current minus 1
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

    return FINALSET;
}

NODE_ID NfaToDfa::GetNextNodeID(NODE_ID curNodeID, TERMINAL terminal)
{
    return DriveTable[curNodeID][terminal];
}

int NfaToDfa::Match(std::string input)
{
	int nextstate = 0;
	int length = 0;
	int templength = 0;

	for (int i = 0; input[i] != '/0'; i++) {

		if (nextstate == -1)
			return length;//提前推出
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
	return DriveTable[curNodeID][terminal];
}

set<NODE_ID> NfaToDfa::GetFinalSet() {
	return FINALSET;
}

int NfaToDfa::GetStateNumber() {
	return StateNumber;
}
void NfaToDfa::OptimizeDfa()
{
}
