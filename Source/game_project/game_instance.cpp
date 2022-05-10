// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_instance.h"

Ugame_instance::Ugame_instance() {
	//game_mode_class_base = LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_projectGameModeBase"));
	game_mode_level_1_class = LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_mode_base_level_1"));
	//static ConstructorHelpers::FClassFinder<AGameModeBase> game_mode_class(TEXT("/Script/game_project.game_projectGameModeBase"));
}
void Ugame_instance::Init() {
	Super::Init();
	GetWorld()->GetWorldSettings()->DefaultGameMode = game_mode_level_1_class;
	//GetWorld()->GetWorldSettings()->DefaultGameMode = game_mode_level_1_class;
}
void Ugame_instance::Shutdown() {
	Super::Shutdown();
}
void Ugame_instance::StartGameInstance() {
	Super::StartGameInstance();
}