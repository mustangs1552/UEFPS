#pragma once

#include "IVersioning.h"
#include "VersioningToolUtility.h"

class AUTOVERSIONING_API VersioningTool : public IVersioning
{
public:
	VersioningTool();

	virtual string GitVersion();
	virtual string VersionPreReleaseBuild();

	virtual void IncrementMajorVersion();
	virtual void IncrementMinorVersion();
	virtual void RemoveIncrements();
	virtual void SetPreReleaseText(string text);
	virtual void SetBuildText(string text);

	virtual void SetProjectSettingsVersion(string version);

protected:
	VersioningToolUtility* versioningToolUtility;
};
