#include "VersioningToolUtility.h"

VersioningToolUtility::VersioningToolUtility(string versioningToolLocation) : toolLoc(versioningToolLocation)
{
	cmdLineUtility = new CMDLineUtility();
}

/// <summary>
/// The Git command of the Versioning Tool.
/// </summary>
/// <param name="args">The list of arguments to pass to the tool.</param>
/// <param name="preReleaseText">The pre-release text argument to add to the generated verion.</param>
/// <param name="buildText">The build text argument to add to the generated verion.</param>
/// <returns>The generated version.</returns>
string VersioningToolUtility::GitCMD(vector<VersioningToolGitCMDArgs> args, string preReleaseText, string buildText)
{
	if (cmdLineUtility == NULL) return "";

	string toolPath = toolLoc + (toolLoc[toolLoc.length() - 1] == '\\' ? "" : "\\") + "VersioningTool.exe ";
	string argString = "";
	for (int i = 0; i < args.size(); i++) argString += args[i] + " ";
	string preRelease = preReleaseText == "NULL" ? "" : "-" + preReleaseText + " ";
	string build = buildText == "NULL" ? "" : "+" + buildText;
	return cmdLineUtility->ExecCMD(toolPath + "Git " + argString + preRelease + build);
}