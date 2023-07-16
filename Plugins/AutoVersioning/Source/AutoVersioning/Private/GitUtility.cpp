#include "GitUtility.h"

#include <algorithm>

GitUtility::GitUtility()
{
    cmdLineUtility = new CMDLineUtility();

	gitLoc = string(TCHAR_TO_UTF8(*FindGitPath()));
	repoLoc = string(TCHAR_TO_UTF8(*FindRepoPath()));
}

string GitUtility::GetGitLocation()
{
	return gitLoc;
}

string GitUtility::GetRepoLocation()
{
	return repoLoc;
}

FString GitUtility::FindGitPath()
{
	FString configPath = FPaths::GeneratedConfigDir();
	FString sourceControlIniPath;
	FConfigCacheIni::LoadGlobalIniFile(sourceControlIniPath, TEXT("SourceControlSettings"), nullptr, false, false, true, true, *configPath);
	FString gitPath;
	GConfig->GetString(TEXT("GitSourceControl.GitSourceControlSettings"), TEXT("BinaryPath"), gitPath, sourceControlIniPath);

	return gitPath;
}
FString GitUtility::FindRepoPath()
{
	return FPaths::ProjectDir();
}

string GitUtility::GetGitRepoVersion()
{
    string cdCMD = "cd \"" + repoLoc + "\"";
    string gitCMD = "\"" + gitLoc + "\" describe --tags --long --match ""v[0-9]*""";
    string result = cmdLineUtility->ExecCMD(cdCMD + " & " + gitCMD);

    if (result.empty()) return "";
    replace(result.begin(), result.end(), '-', '.');
    return result.substr(1, result.find_last_of('.') - 1);
}