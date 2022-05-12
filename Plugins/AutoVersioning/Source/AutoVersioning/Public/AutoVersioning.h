#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Versioning.h"

class FToolBarBuilder;
class FMenuBuilder;

class FAutoVersioningModule : public IModuleInterface
{
public:
	Versioning* versioning;
	bool usePreReleaseText;
	string preReleaseText;
	bool useBuildText;
	string buildText;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	void UpdateVersioning() const;
	string GetVersion() const;
	FReply ApplyVersionToConfig() const;
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
