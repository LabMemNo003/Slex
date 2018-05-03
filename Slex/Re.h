#pragma once

#include"DfaToDriveTable.h"

#include<string>

class YY_Re {
public:
	YY_Re();
	YY_Re(std::string original_re);
    void DoIt(std::string original_re);
    int Match(std::string input);

private:
    DriveTable *dt;
};