#include "Versioning.h"

Versioning::Versioning()
{
	FString gitPath = FindGitPath();
	FString repoPath = FindRepoPath();
	git = new GitUtility(string(TCHAR_TO_UTF8(*gitPath)), string(TCHAR_TO_UTF8(*repoPath)));
}

void Versioning::SetPreReleaseText(string text)
{
	preReleaseText = RemoveIllegalChars(text);
}
void Versioning::SetBuildText(string text)
{
	buildText = RemoveIllegalChars(text);
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

FString Versioning::FindGitPath()
{
	FString configPath = FPaths::GeneratedConfigDir();
	FString sourceControlIniPath;
	FConfigCacheIni::LoadGlobalIniFile(sourceControlIniPath, TEXT("SourceControlSettings"), nullptr, false, false, true, true, *configPath);
	FString gitPath;
	GConfig->GetString(TEXT("GitSourceControl.GitSourceControlSettings"), TEXT("BinaryPath"), gitPath, sourceControlIniPath);

	return gitPath;
}
FString Versioning::FindRepoPath()
{
	return FPaths::ProjectDir();
}

string Versioning::RemoveIllegalChars(string text)
{
	string validText;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '.' || text[i] == '-' || (text[i] >= '0' && text[i] <= '9') || (text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
		{
			if (text[i] == '.' && i - 1 >= 0)
			{
				if (text[i - 1] != '.') validText += text[i];
			}
			else validText += text[i];
		}
	}
	return validText;
}