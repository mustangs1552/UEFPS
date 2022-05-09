// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoVersioning.h"
#include "AutoVersioningStyle.h"
#include "AutoVersioningCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName AutoVersioningTabName("AutoVersioning");

#define LOCTEXT_NAMESPACE "FAutoVersioningModule"

void FAutoVersioningModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAutoVersioningStyle::Initialize();
	FAutoVersioningStyle::ReloadTextures();

	FAutoVersioningCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAutoVersioningCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAutoVersioningModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAutoVersioningModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AutoVersioningTabName, FOnSpawnTab::CreateRaw(this, &FAutoVersioningModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAutoVersioningTabTitle", "AutoVersioning"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAutoVersioningModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAutoVersioningStyle::Shutdown();

	FAutoVersioningCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AutoVersioningTabName);
}

TSharedRef<SDockTab> FAutoVersioningModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	string ver = ApplyVersionToConfig();
	FText WidgetText = FText::FromString((ver.empty()) ? "Unable to get version." : ver.c_str());

	return SNew(SDockTab).TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox).HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FAutoVersioningModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(AutoVersioningTabName);
}

string FAutoVersioningModule::GetVersion()
{
	versioning = new Versioning();
	versioning->preReleaseText = "";
	versioning->buildText = "";
	return versioning->VersionPreReleaseBuild();
}

string FAutoVersioningModule::ApplyVersionToConfig()
{
	string ver = GetVersion();

	if (!ver.empty())
	{
		FString gamePath = FString::Printf(TEXT("%sDefaultGame.ini"), *FPaths::SourceConfigDir());
		if (FPlatformFileManager::Get().GetPlatformFile().IsReadOnly(*gamePath)) FPlatformFileManager::Get().GetPlatformFile().SetReadOnly(*gamePath, false);
		GConfig->SetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), UTF8_TO_TCHAR(ver.c_str()), gamePath);
		GConfig->Flush(false, gamePath);
	}

	return ver;
}

void FAutoVersioningModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAutoVersioningCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAutoVersioningCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAutoVersioningModule, AutoVersioning)