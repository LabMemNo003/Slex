#include"predefine.h"
#include"ReSymbolProcess.h"
#include"ReOperatorProcess.h"
#include"ReToSuffixFormRe.h"
#include"SuffixFormReToNfa.h"
#include"NfaToDfa.h"
#include"DfaToDriveTable.h"

#include<iostream>
#include<string>

using namespace std;

//============================== T E S T ==============================

int main() {
    string original_re = "0|[1-9][0-9]*";
    
    vector<SYMBOL> processed_re_1 = (new ReSymbolProcess())->DoIt(original_re);
    
    vector<SYMBOL> processed_re_2 = (new ReOperatorProcess())->DoIt(processed_re_1);
    
    SuffixFormRe suffix_form_re = (new ReToSuffixFormRe())->DoIt(processed_re_2);

    NFA nfa(suffix_form_re);

    DFA dfa(nfa);

    DriveTable drive_table(dfa);

    string input = "1234567890";

    int matched_length = drive_table.Match(input);

    cout << matched_length << endl;

    return 0;
}