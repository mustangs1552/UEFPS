#pragma once

#include <string>
#include "CMDLineUtility.h"

using namespace std;

class AUTOVERSIONING_API GitUtility
{
public:
	GitUtility(string gitLocation, string repoLocation);
	string GetGitRepoVersion();
protected:
	string gitLoc;
	string repoLoc;
	CMDLineUtility* cmdLineUtility;
};
