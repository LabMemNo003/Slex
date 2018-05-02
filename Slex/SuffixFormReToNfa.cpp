#include "SuffixFormReToNfa.h"

#include<queue>
#include<iostream>

using namespace std;


YY_SuffixFormReToNfa::YY_SuffixFormReToNfa(std::vector<YY_SYMBOL> suffixFormRe)
{
    DoIt(suffixFormRe);
}

void YY_SuffixFormReToNfa::DoIt(std::vector<YY_SYMBOL> suffixFormRe)
{
    std::stack<Graph*> NfaStack;
    Graph *pg, *pg1, *pg2;

    int i = 0, size = int(suffixFormRe.size());
    while (i < size) {
        int cur = suffixFormRe.at(i);

        if (cur == YY_CONCATENATION) {
            pg2 = NfaStack.top();
            NfaStack.pop();
            pg1 = NfaStack.top();
            NfaStack.pop();
            
            pg = concatenateGraph(pg1, pg2);

            NfaStack.push(pg);
        }
        else if (cur == YY_UNION) {
            pg1 = NfaStack.top();
            NfaStack.pop();
            pg2 = NfaStack.top();
            NfaStack.pop();

            pg = unionGraph(pg1, pg2);

            NfaStack.push(pg);
        }
        else if (cur == YY_KLEENE_CLOSURE) {
            pg = NfaStack.top();
            NfaStack.pop();

            pg = kleeneClosure(pg);

            NfaStack.push(pg);
        }
        else {
            pg = createGraph(cur);

            NfaStack.push(pg);
        }

        i++;
    }
    pNfaGraph = NfaStack.top();
    NfaStack.pop();

    setGraphID(pNfaGraph);
}

YY_NODE_ID YY_SuffixFormReToNfa::GetStartNodeID()
{
    return pNfaGraph->startNode->ID;
}

YY_NODE_ID YY_SuffixFormReToNfa::GetFinalNodeID()
{
    return pNfaGraph->endNode->ID;
}

std::set<YY_NODE_ID> YY_SuffixFormReToNfa::CalculateEpsilonClosure(YY_NODE_ID nodeID)
{
    set<YY_NODE_ID> resSet;
    queue<YY_NODE_ID> queSet;

    queSet.push(nodeID);
    while (!queSet.empty()) {
		YY_NODE_ID cur_id = queSet.front();
        queSet.pop();
        resSet.insert(cur_id);

        for (vector<Link*>::iterator ite = pNfaGraph->nodeList[cur_id]->nextLinks.begin();
            ite != pNfaGraph->nodeList[cur_id]->nextLinks.end(); ite++) {
            if ((*ite)->terminal == YY_EPSILON) {
				YY_NODE_ID nxt_id = (*ite)->nextNode->ID;
                if (resSet.find(nxt_id) == resSet.end()) {
                    queSet.push(nxt_id);
                }
            }
        }
    }

    return resSet;
}

std::set<YY_NODE_ID> YY_SuffixFormReToNfa::CalculateEpsilonClosure(std::set<YY_NODE_ID> nodeIDs)
{
    set<YY_NODE_ID> resSet;
    queue<YY_NODE_ID> queSet;

    for (set<YY_NODE_ID>::iterator ite = nodeIDs.begin();
        ite != nodeIDs.end(); ite++) {
        queSet.push(*ite);
    }

    while (!queSet.empty()) {
		YY_NODE_ID cur_id = queSet.front();
        queSet.pop();
        resSet.insert(cur_id);

        for (vector<Link*>::iterator ite = pNfaGraph->nodeList[cur_id]->nextLinks.begin();
            ite != pNfaGraph->nodeList[cur_id]->nextLinks.end(); ite++) {
            if ((*ite)->terminal == YY_EPSILON) {
				YY_NODE_ID nxt_id = (*ite)->nextNode->ID;
                if (resSet.find(nxt_id) == resSet.end()) {
                    queSet.push(nxt_id);
                }
            }
        }
    }

    return resSet;
}

std::set<YY_NODE_ID> YY_SuffixFormReToNfa::GetNextNodeIDs(YY_NODE_ID curNodeID, YY_TERMINAL terminal)
{
    set<YY_NODE_ID> resSet;
    for (vector<Link*>::iterator ite = pNfaGraph->nodeList[curNodeID]->nextLinks.begin();
        ite != pNfaGraph->nodeList[curNodeID]->nextLinks.end(); ite++) {
        if ((*ite)->terminal == terminal) {
            resSet.insert((*ite)->nextNode->ID);
            break;
        }
    }
    return resSet;
}

std::set<YY_NODE_ID> YY_SuffixFormReToNfa::GetNextNodeIDs(std::set<YY_NODE_ID> curNodeIDs, YY_TERMINAL terminal)
{
    set<YY_NODE_ID> resSet;
    for (set<YY_NODE_ID>::iterator ite = curNodeIDs.begin();
        ite != curNodeIDs.end(); ite++) {
		YY_NODE_ID curNodeID = *ite;
        for (vector<Link*>::iterator ite = pNfaGraph->nodeList[curNodeID]->nextLinks.begin();
            ite != pNfaGraph->nodeList[curNodeID]->nextLinks.end(); ite++) {
            if ((*ite)->terminal == terminal) {
                resSet.insert((*ite)->nextNode->ID);
                break;
            }
        }
    }
    return resSet;
}

int YY_SuffixFormReToNfa::Match(std::string input)
{
    return 0;
}

void YY_SuffixFormReToNfa::OptimizeNfa()
{
}

void YY_SuffixFormReToNfa::output()
{
    cout << "==========NFA==========" << endl;
    for (vector<Node*>::iterator ite = pNfaGraph->nodeList.begin();
        ite != pNfaGraph->nodeList.end(); ite++)
    {
        cout << "ID: " << (*ite)->ID << endl;
        for (vector<Link*>::iterator it = (*ite)->nextLinks.begin();
            it != (*ite)->nextLinks.end(); it++)
        {
            cout << "Links: " << (*it)->terminal << " --> " << (*it)->nextNode->ID << endl;
        }
        cout << endl;
    }
    cout << "StartID: " << pNfaGraph->startNode->ID << endl;
    cout << "EndID: " << pNfaGraph->endNode->ID << endl;
    cout << "==========END==========" << endl;
    cout << endl;
}

YY_SuffixFormReToNfa::Graph *YY_SuffixFormReToNfa::createGraph(YY_TERMINAL t)
{
    Graph *pg = new Graph;

    pg->startNode = new Node;
    pg->nodeList.push_back(pg->startNode);

    pg->endNode = new Node;
    pg->nodeList.push_back(pg->endNode);

    Link *link = new Link;
    link->terminal = t;
    pg->linkList.push_back(link);

    pg->startNode->nextLinks.push_back(link);
    link->fromNode = pg->startNode;

    pg->endNode->fromLinks.push_back(link);
    link->nextNode = pg->endNode;

    return pg;
}

YY_SuffixFormReToNfa::Graph *YY_SuffixFormReToNfa::unionGraph(Graph *pg1, Graph *pg2)
{
    for (vector<Link*>::iterator ite = pg2->startNode->nextLinks.begin();
        ite != pg2->startNode->nextLinks.end(); ite++)
    {
        pg1->startNode->nextLinks.push_back(*ite);
        (*ite)->fromNode = pg1->startNode;
    }
    for (vector<Link*>::iterator ite = pg2->endNode->fromLinks.begin();
        ite != pg2->endNode->fromLinks.end(); ite++)
    {
        pg1->endNode->fromLinks.push_back(*ite);
        (*ite)->nextNode = pg1->endNode;
    }
    for (vector<Link*>::iterator ite = pg2->linkList.begin();
        ite != pg2->linkList.end(); ite++)
    {
        pg1->linkList.push_back(*ite);
    }
    for (vector<Node*>::iterator ite = pg2->nodeList.begin();
        ite != pg2->nodeList.end(); ite++)
    {
        if ((*ite) != pg2->startNode && (*ite) != pg2->endNode)
        {
            pg1->nodeList.push_back(*ite);
        }
        else
        {
            delete (*ite);
        }
    }

    return pg1;
}

YY_SuffixFormReToNfa::Graph *YY_SuffixFormReToNfa::concatenateGraph(Graph *pg1, Graph *pg2)
{
    for (vector<Link*>::iterator ite = pg2->startNode->nextLinks.begin();
        ite != pg2->startNode->nextLinks.end(); ite++)
    {
        pg1->endNode->nextLinks.push_back(*ite);
        (*ite)->fromNode = pg1->endNode;
    }
    pg1->endNode = pg2->endNode;
    for (vector<Link*>::iterator ite = pg2->linkList.begin();
        ite != pg2->linkList.end(); ite++)
    {
        pg1->linkList.push_back(*ite);
    }
    for (vector<Node*>::iterator ite = pg2->nodeList.begin();
        ite != pg2->nodeList.end(); ite++)
    {
        if ((*ite) != pg2->startNode)
        {
            pg1->nodeList.push_back(*ite);
        }
        else
        {
            delete (*ite);
        }
    }

    return pg1;
}

YY_SuffixFormReToNfa::Graph *YY_SuffixFormReToNfa::kleeneClosure(Graph *pg)
{
    Node *startNode = new Node;
    pg->nodeList.push_back(startNode);

    Node *endNode = new Node;
    pg->nodeList.push_back(endNode);

    Link *link1 = new Link;
    link1->terminal = YY_EPSILON;
    pg->linkList.push_back(link1);

    Link *link2 = new Link;
    link2->terminal = YY_EPSILON;
    pg->linkList.push_back(link2);

    Link *link3 = new Link;
    link3->terminal = YY_EPSILON;
    pg->linkList.push_back(link3);

    Link *link4 = new Link;
    link4->terminal = YY_EPSILON;
    pg->linkList.push_back(link4);

    startNode->nextLinks.push_back(link1);
    link1->fromNode = startNode;
    pg->startNode->fromLinks.push_back(link1);
    link1->nextNode = pg->startNode;

    endNode->fromLinks.push_back(link2);
    link2->nextNode = endNode;
    pg->endNode->nextLinks.push_back(link2);
    link2->fromNode = pg->endNode;

    startNode->nextLinks.push_back(link3);
    link3->fromNode = startNode;
    endNode->fromLinks.push_back(link3);
    link3->nextNode = endNode;

    pg->endNode->nextLinks.push_back(link4);
    link4->fromNode = pg->endNode;
    pg->startNode->fromLinks.push_back(link4);
    link4->nextNode = pg->startNode;

    pg->startNode = startNode;
    pg->endNode = endNode;

    return pg;
}

void YY_SuffixFormReToNfa::deleteGraph(Graph *pg)
{
    for (vector<Link*>::iterator ite = pg->linkList.begin();
        ite != pg->linkList.end(); ite++)
    {
        delete (*ite);
    }
    for (vector<Node*>::iterator ite = pg->nodeList.begin();
        ite != pg->nodeList.end(); ite++)
    {
        delete (*ite);
    }
}

void YY_SuffixFormReToNfa::setGraphID(Graph * pg)
{
    for (int i = 0; i < pg->nodeList.size(); i++) {
        pg->nodeList[i]->ID = i;
    }
}
