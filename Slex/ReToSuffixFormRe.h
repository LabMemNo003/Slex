#pragma once

#include"predefine.h"

#include<stack>
#include<vector>

//============================== PHASE 3 ==============================

class ReToSuffixFormRe {
public:
    // You need to implement this method.
    std::vector<SYMBOL> DoIt(std::vector<SYMBOL> processedRe);
	
private:
    std::vector<SYMBOL> toSuffix(std::vector<SYMBOL> processedRe);
    int getPriority(OPERATOR op, int flag);
    bool isOperator(SYMBOL ch);
};