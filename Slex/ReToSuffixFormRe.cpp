#include "ReToSuffixFormRe.h"

#include<iostream>

using namespace std;

bool ReToSuffixFormRe::isOperator(SYMBOL ch) {
    if (ch == OPEN_PAREN || ch == CLOSE_PAREN || ch == KLEENE_CLOSURE || ch == CANCATENATION || ch == UNION)
        return true;
    else
        return false;
}

int ReToSuffixFormRe::getPriority(OPERATOR op, int flag) {
    if (op == KLEENE_CLOSURE) {
        if (!flag)  //out of stack
            return 7;
        else 
            return 6;
    }
    else if (op == CANCATENATION) {
        if (!flag)
            return 5;
        else
            return 4;
    }
    else if (op == UNION) {
        if (!flag)
            return 3;
        else
            return 2;
    }
    else if (op == OPEN_PAREN) {
        if (!flag)
            return 8;
        else
            return 1;
    }
    else if (op == CLOSE_PAREN) {
        if (!flag)
            return 1;
        else
            return 8;
    }
}

std::vector<SYMBOL> ReToSuffixFormRe::toSuffix(std::vector<SYMBOL> processedRe) {
    std::stack<SYMBOL> s;
    std::vector<SYMBOL> suffixRe;
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
                if (cur == CLOSE_PAREN) {
                    while (cur == CLOSE_PAREN && s.top() != OPEN_PAREN){
                        SYMBOL sym = s.top();
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

std::vector<SYMBOL> ReToSuffixFormRe::DoIt(std::vector<SYMBOL> processedRe)
{
    std::vector<SYMBOL> suffixRe = toSuffix(processedRe);
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
