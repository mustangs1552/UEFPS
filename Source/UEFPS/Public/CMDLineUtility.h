#pragma once

#include <string>

using namespace std;

class UEFPS_API CMDLineUtility
{
public:
    virtual string ExecCMD(string cmd);
};
