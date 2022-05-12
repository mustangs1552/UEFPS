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
	string ver = GetVersion();
	FText widgetText = FText::FromString((ver.empty()) ? "Unable to get version." : ver.c_str());

	return SNew(SDockTab).TabRole(ETabRole::NomadTab)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight().Padding(5)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot().AutoWidth()
				[
					SNew(STextBlock).Text(FText::FromString("Generated Version: "))
				]
				+SHorizontalBox::Slot().AutoWidth()
				[
					SNew(STextBlock).Text(widgetText)
				]
			]
			+SVerticalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight().Padding(5)
			[
				SNew(SButton).Text(FText::FromString("Apply Version")).OnClicked_Raw(this, &FAutoVersioningModule::ApplyVersionToConfig)
			]
			+SVerticalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight().Padding(5, 20, 5, 5)
			[
				SNew(STextBlock).Text(FText::FromString("Settings"))
			]
			+SVerticalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight().Padding(5)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot().AutoWidth()
				[
					SNew(STextBlock).Text(FText::FromString("Add Pre-Release: "))
				]
				+SHorizontalBox::Slot().AutoWidth()
				[
					SNew(SCheckBox)
				]
			]
		];
}

void FAutoVersioningModule::PluginButtonClicked()
{
	versioning = new Versioning();
	FGlobalTabmanager::Get()->TryInvokeTab(AutoVersioningTabName);
}

void FAutoVersioningModule::UpdateVersioning() const
{
	versioning->preReleaseText = (usePreReleaseText) ? preReleaseText : "";
	versioning->buildText = (useBuildText) ? buildText : "";
}

string FAutoVersioningModule::GetVersion() const
{
	UpdateVersioning();
	return versioning->VersionPreReleaseBuild();
}

FReply FAutoVersioningModule::ApplyVersionToConfig() const
{
	versioning->SetProjectSettingsVersion(GetVersion());
	return FReply::Handled();
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