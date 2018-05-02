#include"Re.h"

#include<iostream>
#include<string>
#include<cstring>

using namespace std;

//============================== T E S T ==============================

int main() {
    string patterns[21];
    patterns[0] = "\\+";
    patterns[1] = "\\-";
    patterns[2] = "\\*";
    patterns[3] = "/";
    patterns[4] = ">";
    patterns[5] = "<";
    patterns[6] = "=";
    patterns[7] = "\\(";
    patterns[8] = "\\)";
    patterns[9] = ";";
    patterns[10] = "if";
    patterns[11] = "then";
    patterns[12] = "else";
    patterns[13] = "while";
    patterns[14] = "do";
    patterns[15] = "[a-zA-Z][a-zA-Z0-9]*";
    patterns[16] = "0|[1-9][0-9]*";
    patterns[17] = "0[0-7]+";
    patterns[18] = "0x[0-9a-fA-F]+";
    patterns[19] = "[\\ \\n\\f\\r\\t\\v]";
    patterns[20] = ".";

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
    cout << "Input string is:" << endl << endl << input << endl;

    cout << endl;

    cout << "The result is:" << endl << endl;
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
    cout << endl;

    system("pause");

    return 0;
}