#pragma once

#include"DfaToDriveTable.h"

#include<string>

class Re {
public:
    Re(std::string original_re);
    ~Re();
    int Match(std::string input);

private:
    DriveTable *dt;
};