#pragma once

#include"predefine.h"

#include<stack>
#include<vector>

//============================== PHASE 3 ==============================

class YY_ReToSuffixFormRe {
public:
    // You need to implement this method.
    std::vector<YY_SYMBOL> DoIt(std::vector<YY_SYMBOL> processedRe);
	
private:
    std::vector<YY_SYMBOL> toSuffix(std::vector<YY_SYMBOL> processedRe);
    int getPriority(YY_OPERATOR op, int flag);
    bool isOperator(YY_SYMBOL ch);
};