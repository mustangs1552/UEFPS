#include "Versioning.h"

Versioning::Versioning()
{
	git = new GitUtility("C:\\Users\\musta\\AppData\\Local\\Atlassian\\SourceTree\\git_local\\cmd\\git.exe", "C:\\Repos\\Online\\Games\\UEFPS");
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
	FString gamePath = FString::Printf(TEXT("%sDefaultGame.ini"), *FPaths::SourceConfigDir());
	if (FPlatformFileManager::Get().GetPlatformFile().IsReadOnly(*gamePath)) FPlatformFileManager::Get().GetPlatformFile().SetReadOnly(*gamePath, false);
	FString ver;
	GConfig->GetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), ver, gamePath);
	return ver;
}
void Versioning::SetProjectSettingsVersion(string newVersion)
{
	if (!newVersion.empty())
	{
		FString gamePath = FString::Printf(TEXT("%sDefaultGame.ini"), *FPaths::SourceConfigDir());
		if (FPlatformFileManager::Get().GetPlatformFile().IsReadOnly(*gamePath)) FPlatformFileManager::Get().GetPlatformFile().SetReadOnly(*gamePath, false);
		GConfig->SetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), UTF8_TO_TCHAR(newVersion.c_str()), gamePath);
		GConfig->Flush(false, gamePath);
	}
}