#include"Re.h"

#include<iostream>
#include<string>

using namespace std;

//============================== T E S T ==============================

int main() {
    string original_re = "0|[1-9][0-9]*";
    
    Re re(original_re);

    string input = "1234567890";

    int matched_length = re.Match(input);

    cout << matched_length << endl;

    system("pause");

    return 0;
}