#pragma once

#include"predefine.h"

#include<stack>
#include<vector>

//============================== PHASE 3 ==============================

typedef std::pair<std::stack<OPERATOR>, std::stack<TERMINAL> > SuffixFormRe;

class ReToSuffixFormRe {
public:
    // You need to implement this method.
    SuffixFormRe DoIt(std::vector<SYMBOL> processedRe);

private:

};