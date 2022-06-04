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
	mutable string version;
	mutable bool usePreReleaseText;
	mutable string preReleaseText;
	mutable bool useBuildText;
	mutable string buildText;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	void SaveSettings() const;
	void LoadSettings();
	void SetupVersioning();
	void UpdateVersioning() const;
	string UpdateVersion() const;
	string UpdateAndApplyVersion();
	FText GetVersionText() const;
	FReply OnUpdateButtonClicked() const;
	FReply OnApplyVersionButtonClicked() const;
	ECheckBoxState GetUsePreReleaseText() const;
	void OnUsePreReleaseTextCBStateChanged(ECheckBoxState inState) const;
	FText GetPreReleaseText() const;
	void OnPreReleaseTextETBTextCommitted(const FText& newText, ETextCommit::Type commitType);
	ECheckBoxState GetUseBuildText() const;
	void OnUseBuildTextCBStateChanged(ECheckBoxState inState) const;
	FText GetBuildText() const;
	void OnBuildTextETBTextCommitted(const FText& newText, ETextCommit::Type commitType);
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
