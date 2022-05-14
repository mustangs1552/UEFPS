#pragma once

#include "GitUtility.h"

class AUTOVERSIONING_API Versioning
{
public:
	void SetPreReleaseText(string text);
	void SetBuildText(string text);
	string GetGitPath();
	string GetRepoPath();
	Versioning();
	string Version();
	string VersionPreRelease();
	string VersionBuild();
	string VersionPreReleaseBuild();
	FString GetProjectSettingsVersion();
	void SetProjectSettingsVersion(string newVersion);
protected:
	GitUtility* git;
	string preReleaseText;
	string buildText;

	FString SetGitPath();
	FString SetRepoPath();
	string RemoveIllegalChars(string text);
};
