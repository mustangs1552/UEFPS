#pragma once

#include <string>
#include "CMDLineUtility.h"

using namespace std;

class AUTOVERSIONING_API GitUtility
{
public:
	GitUtility();
	string GetGitLocation();
	string GetRepoLocation();
	string GetGitRepoVersion();
protected:
	CMDLineUtility* cmdLineUtility;
	string gitLoc;
	string repoLoc;

	FString FindGitPath();
	FString FindRepoPath();
};
