// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_mode_base_level_1.h"
#include "paper_plane.h"
#include "spawning_info_interface.h"


Agame_mode_base_level_1::Agame_mode_base_level_1() {
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FClassFinder<APawn> pawn_class(TEXT("/Script/game_project.paper_player"));
    if (pawn_class.Class != NULL) DefaultPawnClass = pawn_class.Class;
    static ConstructorHelpers::FClassFinder<AHUD> hud_class(TEXT("/Script/game_project.combat_hud"));
    if (hud_class.Class != NULL) HUDClass = hud_class.Class;
    world = GetWorld();
    paper_plane_class = LoadClass<Apaper_plane>(world, TEXT("/Script/game_project.paper_plane"));
    //GetCurrentLevelName();
    game_mode_class_base = LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_projectGameModeBase"));
}
void Agame_mode_base_level_1::BeginPlay() {
	Super::BeginPlay();
	FActorSpawnParameters paper_plane_spawn_parameters;
	//paper_plane_spawn_parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    //TArray<Apaper_plane*> paper_floor_1;
    //Apaper_plane* paper_floor_array = new Apaper_plane[10];
    TArray<FVector> location_info_array = { FVector(0.0f) };
    TArray<FRotator> rotation_info_array = { FRotator(0.0f) };
    check(location_info_array.Num() == rotation_info_array.Num());
    TArray<Apaper_plane*> paper_floor_array;
    paper_floor_array.SetNum(location_info_array.Num());
    
    paper_floor_array[0] = world->SpawnActor<Apaper_plane>(paper_plane_class, location_info_array[0], rotation_info_array[0], paper_plane_spawn_parameters);
	//if (paper_floor_1) {

	//}
 //   Destroy();
    //GetWorld()->GetWorldSettings()->DefaultGameMode = game_mode_class_base;
    //UGameplayStatics::OpenLevel(GetWorld(), FName("level_1"));

    
    //UWorld* World = GEngine->GetWorldFromContextObject(GetWorld(), EGetWorldErrorMode::LogAndReturnNull);
    //const ETravelType TravelType = TRAVEL_Relative;
    //GEngine->SetClientTravel(World, *level_name, TravelType);
    FString current_level_name = world->GetMapName();
    current_level_name.RemoveFromStart(world->StreamingLevelsPrefix);
    FString new_level_name = "level_1";
    if(current_level_name != new_level_name) world->ServerTravel(new_level_name, false);
}
void Agame_mode_base_level_1::Tick(float delta_time) {
    Super::Tick(delta_time);
    //UE_LOG(LogTemp, Warning, TEXT("LOL"));
   
}