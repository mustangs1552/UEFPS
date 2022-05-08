#pragma once

#include "GitUtility.h"

class UEFPS_API Versioning
{
public:
	string preReleaseText;
	string buildText;

	Versioning();
	virtual string Version();
	virtual string VersionPreRelease();
	virtual string VersionBuild();
	virtual string VersionPreReleaseBuild();
protected:
	GitUtility* git;
};
