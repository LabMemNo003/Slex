#include"Re.h"

#include<iostream>
#include<string>

using namespace std;

//============================== T E S T ==============================

int main() {
    //string original_re = "01|2*";
    string original_re = "0|[1-9][0-9]*"; // 0|(1|2|3|4|5|6|7|8|9)_((0|1|2|3|4|5|6|7|8|9)*)
    //string original_re = "0[1-7][0-7]*"; // 0_(1|2|3|4|5|6|7)_((0|1|2|3|4|5|6|7)*)
    //string original_re = "0x[0-9a-f]+"; // 0_x_((0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)_(0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)*)
    //string original_re = "[^\\0-\\57\\72-\\177]"; //(0|1|2|3|4|5|6|7|8|9)
    //string original_re = "[-^`~!@#$%&*()_+={}|;':\",.<>/?]"; // (!|"|#|$|%|&|'|(|)|*|+|,|-|.|/|:|;|<|=|>|?|@|^|_|`|{|||}|~)
    //string original_re = "[\"0-9\"]"; // ("|0|1|2|3|4|5|6|7|8|9)
    //string original_re = "\"1 [0-9] 1\""; // 1_ _[_0_-_9_]_ _1
    //string original_re = "\"1 -^`~!@#$%&*()_+={}|;':\\\",.<>/? 1\""; // 1_ _-_^_`_~_!_@_#_$_%_&_*_(_)___+_=_{_}_|_;_'_:_"_,_._<_>_/_?_ _1
    //string original_re = "\"1 -^`~!@#$%&*()_+={}|;':\\\",.<>/? 1\"";

    Re re(original_re);
    /*
    string input = "1234567890";

    int matched_length = re.Match(input);

    cout << matched_length << endl;
    */
    system("pause");

    return 0;
}