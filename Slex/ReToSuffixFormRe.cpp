#include "ReToSuffixFormRe.h"

#include<iostream>

using namespace std;

bool YY_ReToSuffixFormRe::isOperator(YY_SYMBOL ch) {
    if (ch == YY_OPEN_PAREN || ch == YY_CLOSE_PAREN || ch == YY_KLEENE_CLOSURE || ch == YY_CONCATENATION || ch == YY_UNION)
        return true;
    else
        return false;
}

int YY_ReToSuffixFormRe::getPriority(YY_OPERATOR op, int flag) {
    if (op == YY_KLEENE_CLOSURE) {
        if (!flag)  //out of stack
            return 7;
        else 
            return 6;
    }
    else if (op == YY_CONCATENATION) {
        if (!flag)
            return 5;
        else
            return 4;
    }
    else if (op == YY_UNION) {
        if (!flag)
            return 3;
        else
            return 2;
    }
    else if (op == YY_OPEN_PAREN) {
        if (!flag)
            return 8;
        else
            return 1;
    }
    else if (op == YY_CLOSE_PAREN) {
        if (!flag)
            return 1;
        else
            return 8;
    }
}

std::vector<YY_SYMBOL> YY_ReToSuffixFormRe::toSuffix(std::vector<YY_SYMBOL> processedRe) {
    std::stack<YY_SYMBOL> s;
    std::vector<YY_SYMBOL> suffixRe;
    int i = 0;
    while (i < processedRe.size()) {
        int cur = processedRe.at(i); 
        if (!isOperator(cur)) {
            suffixRe.push_back(cur);
            //cout << "cur:"<<cur << endl;
            i++;
            continue;
        }
        else {
            if (s.empty()) {
                s.push(cur);
                i++;
            }
            else {
                if (cur == YY_CLOSE_PAREN) {
                    while (cur == YY_CLOSE_PAREN && s.top() != YY_OPEN_PAREN){
						YY_SYMBOL sym = s.top();
                        suffixRe.push_back(sym);
                        s.pop();
					}
                    //while (!s.empty()) {
                        s.pop();
                    //}
                    i++;
                    continue;
                    //cur = processedRe[i];  //skip ')'
                }
                if (getPriority(cur, 0) > getPriority(s.top(), 1)) {
                    s.push(cur);
                    //i++;
                }
                else {
                    while (!s.empty() && getPriority(cur, 0) <= getPriority(s.top(), 1)) {
                        suffixRe.push_back(s.top());
                        s.pop();
                    }
                    s.push(cur);
                    //i++;
                }
                i++;
            }
            //i++;
        }
    }
    while (!s.empty()) {
        suffixRe.push_back(s.top());
        //cout << "s top:" << s.top() << " ";
        s.pop();
    }
    
    return suffixRe;
}

std::vector<YY_SYMBOL> YY_ReToSuffixFormRe::DoIt(std::vector<YY_SYMBOL> processedRe)
{
    std::vector<YY_SYMBOL> suffixRe = toSuffix(processedRe);
    /*std::stack<OPERATOR> opStack;  //operator stack
    std::stack<TERMINAL> termStack;  //terminal stack
    int i = suffixRe.size();
    while (i >= 0) {
        int cur = suffixRe.at(i);
        if (isOperator(cur)) {   //operator
            opStack.push(cur);
            i--;
        }
        else {
            termStack.push(cur);  //terminal
            i--;
        }
    }
    return SuffixFormRe(opStack,termStack);*/
    return suffixRe;
}
