#include "SuffixFormReToNfa.h"

SuffixFormReToNfa::SuffixFormReToNfa(std::vector<SYMBOL> suffixFormRe)
{
    this->NFAGraph = DoIt(suffixFormRe);
}

Graph Graph::createGraph(int id1, int id2, TERMINAL t) {
    Graph newG;
    Node* n1=new Node;
    Node* n2=new Node;
    n1->ID = id1;
    n2->ID = id2;

    Link* l=new Link;
    l->terminal = t;
    l->next = n2;

    n1->links.push_back(l);

    Link* startLk = new Link;
    Link* endLk = new Link;
    //startLk->terminal = NULL;
    startLk->next = n1;
    newG.start = n1;
    newG.end = n2;
    //newG.start->links.push_back(startLk);
    //endLk->terminal = NULL;
    endLk->next = newG.end;
    //newG.end->links.push_back(endLk);

    newG.list.push_back(n1);
    newG.list.push_back(n2);

    return newG;
}

Graph SuffixFormReToNfa::DoIt(std::vector<SYMBOL> suffixFormRe)
{
    std::stack<Graph> NFAStack;
    int i = 0;
    NODE_ID id1 = 0, id2 = 1;
    while (i < suffixFormRe.size()) {
        
        int cur = suffixFormRe.at(i);
        if (cur == CANCATENATION || cur == UNION) {
            //弹出两个
            Graph g2 = NFAStack.top();
            NFAStack.pop();
            Graph g1 = NFAStack.top();
            NFAStack.pop();
            Graph newG;
            if (cur == CANCATENATION) {
                Link* l = new Link;
                //Graph newG;
                newG.start = g1.start;
                newG.end = g2.end;
                
                l->terminal = EPSILON;
                l->next = g2.start;

                Node* p = g1.end;
                p->links.push_back(l);

                for (int j = 0; j < g1.list.size(); j++) {
                    Node* tmp = g1.list[j];
                    newG.list.push_back(tmp);
                }
                for (int j = 0; j < g1.list.size(); j++) {
                    Node* tmp = g2.list[j];
                    newG.list.push_back(tmp);
                }
            }
            else {          //UNION
                //Graph newG;
                Node *newStart = new Node;
                Node* newEnd=new Node;
                newStart->ID = id1;
                newEnd->ID = id2;
                newG.start = newStart;
                newG.end = newEnd;
                Link *l1 = new Link;
                Link* l2 = new Link;
                Link* l3 = new Link;
                Link* l4 = new Link;
                l1->terminal = EPSILON; l2->terminal = EPSILON; 
                l3->terminal = EPSILON; l4->terminal = EPSILON;
                l1->next = g1.start;
                l2->next = g2.start;
                l3->next = newEnd;
                l4->next = newEnd;
                newStart->links.push_back(l1);
                newStart->links.push_back(l2);
                Node* p = g1.end;
                p->links.push_back(l3);
                Node* q = g2.end;
                q->links.push_back(l4);

                for (int j = 0; j < g1.list.size(); j++) {
                    Node* tmp = g1.list[j];
                    newG.list.push_back(tmp);
                }
                for (int k = 0; k < g2.list.size(); k++) {
                    Node* tmp = g2.list[k];
                    newG.list.push_back(tmp);
                }
                newG.list.push_back(newStart);
                newG.list.push_back(newEnd);
            }
            NFAStack.push(newG);
        }
        else if (cur == KLEENE_CLOSURE) {
            //弹出一个
            Graph newG;
            Graph g1 = NFAStack.top();
            NFAStack.pop();

            Node *newStart = new Node;
            Node* newEnd = new Node;
            newG.start = newStart;
            newG.end = newEnd;
            newStart->ID = id1;
            newEnd->ID = id2;
            newG.start = newStart;
            newG.end = newEnd;
            Link *l1 = new Link;
            Link* l2 = new Link;
            Link* l3 = new Link;
            Link* l4 = new Link;
            l1->terminal = EPSILON; l2->terminal = EPSILON;
            l3->terminal = EPSILON; l4->terminal = EPSILON;
            l1->next = g1.start;l2->next = g1.start;
            l3->next = newEnd;l4->next = newEnd;
            newStart->links.push_back(l1);
            newStart->links.push_back(l4);
            g1.end->links.push_back(l2);
            g1.end->links.push_back(l3);

            for (int j = 0; j < g1.list.size(); j++) {
                Node* tmp = g1.list[j];
                newG.list.push_back(tmp);
            }
            newG.list.push_back(newStart);
            newG.list.push_back(newEnd);

            NFAStack.push(newG);
        }
        else{  //terminal
            //制图 NFA
            Graph g = g.createGraph(id1, id2, cur);
            NFAStack.push(g);
        }
        id1 += 2;
        id2 += 2;
        i++;
    }
    Graph finalGraph = NFAStack.top();
    this->NFAGraph = NFAStack.top();
    for (int k = 0; k < this->NFAGraph.list.size(); k++) {
        //cout << k << " ";
        this->NFAGraph.list[k]->ID = k;
    }
    return finalGraph;
}

NODE_ID SuffixFormReToNfa::GetStartNodeID()
{
    //cout << "start node ID: " << this->NFAGraph.start->ID << endl;
    return this->NFAGraph.start->ID;
}

NODE_ID SuffixFormReToNfa::GetFinalNodeID()
{
    return this->NFAGraph.end->ID;
}

Node* SuffixFormReToNfa::locateNode(NODE_ID nodeID) {
    Node* p = new Node;
    for (int i = 0; i < this->NFAGraph.list.size(); i++) {
        if (NFAGraph.list[i]->ID == nodeID) {
            p = NFAGraph.list[i];
            return p;
        }
    }
    return NULL;
}

std::set<NODE_ID> SuffixFormReToNfa::CalculateEpsilonClosure(NODE_ID nodeID)
{
    Node* curNode = locateNode(nodeID);
    std::set<NODE_ID> resSet;
    std::stack<Node*> tmpStack;
    tmpStack.push(curNode);
    resSet.insert(nodeID); //itself
    while (!tmpStack.empty()) {
        Node* tmp;
        tmp= tmpStack.top();
        tmpStack.pop();
        for (int i = 0; i < tmp->links.size(); i++) {
            if (tmp->links[i]->terminal == EPSILON) {
                resSet.insert(tmp->links[i]->next->ID);
                tmpStack.push(tmp->links[i]->next);
            }
        }
    }
    /*
    cout<<"e-CLOSURE of this node: ";
    set<int>::iterator it;
    for (it = resSet.begin(); it != resSet.end(); it++)
        cout << (*it) << " ";
    cout<<endl;
	*/

    return resSet;
}

std::set<NODE_ID> SuffixFormReToNfa::CalculateEpsilonClosure(std::set<NODE_ID> nodeIDs)
{
    std::set<NODE_ID> resSet;
    set<NODE_ID>::iterator it;
    for (it = nodeIDs.begin(); it != nodeIDs.end(); it++) {
        std::set<NODE_ID> tmp=CalculateEpsilonClosure(*it);
        set<NODE_ID>::iterator tmpIt;
        for (tmpIt = tmp.begin(); tmpIt != tmp.end(); tmpIt++) {
            set<NODE_ID>::iterator search;
            bool flag = false;
            for (search = resSet.begin(); search != resSet.end(); search++) {
                if (*tmpIt == *search) {
                    flag = true;
                    break;
                }
            }
            if(!flag)
                resSet.insert(*tmpIt);
        }
    }
    /*
    cout << "e-CLOSURE of this set: ";
    for (it = resSet.begin(); it != resSet.end(); it++)
        cout << (*it) << " ";
    cout << endl;
    */
    return resSet;
}

std::set<NODE_ID> SuffixFormReToNfa::GetNextNodeIDs(NODE_ID curNodeID, TERMINAL terminal)
{
    Node* curNode = locateNode(curNodeID);
    std::set<NODE_ID> resultSet;
    int i;
    set<int>::iterator it;
    for (i = 0; i < curNode->links.size(); i++) {
        if (curNode->links[i]->terminal == terminal) {
            resultSet.insert(curNode->links[i]->next->ID);
        }
    }
    for (i = 0; i < resultSet.size(); i++) {
        for (it = resultSet.begin(); it != resultSet.end(); it++) {
            std::set<NODE_ID> e_set = CalculateEpsilonClosure(resultSet);
            set<int>::iterator tmp;
            for (tmp = e_set.begin(); tmp != e_set.end(); tmp++) {
                resultSet.insert(*tmp);
            }
        }
    }
    /*
    cout << "next nodes are: ";
    for (it = resultSet.begin(); it != resultSet.end(); it++)
        cout << (*it) << " ";
    cout << endl;*/
    return resultSet;
}

std::set<NODE_ID> SuffixFormReToNfa::GetNextNodeIDs(std::set<NODE_ID> curNodeIDs, TERMINAL terminal)
{
    std::set<NODE_ID> resSet;
    set<NODE_ID>::iterator it;
    for (it = curNodeIDs.begin(); it != curNodeIDs.end(); it++) {
		if (*it == 8) {
			cout << endl;
		}
        std::set<NODE_ID> tmpSet = GetNextNodeIDs(*it,terminal);
        set<NODE_ID>::iterator tmp;
        for (tmp = tmpSet.begin(); tmp != tmpSet.end(); tmp++) {
            resSet.insert(*tmp);
        }
    }
	/*
    cout << "next nodes are: ";
    for (it = resSet.begin(); it != resSet.end(); it++)
        cout << (*it) << " ";
    cout << endl;
	*/
    return resSet;
}

int SuffixFormReToNfa::Match(std::string input)
{
    return 0;
}

void SuffixFormReToNfa::OptimizeNfa()
{
}