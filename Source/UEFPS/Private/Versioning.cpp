#include "Versioning.h"

#include "GitUtility.h"

Versioning::Versioning()
{
	git = new GitUtility("C:\\Users\\musta\\AppData\\Local\\Atlassian\\SourceTree\\git_local\\cmd\\git.exe", "C:\\Repos\\Online\\Tools\\MattRGeorge");
}

string Versioning::Version()
{
	return git->GetGitRepoVersion();
}
string Versioning::VersionPreRelease()
{
	string ver = Version();
	if (!ver.empty() && !preReleaseText.empty()) ver += "-" + preReleaseText;
	return ver;
}
string Versioning::VersionBuild()
{
	string ver = Version();
	if (!ver.empty() && !buildText.empty()) ver += "+" + buildText;
	return ver;
}
string Versioning::VersionPreReleaseBuild()
{
	string ver = VersionPreRelease();
	if (!ver.empty() && !buildText.empty()) ver += "+" + buildText;
	return ver;
}