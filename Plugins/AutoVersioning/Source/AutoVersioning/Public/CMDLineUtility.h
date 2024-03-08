#pragma once

#include <string>
#include <Windows.h>

using namespace std;

class AUTOVERSIONING_API CMDLineUtility
{
public:
    string ExecCMD(string cmd);
};
