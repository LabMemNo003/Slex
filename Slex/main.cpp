#include"Re.h"

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdio>

using namespace std;

//============================== T E S T ==============================

int main(int argc, char *argv[]) {
#ifdef DEBUG
    cout << argv[0] << endl;
#endif // DEBUG

    string inFileName;
    cout << "Please input inFileName:\n";
    getline(cin, inFileName);
#ifdef DEBUG
    cout << inFileName << endl;
#endif // DEBUG


    string outFileName;
    cout << "Please input outFileName:\n";
    getline(cin, outFileName);
#ifdef DEBUG
    cout << outFileName << endl;
#endif // DEBUG


    ifstream inFile(inFileName, ios::in);
    if (!inFile.is_open()) {
        cout << "Open file failure" << endl;
    }

    string line;
    while (getline(inFile, line)) {
        if (line[0] == '%' && line[1] == '%') {
            break;
        }
    }

    vector<string> reStrs;
    vector<string> actionStrs;
    int cntStrs = 0;

    while (getline(inFile, line)) {
        if (line[0] == '%' && line[1] == '%') {
            break;
        }

        string tmpRe;
        string tmpAction;
        
        int ind = 0;
        int len = line.length();
        while (ind < len) {
            if ((line[ind] == ' ' && line[ind - 1] != '\\') || line[ind] == '\t') {
                reStrs.push_back(tmpRe);
#ifdef DEBUG
                cout << tmpRe << endl;
#endif // DEBUG
                break;
            }
            if (line[ind] == '\\')
                tmpRe.push_back('\\');
            tmpRe.push_back(line[ind]);
            ind++;
        }

        while (line[ind] != '{') {
            ind++;
        }
        tmpAction = line.substr(ind);
        actionStrs.push_back(tmpAction);

        cntStrs++;
#ifdef DEBUG
        cout << tmpAction << endl;
#endif // DEBUG
    }

    string userCode;
    while (getline(inFile, line)) {
        userCode = userCode + line;
    }

    inFile.close();

    //===============================================================

    ofstream outFile(outFileName, ios::out);
    if (!outFile.is_open()) {
        cout << "Open file failure" << endl;
    }

    outFile
        << "#include\"Re.h\"\n"
        << "\n"
        << "#include<iostream>\n"
        << "#include<string>\n"
        << "#include<cstdio>\n"
        << "\n"
        << "using namespace std;\n"
        << "\n"
        << userCode
        << "\n"
        << "int main(int argc, char *argv[]) {\n"
        << "    string YY_patterns[" << cntStrs << "];\n";
    for (int i = 0; i < cntStrs; i++) {
        outFile << "    YY_patterns[" << i << "]=\"" << reStrs[i] << "\";\n";
    }

    outFile
        << "    \n"
        << "    YY_Re YY_automas[" << cntStrs << "];\n"
        << "    for (int YY_i = 0; YY_i < " << cntStrs << "; YY_i++) {\n"
        << "        YY_automas[YY_i].DoIt(YY_patterns[YY_i]);\n"
        << "    }\n"
        << "    \n"
        << "    typedef void(*YY_PtrFunc)(string);\n"
        << "    YY_PtrFunc YY_actions[" << cntStrs << "];\n";
    for (int i = 0; i < cntStrs; i++) {
        outFile << "    YY_actions[" << i << "] = [](string yytext) " << actionStrs[i] << ";\n";
    }

    outFile
        << "    \n"
        << "    string YY_input;\n"
        << "    while (getline(cin, YY_input)){\n"
        << "        int YY_ind = 0;\n"
        << "        int YY_len = YY_input.length();\n"
        << "        while (YY_ind < YY_len){\n"
        << "            int YY_max_match = 0;\n"
        << "            int YY_max_pattern = 0;\n"
        << "            for (int YY_i = 0; YY_i < " << cntStrs << "; YY_i++) {\n"
        << "                int YY_len_match = YY_automas[YY_i].Match(YY_input.substr(YY_ind));\n"
        << "                if (YY_len_match > YY_max_match) {\n"
        << "                    YY_max_pattern = YY_i;\n"
        << "                    YY_max_match = YY_len_match;\n"
        << "                }\n"
        << "            }\n"
        << "        YY_actions[YY_max_pattern](YY_input.substr(YY_ind, YY_max_match));\n"
        << "        YY_ind = YY_ind + YY_max_match;\n"
        << "        }\n"
        << "    }\n"
        << "    \n"
        << "    getchar();\n"
        << "    \n"
        << "    return 0;\n"
        << "}\n";

    outFile.close();

    getchar();

    return 0;
}