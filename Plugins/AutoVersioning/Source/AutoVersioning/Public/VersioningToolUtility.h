#pragma once

#include <string>
#include "CMDLineUtility.h"

using namespace std;

enum VersioningToolGitCMDArgs
{
	IncrementMajor,
	IncrementMinor,
	IncrementPatch,
	PreCommitMode,
	ApplyTag,
	ApplyTagPush,
	MergeUEVersion,
	ApplyUEProjectVersion
};

class AUTOVERSIONING_API VersioningToolUtility
{
public:
	const string toolLoc;

	VersioningToolUtility(string versioningToolLocation);
	string GitCMD(vector<VersioningToolGitCMDArgs> args, string preReleaseText = "", string buildText = "");
protected:
	CMDLineUtility* cmdLineUtility;
};
