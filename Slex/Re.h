#pragma once

#include"DfaToDriveTable.h"

#include<string>

class Re {
public:
    Re();
    Re(std::string original_re);
    void DoIt(std::string original_re);
    int Match(std::string input);

private:
    DriveTable *dt;
};