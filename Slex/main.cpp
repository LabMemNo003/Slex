#include"Re.h"

#include<iostream>
#include<string>
#include<cstring>

using namespace std;

//============================== T E S T ==============================

int main() {
    string PLUS = "\\+";
    string MINUS = "\\-";
    string MULTIPY = "\\*";
    string DIVIDE = "/";
    string GREATER = ">";
    string LESS = "<";
    string ASSIGN = "=";
    string L_PAREN = "\\(";
    string R_PAREN = "\\)";
    string SEMICOLON = ";";

    string KEY_IF = "if";
    string KEY_THEN = "then";
    string KEY_ELSE = "else";
    string KEY_WHILE = "while";
    string KEY_DO = "do";

    string IDN = "[a-zA-Z][a-zA-Z0-9]*";
    string INT10 = "0|[1-9][0-9]*";
    string INT8 = "0[0-7]+";
    string INT16 = "0x[0-9a-fA-F]+";

    string SPACE = "\\ \\n\\f\\r\\t\\v";
    string ERROR = ".";

    string patterns[21];
    patterns[0] = PLUS;
    patterns[1] = MINUS;
    patterns[2] = MULTIPY;
    patterns[3] = DIVIDE;
    patterns[4] = GREATER;
    patterns[5] = LESS;
    patterns[6] = ASSIGN;
    patterns[7] = L_PAREN;
    patterns[8] = R_PAREN;
    patterns[9] = SEMICOLON;
    patterns[10] = KEY_IF;
    patterns[11] = KEY_THEN;
    patterns[12] = KEY_ELSE;
    patterns[13] = KEY_WHILE;
    patterns[14] = KEY_DO;
    patterns[15] = IDN;
    patterns[16] = INT10;
    patterns[17] = INT8;
    patterns[18] = INT16;
    patterns[19] = SPACE;
    patterns[20] = ERROR;

    Re automas[21];
    for (int i = 0; i < 21; i++) {
        automas[i].DoIt(patterns[i]);
    }

    typedef void(*PtrFunc)(string);
    PtrFunc actions[21];
    actions[0] = [](string str) { cout << "+" << endl; };
    actions[1] = [](string str) { cout << "-" << endl; };
    actions[2] = [](string str) { cout << "*" << endl; };
    actions[3] = [](string str) { cout << "/" << endl; };
    actions[4] = [](string str) { cout << ">" << endl; };
    actions[5] = [](string str) { cout << "<" << endl; };
    actions[6] = [](string str) { cout << "=" << endl; };
    actions[7] = [](string str) { cout << "(" << endl; };
    actions[8] = [](string str) { cout << ")" << endl; };
    actions[9] = [](string str) { cout << ";" << endl; };
    actions[10] = [](string str) { cout << "IF" << endl; };
    actions[11] = [](string str) { cout << "THEN" << endl; };
    actions[12] = [](string str) { cout << "ELSE" << endl; };
    actions[13] = [](string str) { cout << "WHILE" << endl; };
    actions[14] = [](string str) { cout << "DO" << endl; };
    actions[15] = [](string str) { cout << "IDN\t" << str << endl; };
    actions[16] = [](string str) { cout << "INT10\t" << str << endl; };
    actions[17] = [](string str) { cout << "INT8\t" << str << endl; };
    actions[18] = [](string str) { cout << "INT16\t" << str << endl; };
    actions[19] = [](string str) { };
    actions[20] = [](string str) {cout << "ERROR" << endl; };


    string input = "0  92+data>  0x3f  00  while";

    int ind = 0;
    int len = input.length();
    while (ind < len) {
        int max_match = 0;
        int max_pattern = 0;
        for (int i = 0; i < 21; i++) {
            int len_match = automas[i].Match(input.substr(ind));
            if (len_match > max_match) {
                max_pattern = i;
                max_match = len_match;
            }
        }
        actions[max_pattern](input.substr(ind, max_match));
        ind = ind + max_match;
    }

    system("pause");

    return 0;
}