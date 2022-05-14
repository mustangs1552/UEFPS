#include "Versioning.h"

Versioning::Versioning()
{
	FString gitPath = SetGitPath();
	FString repoPath = SetRepoPath();
	git = new GitUtility(string(TCHAR_TO_UTF8(*gitPath)), string(TCHAR_TO_UTF8(*repoPath)));
}

string Versioning::GetGitPath()
{
	return git->gitLoc;
}
string Versioning::GetRepoPath()
{
	return git->repoLoc;
}

string Versioning::Version()
{
	return git->GetGitRepoVersion();
}
string Versioning::VersionPreRelease()
{
	string ver = Version();
	if (!ver.empty() && !preReleaseText.empty()) ver += "-" + preReleaseText;
	return ver;
}
string Versioning::VersionBuild()
{
	string ver = Version();
	if (!ver.empty() && !buildText.empty()) ver += "+" + buildText;
	return ver;
}
string Versioning::VersionPreReleaseBuild()
{
	string ver = VersionPreRelease();
	if (!ver.empty() && !buildText.empty()) ver += "+" + buildText;
	return ver;
}

FString Versioning::GetProjectSettingsVersion()
{
	FString defaultGameIniPath = FString::Printf(TEXT("%sDefaultGame.ini"), *FPaths::SourceConfigDir());
	if (FPlatformFileManager::Get().GetPlatformFile().IsReadOnly(*defaultGameIniPath)) FPlatformFileManager::Get().GetPlatformFile().SetReadOnly(*defaultGameIniPath, false);
	FString ver;
	GConfig->GetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), ver, defaultGameIniPath);
	return ver;
}
void Versioning::SetProjectSettingsVersion(string newVersion)
{
	if (!newVersion.empty())
	{
		FString defaultGameIniPath = FString::Printf(TEXT("%sDefaultGame.ini"), *FPaths::SourceConfigDir());
		if (FPlatformFileManager::Get().GetPlatformFile().IsReadOnly(*defaultGameIniPath)) FPlatformFileManager::Get().GetPlatformFile().SetReadOnly(*defaultGameIniPath, false);
		GConfig->SetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), UTF8_TO_TCHAR(newVersion.c_str()), defaultGameIniPath);
		GConfig->Flush(false, defaultGameIniPath);
	}
}

FString Versioning::SetGitPath()
{
	FString sourceControlIniPath = FPaths::GeneratedConfigDir().Append("Windows/SourceControlSettings.ini");
	FString gitPath;
	GConfig->GetString(TEXT("GitSourceControl.GitSourceControlSettings"), TEXT("BinaryPath"), gitPath, sourceControlIniPath);

	return gitPath;
}
FString Versioning::SetRepoPath()
{
	return FPaths::ProjectDir();
}