#include "VersioningTool.h"

VersioningTool::VersioningTool()
{
	versioningToolUtility = new VersioningToolUtility("");
}

string VersioningTool::GitVersion()
{
	return "";
}
string VersioningTool::VersionPreReleaseBuild()
{
	return "";
}

void VersioningTool::IncrementMajorVersion()
{

}
void VersioningTool::IncrementMinorVersion()
{

}
void VersioningTool::RemoveIncrements()
{

}
void VersioningTool::SetPreReleaseText(string text)
{

}
void VersioningTool::SetBuildText(string text)
{

}

void VersioningTool::SetProjectSettingsVersion(string version)
{

}