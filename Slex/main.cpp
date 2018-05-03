#include"Re.h"

#include<iostream>
#include<string>
#include<cstring>

using namespace std;

//============================== T E S T ==============================

int main() {
    string YY_patterns[21];
    YY_patterns[0] = "\\+";
    YY_patterns[1] = "\\-";
    YY_patterns[2] = "\\*";
    YY_patterns[3] = "/";
    YY_patterns[4] = ">";
    YY_patterns[5] = "<";
    YY_patterns[6] = "=";
    YY_patterns[7] = "\\(";
    YY_patterns[8] = "\\)";
    YY_patterns[9] = ";";
    YY_patterns[10] = "if";
    YY_patterns[11] = "then";
    YY_patterns[12] = "else";
    YY_patterns[13] = "while";
    YY_patterns[14] = "do";
    YY_patterns[15] = "[a-zA-Z][a-zA-Z0-9]*";
    YY_patterns[16] = "0|[1-9][0-9]*";
    YY_patterns[17] = "0[0-7]+";
    YY_patterns[18] = "0x[0-9a-fA-F]+";
    YY_patterns[19] = "[\\ \\n\\f\\r\\t\\v]";
    YY_patterns[20] = ".";

	YY_Re YY_automas[21];
    for (int YY_i = 0; YY_i < 21; YY_i++) {
        YY_automas[YY_i].DoIt(YY_patterns[YY_i]);
    }

    typedef void(*YY_PtrFunc)(string);
    YY_PtrFunc YY_actions[21];
    YY_actions[0] = [](string yytext) { cout << "+" << endl; };
    YY_actions[1] = [](string yytext) { cout << "-" << endl; };
    YY_actions[2] = [](string yytext) { cout << "*" << endl; };
    YY_actions[3] = [](string yytext) { cout << "/" << endl; };
    YY_actions[4] = [](string yytext) { cout << ">" << endl; };
    YY_actions[5] = [](string yytext) { cout << "<" << endl; };
    YY_actions[6] = [](string yytext) { cout << "=" << endl; };
    YY_actions[7] = [](string yytext) { cout << "(" << endl; };
    YY_actions[8] = [](string yytext) { cout << ")" << endl; };
    YY_actions[9] = [](string yytext) { cout << ";" << endl; };
    YY_actions[10] = [](string yytext) { cout << "IF" << endl; };
    YY_actions[11] = [](string yytext) { cout << "THEN" << endl; };
    YY_actions[12] = [](string yytext) { cout << "ELSE" << endl; };
    YY_actions[13] = [](string yytext) { cout << "WHILE" << endl; };
    YY_actions[14] = [](string yytext) { cout << "DO" << endl; };
    YY_actions[15] = [](string yytext) { cout << "IDN\t" << yytext << endl; };
    YY_actions[16] = [](string yytext) { cout << "INT10\t" << yytext << endl; };
    YY_actions[17] = [](string yytext) { cout << "INT8\t" << yytext << endl; };
    YY_actions[18] = [](string yytext) { cout << "INT16\t" << yytext << endl; };
    YY_actions[19] = [](string yytext) { };
    YY_actions[20] = [](string yytext) { cout << "ERROR" << endl; };


    string YY_input = "0  92+data>  0x3f  00  while";
    cout << "Input string is:" << endl << endl << YY_input << endl;

    cout << endl;

    cout << "The result is:" << endl << endl;
    int YY_ind = 0;
    int YY_len = YY_input.length();
    while (YY_ind < YY_len) {
        int YY_max_match = 0;
        int YY_max_pattern = 0;
        for (int YY_i = 0; YY_i < 21; YY_i++) {
            int YY_len_match = YY_automas[YY_i].Match(YY_input.substr(YY_ind));
            if (YY_len_match > YY_max_match) {
                YY_max_pattern = YY_i;
                YY_max_match = YY_len_match;
            }
        }
        YY_actions[YY_max_pattern](YY_input.substr(YY_ind, YY_max_match));
        YY_ind = YY_ind + YY_max_match;
    }
    cout << endl;

    system("pause");

    return 0;
}
