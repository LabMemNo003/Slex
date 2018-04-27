#include "ReSymbolProcess.h"

#include <iostream>

using namespace std;

void slash(unsigned int &i, string originalRe, std::vector<SYMBOL> &v) {
    i++;
    int temp;
    char a1, a2, a3;
    switch (originalRe[i]) {
    case '(':
        v.push_back(int('('));
        break;
    case ')':
        v.push_back(int(')'));
        break;
    case '*':
        v.push_back(int('*'));
        break;
    case '|':
        v.push_back(int('|'));
        break;
    case '{':
        v.push_back(int('{'));
        break;
    case '}':
        v.push_back(int('}'));
        break;
    case '[':
        v.push_back(int('['));
        break;
    case ']':
        v.push_back(int(']'));
        break;
    case '.':
        v.push_back(int('.'));
        break;
    case '-':
        v.push_back(int('-'));
        break;
    case '^':
        v.push_back(int('^'));
        break;
    case '+':
        v.push_back(int('+'));
        break;
    case '?':
        v.push_back(int('?'));
        break;
    case '"':
        v.push_back(int('"'));
        break;
    case 'e':
        v.push_back(EPSILON);
        break;
    case 'a':
        v.push_back(7);
        break;
    case 'b':
        v.push_back(8);
        break;
    case 'f':
        v.push_back(12);
        break;
    case 'n':
        v.push_back(10);
        break;
    case 'r':
        v.push_back(13);
        break;
    case 't':
        v.push_back(9);
        break;
    case 'v':
        v.push_back(11);
        break;
    case 'x':
        temp = 0;
        if (i + 1 < originalRe.size()) {
            a1 = originalRe[i + 1];
            if (a1 >= '0'&&a1 <= '9') {
                temp += 16 * (a1 - '0');
                i++;
            }
            else if (a1 >= 'a'&&a1 <= 'f') {
                temp += 16 * (a1 - 'a') + 160;
                i++;
            }
            else {
                v.push_back(int('x'));
                break;
            }
            if (i + 1 < originalRe.size()) {
                a2 = originalRe[i + 1];
                if (a2 >= '0'&&a2 <= '9') {
                    temp += a2 - '0';
                    i++;
                }
                else if (a2 >= 'a'&&a2 <= 'f') {
                    temp += a2 - 'a';
                    i++;
                }
                else
                    temp /= 16;
            }
            else
                temp /= 16;
            v.push_back(temp);
        }
        else
            v.push_back(int('x'));
        break;
    case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':
        a1 = originalRe[i];
        if ((i + 1 < originalRe.size()) && (originalRe[i + 1] >= '0'&&originalRe[i + 1] <= '7')) {
            a2 = originalRe[i + 1];
            i++;
            if ((i + 1 < originalRe.size()) && (originalRe[i + 1] >= '0'&&originalRe[i + 1] <= '7')) {
                a3 = originalRe[i + 1];
                i++;
                v.push_back(64 * (a1 - '0') + 8 * (a2 - '0') + (a3 - '0'));
            }
            else
                v.push_back(8 * (a1 - '0') + (a2 - '0'));
        }
        else
            v.push_back(a1 - '0');
        break;
    default:
        v.push_back(int(originalRe[i]));
        break;
    }
}

void s1(unsigned int &i, string originalRe, std::vector<SYMBOL> &v) {
    i++;
    for (;i < originalRe.size();i++) {
        if (originalRe[i] == ')') {
            v.push_back(CLOSE_PAREN);
            return;
        }
        else if (originalRe[i] == '\\')
            slash(i, originalRe, v);
        else
            v.push_back(int(originalRe[i]));
    }
}

void s2(unsigned int &i, string originalRe, std::vector<SYMBOL> &v) {
    i++;
    for (;i < originalRe.size();i++) {
        if (originalRe[i] == '}') {
            v.push_back(CLOSE_CURLY);
            return;
        }
        v.push_back(int(originalRe[i]));
    }
}

void s3(unsigned int &i, string originalRe, std::vector<SYMBOL> &v) {
    i++;
    if (originalRe[i] == '^') {
        v.push_back(CARET);
        i++;
        if (originalRe[i] == '-') {
            v.push_back(int('-'));
            i++;
        }
    }
    else if (originalRe[i] == '-') {
        v.push_back(int('-'));
        i++;
    }
    else;

    for (;i < originalRe.size();i++) {
        if (originalRe[i] == ']') {
            v.push_back(CLOSE_BRACKET);
            return;
        }
        else if (originalRe[i] == '-')
            if (originalRe[i + 1] != CLOSE_BRACKET)
                v.push_back(HYPHEN);
            else
                v.push_back(int('-'));
        else if (originalRe[i] == '\\')
            slash(i, originalRe, v);
        else
            v.push_back(int(originalRe[i]));
    }
}

void s4(unsigned int &i, string originalRe, std::vector<SYMBOL> &v) {
    i++;
    for (;i < originalRe.size();i++) {
        if (originalRe[i] == '"')
            return;
        else if (originalRe[i] == '\\')
            slash(i, originalRe, v);
        else
            v.push_back(int(originalRe[i]));
    }
}

std::vector<SYMBOL> ReSymbolProcess::DoIt(std::string originalRe)
{
    std::vector<SYMBOL> v;
    for (unsigned int i = 0;i < originalRe.size(); i++) {
        if (originalRe[i] == '\\') {
            slash(i, originalRe, v);
        }
        else {
            switch (originalRe[i]) {
            case '(':
                v.push_back(OPEN_PAREN);
                s1(i, originalRe, v);
                break;
            case '*':
                v.push_back(KLEENE_CLOSURE);
                break;
            case '|':
                v.push_back(UNION);
                break;
            case '{':
                v.push_back(OPEN_CURLY);
                s2(i, originalRe, v);
                break;
            case '[':
                v.push_back(OPEN_BRACKET);
                s3(i, originalRe, v);
                break;
            case '.':
                v.push_back(PERIOD);
                break;
            case '-':
                v.push_back(HYPHEN);
                break;
            case '^':
                v.push_back(CARET);
                break;
            case '+':
                v.push_back(POSITIVE_CLOSURE);
                break;
            case '?':
                v.push_back(QUESTION);
                break;
            case '"':
                s4(i, originalRe, v);
                break;
            default:
                v.push_back(int(originalRe[i]));
                break;
            }
        }
    }
    return v;
}