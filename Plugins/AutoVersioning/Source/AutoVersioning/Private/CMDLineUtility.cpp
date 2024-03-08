#include "CMDLineUtility.h"

string CMDLineUtility::ExecCMD(string cmd)
{
    /*char buffer[128];
    string result = "";

    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) return "popen failed!";

    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL) result += buffer;
    }

    _pclose(pipe);
    return result;*/

    HANDLE stdInHandles[2];
    HANDLE stdOutHandles[2];
    HANDLE stdErrHandles[2];
    CreatePipe(&stdInHandles[0], &stdInHandles[1], NULL, 4096);
    CreatePipe(&stdOutHandles[0], &stdOutHandles[1], NULL, 4096);
    CreatePipe(&stdErrHandles[0], &stdErrHandles[1], NULL, 4096);

    STARTUPINFOA startupInfo = { 0 };
    PROCESS_INFORMATION procInfo = { 0 };
    startupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    startupInfo.wShowWindow = SW_HIDE;
    startupInfo.hStdInput = stdInHandles[0];
    startupInfo.hStdOutput = stdOutHandles[1];
    startupInfo.hStdError = stdErrHandles[1];
    bool result = ::CreateProcessA("C:\\windows\\system32\\cmd.exe", const_cast<char*>(cmd.c_str()), NULL, NULL, false, 0, NULL, NULL, &startupInfo, &procInfo);
    if (result == false)
    {
        DWORD error = ::GetLastError();
        return "Error: " + to_string(error);
    }

    LPDWORD returnVal = new DWORD[1];
    ::GetExitCodeProcess(procInfo.hProcess, returnVal);
    return to_string(returnVal[0]);
}