#pragma once

#include <string>
#include "CMDLineUtility.h"

using namespace std;

class UEFPS_API GitUtility
{
public:
	GitUtility(string gitLocation, string repoLocation);
	virtual string GetGitRepoVersion();
protected:
	string gitLoc;
	string repoLoc;
	CMDLineUtility* cmdLineUtility;
};
