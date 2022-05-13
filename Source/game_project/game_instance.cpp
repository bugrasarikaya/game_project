// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_instance.h"
#include "GameFramework/GameUserSettings.h"

Ugame_instance::Ugame_instance() {
	//game_mode_class_base = LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_projectGameModeBase"));
	game_mode_level_1_class = LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_mode_base_level_1"));
	//static ConstructorHelpers::FClassFinder<AGameModeBase> game_mode_class(TEXT("/Script/game_project.game_projectGameModeBase"));
    game_user_settings = const_cast<UGameUserSettings*>(GetDefault<UGameUserSettings>());
    //UGameUserSettings* game_user_settings = GEngine->GetGameUserSettings();
}
void Ugame_instance::Init() {
	Super::Init();
	world = GetWorld();
	world->GetWorldSettings()->DefaultGameMode = game_mode_level_1_class;
    if (game_user_settings) {
        game_user_settings->SetScreenResolution(game_user_settings->GetDesktopResolution());
        game_user_settings->SetFullscreenMode(EWindowMode::Fullscreen);
        //game_user_settings->SetDynamicResolutionEnabled(true);
        game_user_settings->SetVSyncEnabled(true);
        game_user_settings->SetAntiAliasingQuality(0);
        //game_user_settings->SaveSettings();
        game_user_settings->ApplySettings(false);
    }
    FString current_level_name = world->GetMapName();
    current_level_name.RemoveFromStart(world->StreamingLevelsPrefix);
    FString new_level_name = "level_1";
    if (current_level_name != new_level_name) world->ServerTravel(new_level_name, false);
}
void Ugame_instance::Shutdown() {
	Super::Shutdown();
}
void Ugame_instance::StartGameInstance() {
	Super::StartGameInstance();
}