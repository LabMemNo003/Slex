#include "ReOperatorProcess.h"

#include <iostream>
#include <stack>

using namespace std;

void display1(vector<SYMBOL> &v) {
    cout << "the session is:" << endl;
    for (int i = 0; i < v.size();i++)
    {
        if (v[i]<128) cout << char(v[i]);
        else {
            if (v[i] == EPSILON) cout << "EPSILON";
            else if (v[i] == 301)cout << "(";
            else if (v[i] == 302)cout << ")";
            else if (v[i] == 303)cout << "*";
            else if (v[i] == 304)cout << "_";
            else if (v[i] == 305)cout << "|";
            else if (v[i] == 400)cout << "{";
            else if (v[i] == 401)cout << "}";
            else if (v[i] == 402)cout << "[";
            else if (v[i] == 403)cout << "]";
            else if (v[i] == 404)cout << ".";
            else if (v[i] == 405)cout << "-";
            else if (v[i] == 406)cout << "^";
            else if (v[i] == 407)cout << "+";
            else if (v[i] == 408)cout << "?";
            else if (v[i] == 409)cout << "\"";
            else cout << "unknow";
        }
    }
    cout << "\n" << endl;
}

bool isnum(int a) {
    if (a >= int('0') && a <= int('9')) return true;
    else return false;
}

bool is_ext(int &i, std::vector<SYMBOL> &processedRe) {
    if (i + 1 < processedRe.size()) {
        int c = processedRe[i + 1];
        if (c == KLEENE_CLOSURE || c == POSITIVE_CLOSURE || c == QUESTION)
            return true;
        else
            return false;
    }
    else
        return false;
}

void open_b(int &i, std::vector<SYMBOL> &re, std::vector<SYMBOL> &v_temp) {
    i++;
    int ascii[128];
    for (int j = 0;j < 128;j++)
        ascii[j] = 1;
    if (re[i] == CARET) {
        i++;
        while (re[i] != CLOSE_BRACKET) {
            if (re[i] < 128)
                ascii[re[i]] = 0;
            else {
                if (re[i] != HYPHEN) {
                    if (re[i] == OPEN_PAREN) ascii[int('(')] = 0;
                    else if (re[i] == CLOSE_PAREN) ascii[int(')')] = 0;
                    else if (re[i] == KLEENE_CLOSURE) ascii[int('*')] = 0;
                    else if (re[i] == UNION) ascii[int('|')] = 0;
                    else if (re[i] == OPEN_CURLY) ascii[int('{')] = 0;
                    else if (re[i] == CLOSE_CURLY) ascii[int('}')] = 0;
                    else if (re[i] == PERIOD) ascii[int('.')] = 0;
                    else if (re[i] == HYPHEN);
                    else if (re[i] == CARET) ascii[int('^')] = 0;
                    else if (re[i] == POSITIVE_CLOSURE) ascii[int('+')] = 0;
                    else if (re[i] == QUESTION) ascii[int('?')] = 0;
                    else if (re[i] == QUOTATION) ascii[int('\"')] = 0;
                    else {
                        cout << "ascii error1" << endl;
                        getchar();
                    }
                }
            }
            if (re[i] == HYPHEN) {
                if (re[i - 1] == CARET || re[i + 1] == CLOSE_BRACKET)
                    ascii[int('-')] = 0;
                else {
                    if (int(re[i - 1]) > int(re[i + 1])) {
                        cout << "ascii error2" << endl;
                    }
                    for (int k = int(re[i - 1]);k <= int(re[i + 1]);k++)
                        ascii[k] = 0;
                }
            }
            i++;
        }
        v_temp.push_back(OPEN_PAREN);
        for (int j = 0;j < 128;j++) {
            if (ascii[j] == 1) {
                v_temp.push_back(j);
                v_temp.push_back(UNION);
            }
        }
        if (v_temp[v_temp.size() - 1] == UNION)
            v_temp.pop_back();
        v_temp.push_back(CLOSE_PAREN);
    }
    else {
        if (re[i] == HYPHEN) {
            ascii[int('-')] = 0;
            i++;
            if (re[i] == CARET) {
                ascii[int('^')] = 0;
                i++;
            }
        }
        while (re[i] != CLOSE_BRACKET) {
            if (re[i] < 128)
                ascii[re[i]] = 0;
            else {
                if (re[i] == OPEN_PAREN) ascii[int('(')] = 0;
                else if (re[i] == CLOSE_PAREN) ascii[int(')')] = 0;
                else if (re[i] == KLEENE_CLOSURE) ascii[int('*')] = 0;
                else if (re[i] == UNION) ascii[int('|')] = 0;
                else if (re[i] == OPEN_CURLY) ascii[int('{')] = 0;
                else if (re[i] == CLOSE_CURLY) ascii[int('}')] = 0;
                else if (re[i] == PERIOD) ascii[int('.')] = 0;
                else if (re[i] == HYPHEN);
                else if (re[i] == CARET) ascii[int('^')] = 0;
                else if (re[i] == POSITIVE_CLOSURE) ascii[int('+')] = 0;
                else if (re[i] == QUESTION) ascii[int('?')] = 0;
                else if (re[i] == QUOTATION) ascii[int('\"')] = 0;
                else {
                    cout << "ascii error3" << endl;
                    getchar();
                }
            }
            if (re[i] == HYPHEN) {
                if (re[i + 1] == CLOSE_BRACKET)
                    ascii[int('-')] = 0;
                else {
                    if (int(re[i - 1]) > int(re[i + 1])) {
                        cout << "ascii error4" << endl;
                        getchar();
                    }
                    for (int k = int(re[i - 1]);k <= int(re[i + 1]);k++)
                        ascii[k] = 0;
                }
            }
            i++;
        }
        v_temp.push_back(OPEN_PAREN);
        for (int j = 0;j < 128;j++) {
            if (ascii[j] == 0) {
                v_temp.push_back(j);
                v_temp.push_back(UNION);
            }
        }
        if (v_temp[v_temp.size() - 1] == UNION)
            v_temp.pop_back();
        v_temp.push_back(CLOSE_PAREN);
    }
}

void open_c(int &i, std::vector<SYMBOL> &processedRe, std::vector<SYMBOL> &v_temp) {
    int c = processedRe[i - 1];
    i++;
    if (isnum(processedRe[i])) {
        std::stack<int> s;
        int t1 = 0, h = 1, t2 = 0;
        while (isnum(processedRe[i])) {
            s.push(processedRe[i]);
            i++;
        }
        while (!s.empty()) {
            t1 += h*(s.top() - int('0'));
            s.pop();
            h *= 10;
        }
        if (processedRe[i] == CLOSE_CURLY) {
            for (int j = 0;j < t1 - 1;j++) {
                //v_temp.push_back(c);
                v_temp.push_back(CANCATENATION);
                v_temp.push_back(c);
            }
        }
        else if (processedRe[i] == int(',')) {
            i++;
            if (processedRe[i] == CLOSE_CURLY) {
                for (int j = 0;j < t1;j++) {
                    //v_temp.push_back(c);
                    if (j != 0) v_temp.push_back(c);
                    v_temp.push_back(CANCATENATION);
                }
                v_temp.push_back(c);
                v_temp.push_back(KLEENE_CLOSURE);
            }
            else {
                h = 1;
                while (isnum(processedRe[i])) {
                    s.push(processedRe[i]);
                    i++;
                }
                while (!s.empty()) {
                    t2 += h*(s.top() - int('0'));
                    s.pop();
                    h *= 10;
                }
                if (processedRe[i] == CLOSE_CURLY) {
                    if (t2 == t1) {
                        for (int j = 0;j < t1 - 1;j++) {
                            //v_temp.push_back(c);
                            v_temp.push_back(CANCATENATION);
                            v_temp.push_back(c);
                        }
                    }
                    else if (t2 > t1) {
                        for (int j = 0;j < t1;j++) {
                            //v_temp.push_back(c);
                            if (j != 0) v_temp.push_back(c);
                            v_temp.push_back(CANCATENATION);
                        }
                        v_temp.push_back(OPEN_PAREN);
                        v_temp.push_back(EPSILON);
                        for (int j = 0;j < t2 - t1;j++) {
                            v_temp.push_back(UNION);
                            for (int j1 = 0;j1 <= j;j1++) {
                                v_temp.push_back(c);
                                if (j1 != j) v_temp.push_back(CANCATENATION);
                            }
                        }
                        v_temp.push_back(CLOSE_PAREN);
                    }
                    else {
                        cout << "open_c:error0!" << endl;
                        getchar();
                    }
                }
                else {
                    cout << "open_c:error1!" << endl;
                    getchar();
                }
            }
        }
        else {
            cout << "open_c:error2!" << endl;
            getchar();
        }
    }
    else {
        cout << "open_c:error3!" << endl;
        getchar();
    }
}

void period(std::vector<SYMBOL> &v_temp) {
    v_temp.push_back(OPEN_PAREN);
    for (int i = 0;i < 128;i++) {
        if (i != 10) {
            v_temp.push_back(i);
            if (i != 127)
                v_temp.push_back(UNION);
        }
    }
    v_temp.push_back(CLOSE_PAREN);
}

void kleene(std::vector<SYMBOL> &v_temp) {
    vector<SYMBOL>::iterator it = v_temp.begin();
    v_temp.insert(it, OPEN_PAREN);
    v_temp.push_back(KLEENE_CLOSURE);
    v_temp.push_back(CLOSE_PAREN);
}

void quest(std::vector<SYMBOL> &v_temp) {
    if (v_temp.size() == 0) {
        cout << "quest error1" << endl;
        getchar();
    }
    vector<SYMBOL>::iterator it = v_temp.begin();
    v_temp.insert(it, OPEN_PAREN);
    v_temp.push_back(UNION);
    v_temp.push_back(EPSILON);
    v_temp.push_back(CLOSE_PAREN);
}

void positive(std::vector<SYMBOL> &v_temp) {
    vector<SYMBOL>::iterator it = v_temp.begin();
    v_temp.insert(it, OPEN_PAREN);
    int s = v_temp.size();
    for (int i = 0;i < s;i++) {
        v_temp.push_back(CANCATENATION);
        v_temp.push_back(v_temp[i]);
    }
    v_temp.push_back(KLEENE_CLOSURE);
    v_temp.push_back(CLOSE_PAREN);
}

void other(int &i, std::vector<SYMBOL> &processedRe, std::vector<SYMBOL> &v_temp) {
    v_temp.push_back(processedRe[i]);
}

void close_p(std::vector<SYMBOL> &v_temp_all, std::vector<SYMBOL> &v_temp_out) {
    v_temp_all.push_back(CLOSE_PAREN);
    for (int i = 0;i < v_temp_all.size();i++)
        v_temp_out.push_back(v_temp_all[i]);
}

void temp_to_all(std::vector<SYMBOL> &v_temp, std::vector<SYMBOL> &v_temp_all) {
    for (int i = 0;i < v_temp.size();i++)
        v_temp_all.push_back(v_temp[i]);
}

void open_p(int &i, std::vector<SYMBOL> &processedRe, std::vector<SYMBOL> &v_temp_out) {
    std::vector<SYMBOL> v_temp_all;
    v_temp_all.push_back(OPEN_PAREN);
    i++;
    for (;i < processedRe.size();i++) {
        int c = processedRe[i];
        std::vector<SYMBOL> v_temp;
        if (c == CLOSE_PAREN) {
            close_p(v_temp_all, v_temp_out);
            return;
        }
        else if (c == OPEN_BRACKET) {
            open_b(i, processedRe, v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        else if (c == OPEN_CURLY) {
            open_c(i, processedRe, v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        else if (c == PERIOD) {
            period(v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        else if (c == OPEN_PAREN) {
            open_p(i, processedRe, v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        else {
            other(i, processedRe, v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        temp_to_all(v_temp, v_temp_all);
    }
}

std::vector<SYMBOL> ReOperatorProcess::DoIt(std::vector<SYMBOL> processedRe)
{
    std::vector<SYMBOL> v;
    for (int i = 0;i < processedRe.size();i++) {
        int c = processedRe[i];
        std::vector<SYMBOL> v_temp;
        if (c == OPEN_BRACKET) {
            open_b(i, processedRe, v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        else if (c == OPEN_CURLY) {
            open_c(i, processedRe, v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        else if (c == PERIOD) {
            period(v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        else if (c == OPEN_PAREN) {
            open_p(i, processedRe, v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        else {
            other(i, processedRe, v_temp);
            while (is_ext(i, processedRe)) {
                i++;
                if (processedRe[i] == QUESTION)
                    quest(v_temp);
                else if (processedRe[i] == POSITIVE_CLOSURE)
                    positive(v_temp);
                else
                    kleene(v_temp);
            }
        }
        temp_to_all(v_temp, v);
    }
    return v;
}