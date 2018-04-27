#include"predefine.h"
#include"ReSymbolProcess.h"
#include"ReOperatorProcess.h"
#include"ReToSuffixFormRe.h"
#include"SuffixFormReToNfa.h"
//#include"NfaToDfa.h"
//#include"DfaToDriveTable.h"

#include<iostream>
#include<string>

using namespace std;

//============================== T E S T ==============================

int main() {
    //string original_re = "0|[1-9][0-9]*";
    
    //vector<SYMBOL> processed_re_1 = (new ReSymbolProcess())->DoIt(original_re);
    
    //vector<SYMBOL> processed_re_2 = (new ReOperatorProcess())->DoIt(processed_re_1);
    
    //std::vector<SYMBOL> processed_re_2;
    std::vector<int> s;
    
    //s.push_back(301); //"("
    s.push_back(97);
    //s.push_back(305);  //"+"
    //s.push_back(98);
    //s.push_back(302); //")"
    //s.push_back(304);   //"/c"
    //s.push_back(99);
    s.push_back(303);  //"*"
    
    /*
    s.push_back(97);
    s.push_back(304);
    s.push_back(98);
    s.push_back(305);
    s.push_back(97);
    */
    //转后缀表达式
    
    std::vector<SYMBOL> suffix = (new ReToSuffixFormRe())->DoIt(s);
    for (int i = 0; i < suffix.size(); i++) {
        cout << suffix[i] << " ";
    }
    cout << endl;

    NFA nfa(suffix);
    nfa.output();
    nfa.GetStartNodeID();
    std::set<NODE_ID> testSet;
    testSet.insert(0);
    testSet.insert(2);
    //nfa.CalculateEpsilonClosure(testSet);
    
    nfa.CalculateEpsilonClosure(1);   //ID越界？
    //nfa.GetNextNodeIDs(0,97);
    //nfa.GetNextNodeIDs(testSet, 97);
    
    //-------------------- 
    //DFA dfa(nfa);

    //DriveTable drive_table(dfa);

    //string input = "1234567890";

    //int matched_length = drive_table.Match(input);

    //cout << matched_length << endl;

    return 0;
}