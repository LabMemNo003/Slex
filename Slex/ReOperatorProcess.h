#pragma once

#include"predefine.h"

#include<vector>

//============================== PHASE 2 ==============================

class YY_ReOperatorProcess {
public:
    // You need to implement this method.
    std::vector<YY_SYMBOL> DoIt(std::vector<YY_SYMBOL> processedRe);
    void display(const std::vector<YY_SYMBOL> &v);

private:

};