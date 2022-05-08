#include "CMDLineUtility.h"

#include <string>

using namespace std;

string CMDLineUtility::ExecCMD(string cmd)
{
    char buffer[128];
    string result = "";

    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) return "popen failed!";

    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL) result += buffer;
    }

    _pclose(pipe);
    return result;
}