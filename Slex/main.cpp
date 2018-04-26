#include"Re.h"

#include<iostream>
#include<string>

using namespace std;

//============================== T E S T ==============================

int main() {
    //string original_re = "0|[1-9][0-9]*"; // 0|(1|2|3|4|5|6|7|8|9)_((0|1|2|3|4|5|6|7|8|9)*)
    //string original_re = "0[1-7][0-7]*"; // 0_(1|2|3|4|5|6|7)_((0|1|2|3|4|5|6|7)*)
    //string original_re = "0x[0-9a-f]+"; // 0_x_((0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)_(0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)*)
    string original_re = "[^\\0-\\177]";

    Re re(original_re);

    string input = "1234567890";

    int matched_length = re.Match(input);

    cout << matched_length << endl;

    system("pause");

    return 0;
}