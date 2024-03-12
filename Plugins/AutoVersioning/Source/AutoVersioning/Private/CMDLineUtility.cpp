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

    HANDLE pipeRead = NULL;
    HANDLE pipeWrite = NULL;
    SECURITY_ATTRIBUTES secAtts = { sizeof(SECURITY_ATTRIBUTES) };
    secAtts.bInheritHandle = true;
    secAtts.lpSecurityDescriptor = NULL;
    if (!CreatePipe(&pipeRead, &pipeWrite, &secAtts, 0)) return "";

    STARTUPINFOA startupInfo = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION procInfo = { 0 };
    startupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    startupInfo.wShowWindow = SW_HIDE;
    startupInfo.hStdOutput = pipeWrite;
    startupInfo.hStdError = pipeWrite;
    bool success = ::CreateProcessA(NULL, (LPSTR)("C:\\windows\\system32\\cmd.exe " + cmd).c_str(), NULL, NULL, true, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &procInfo);
    if (success == false)
    {
        UE_LOG(LogTemp, Error, TEXT("Error: C-%s."), UTF8_TO_TCHAR(to_string(::GetLastError()).c_str()));
        return "Error: C-" + to_string(::GetLastError());
    }

    string result = "";
    bool procEnded = false;
    bool r1Failed = false;
    for (; !procEnded;)
    {
        procEnded = WaitForSingleObject(procInfo.hProcess, 50) == WAIT_OBJECT_0;

        for (;;)
        {
            char buff[1024];
            DWORD dwRead = 0;
            DWORD dwAvail = 0;

            if (::PeekNamedPipe(pipeRead, NULL, 0, NULL, &dwAvail, NULL)) r1Failed = true;
            if (!dwAvail)
            {
                UE_LOG(LogTemp, Error, TEXT("Error: R-2."));
                break;
            }
            if (!::ReadFile(pipeRead, buff, min(sizeof(buff) - 1, dwAvail), &dwRead, NULL) || !dwRead)
            {
                UE_LOG(LogTemp, Error, TEXT("Error: R-3."));
                break;
            }

            buff[dwRead] = 0;
            result += buff;
        }
    }
    if (r1Failed) UE_LOG(LogTemp, Error, TEXT("Error: R-1: %s"), result.c_str());

    CloseHandle(pipeWrite);
    CloseHandle(pipeRead);
    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);
    return result;
}