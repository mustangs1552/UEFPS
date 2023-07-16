#pragma once

#include "IVersioning.h"
#include "GitUtility.h"

class AUTOVERSIONING_API Versioning : public IVersioning
{
public:
	virtual void SetPreReleaseText(string text);
	virtual void SetBuildText(string text);
	Versioning(GitUtility* gitUtility);
	virtual string GitVersion();
	string Version();
	string VersionPreRelease();
	string VersionBuild();
	virtual string VersionPreReleaseBuild();
	virtual void IncrementMajorVersion();
	virtual void IncrementMinorVersion();
	virtual void RemoveIncrements();
	FString GetProjectSettingsVersion();
	virtual void SetProjectSettingsVersion(string newVersion);
protected:
	GitUtility* git;
	string preReleaseText;
	string buildText;
	int majorVerIncrements;
	int minorVerIncrements;

	string RemoveIllegalChars(string text);
	string ApplyVersionIncrements(string ver);
};
