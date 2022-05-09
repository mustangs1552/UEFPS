#pragma once

#include "GitUtility.h"

class AUTOVERSIONING_API Versioning
{
public:
	string preReleaseText;
	string buildText;

	Versioning();
	string Version();
	string VersionPreRelease();
	string VersionBuild();
	string VersionPreReleaseBuild();
	FString GetProjectSettingsVersion();
	void SetProjectSettingsVersion(string newVersion);
protected:
	GitUtility* git;
};
