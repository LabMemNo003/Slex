#include"Re.h"

#include"predefine.h"
#include"ReSymbolProcess.h"
#include"ReOperatorProcess.h"
#include"ReToSuffixFormRe.h"
#include"SuffixFormReToNfa.h"
#include"NfaToDfa.h"
#include"DfaToDriveTable.h"

#include<vector>
#include<iostream>

Re::Re()
{
    dt = NULL;
}

Re::Re(std::string original_re)
{
    DoIt(original_re);
}

void Re::DoIt(std::string original_re)
{
    ReSymbolProcess rsp;
    std::vector<SYMBOL> processed_re_1 = rsp.DoIt(original_re);

    ReOperatorProcess rop;
    std::vector<SYMBOL> processed_re_2 = rop.DoIt(processed_re_1);

#ifdef DEBUG
    rop.display(processed_re_2);
#endif //DEBUG

    ReToSuffixFormRe rtsf;
	std::vector<SYMBOL> suffix_form_re = rtsf.DoIt(processed_re_2);

#ifdef DEBUG
    for (int i = 0; i < suffix_form_re.size(); i++) {
        std::cout << suffix_form_re[i] << " ";
    }
    std::cout << std::endl;
#endif //DEBUG
    
    NFA nfa(suffix_form_re);

#ifdef DEBUG
    nfa.output();
#endif //DEBUG

    DFA dfa(nfa);

#ifdef DEBUG
    dfa.output();
#endif //DEBUG

    dt = new DriveTable(dfa);

#ifdef DEBUG
    dt->output();
#endif // DEBUG

}

int Re::Match(std::string input)
{
    return dt->Match(input);
}
