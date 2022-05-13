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
	mutable bool usePreReleaseText;
	mutable string preReleaseText;
	mutable bool useBuildText;
	mutable string buildText;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	void UpdateVersioning() const;
	string GetVersion() const;
	FReply OnApplyVersionButtonClicked() const;
	void OnUsePreReleaseTextCBStateChanged(ECheckBoxState inState) const;
	void OnUseBuildTextCBStateChanged(ECheckBoxState inState) const;
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
