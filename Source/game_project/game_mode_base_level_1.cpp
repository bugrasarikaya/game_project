// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_mode_base_level_1.h"
#include "static_mesh_plane.h"
#include "spawning_info_interface.h"


Agame_mode_base_level_1::Agame_mode_base_level_1() {
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FClassFinder<APawn> pawn_class(TEXT("/Script/game_project.paper_player"));
    if (pawn_class.Class != NULL) DefaultPawnClass = pawn_class.Class;
    static ConstructorHelpers::FClassFinder<AHUD> hud_class(TEXT("/Script/game_project.combat_hud"));
    if (hud_class.Class != NULL) HUDClass = hud_class.Class;
    world = GetWorld();
    static_mesh_plane_class = LoadClass<Astatic_mesh_plane>(world, TEXT("/Script/game_project.static_mesh_plane"));
    material_asset = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_inst_type_3_part_4.plane_material_inst_type_3_part_4"));
    game_mode_class_base = LoadClass<AGameModeBase>(world, TEXT("/Script/game_project.game_projectGameModeBase"));
}
void Agame_mode_base_level_1::BeginPlay() {
	Super::BeginPlay();
	FActorSpawnParameters paper_plane_spawn_parameters;
	//paper_plane_spawn_parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    //TArray<Apaper_plane*> paper_floor_1;
    //Apaper_plane* paper_floor_array = new Apaper_plane[10];
    //TArray<FVector> location_info_array = { FVector(0.0f) };
    //TArray<FRotator> rotation_info_array = { FRotator(0.0f) };
    //check(location_info_array.Num() == rotation_info_array.Num());
    //TStaticArray< TStaticArray<Astatic_mesh_plane*, 50>, 30> floor_array_1;
    //floor_array[50][30];
    FTransform local_to_world;
    temp_static_mesh_plane = GetWorld()->SpawnActor<Astatic_mesh_plane>();
    plane_size = ((temp_static_mesh_plane->GetStaticMeshComponent()->CalcBounds(local_to_world).BoxExtent).X) * 2;
    //initial_floor_0_location_x = plane_size;
    //initial_floor_0_location_y = plane_size;
    //initial_floor_0_location_z = 0.0f;
    //initial_wall_0_left_location_x = initial_floor_0_location_x;
    //initial_wall_0_left_location_y = initial_floor_0_location_y - (plane_size / 2);
    //initial_wall_0_left_location_z = initial_floor_0_location_z + (plane_size / 2);
    temp_static_mesh_plane->Destroy();
    floor_0_array.SetNum(floor_0_row_count);
    for (int32 i = 0; i < floor_0_row_count; i++) floor_0_array[i].inner_plane_array.SetNum(floor_0_column_count);
    last_floor_0_location_x = initial_floor_0_location_x;
    last_floor_0_location_y = initial_floor_0_location_y;
    last_floor_0_location_z = initial_floor_0_location_z;
    temp_location_y = last_floor_0_location_y;
    for (int32 floor_0_row_number = 0; floor_0_row_number < floor_0_row_count; floor_0_row_number++, last_floor_0_location_x += plane_size) {
        last_floor_0_location_y = temp_location_y;
        for (int32 floor_0_column_number = 0; floor_0_column_number < floor_0_column_count; floor_0_column_number++, last_floor_0_location_y += plane_size) {
            floor_0_array[floor_0_row_number].inner_plane_array[floor_0_column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, FVector(last_floor_0_location_x, last_floor_0_location_y, last_floor_0_location_z), floor_rotation, paper_plane_spawn_parameters);
            floor_0_array[floor_0_row_number].inner_plane_array[floor_0_column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
        }
    }
    last_floor_0_location_x -= plane_size;
    last_floor_0_location_y -= plane_size;
    initial_wall_0_right_location_x = last_floor_0_location_x;
    initial_wall_0_right_location_y = last_floor_0_location_y + (plane_size / 2);
    initial_wall_0_right_location_z = last_floor_0_location_z + (plane_size / 2);
    wall_0_right_array.SetNum(wall_0_right_row_count);
    for (int32 i = 0; i < wall_0_right_row_count; i++) wall_0_right_array[i].inner_plane_array.SetNum(wall_0_right_column_count);
    last_wall_0_right_location_x = initial_wall_0_right_location_x;
    last_wall_0_right_location_y = initial_wall_0_right_location_y;
    last_wall_0_right_location_z = initial_wall_0_right_location_z;
    temp_location_x = last_wall_0_right_location_x;
    for (int32 wall_0_right_row_number = 0; wall_0_right_row_number < wall_0_right_row_count; wall_0_right_row_number++, last_wall_0_right_location_z += plane_size) {
        last_wall_0_right_location_x = temp_location_x;
        for (int32 wall_0_right_column_number = 0; wall_0_right_column_number < wall_0_right_column_count; wall_0_right_column_number++, last_wall_0_right_location_x -= plane_size) {
            wall_0_right_array[wall_0_right_row_number].inner_plane_array[wall_0_right_column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, FVector(last_wall_0_right_location_x, last_wall_0_right_location_y, last_wall_0_right_location_z), wall_right_rotation, paper_plane_spawn_parameters);
            wall_0_right_array[wall_0_right_row_number].inner_plane_array[wall_0_right_column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
        }
    }
    last_wall_0_right_location_x += plane_size;
    last_wall_0_right_location_z -= plane_size;
    initial_wall_0_back_location_x = last_wall_0_right_location_x - (plane_size / 2);
    initial_wall_0_back_location_y = last_wall_0_right_location_y - (plane_size / 2);;
    initial_wall_0_back_location_z = last_wall_0_right_location_z;
    wall_0_back_array.SetNum(wall_0_back_row_count);
    for (int32 i = 0; i < wall_0_back_row_count; i++) wall_0_back_array[i].inner_plane_array.SetNum(wall_0_back_column_count);
    last_wall_0_back_location_x = initial_wall_0_back_location_x;
    last_wall_0_back_location_y = initial_wall_0_back_location_y;
    last_wall_0_back_location_z = initial_wall_0_back_location_z;
    temp_location_y = last_wall_0_back_location_y;
    for (int32 wall_0_back_row_number = 0; wall_0_back_row_number < wall_0_back_row_count; wall_0_back_row_number++, last_wall_0_back_location_z -= plane_size) {
        last_wall_0_back_location_y = temp_location_y;
        for (int32 wall_0_back_column_number = 0; wall_0_back_column_number < wall_0_back_column_count; wall_0_back_column_number++, last_wall_0_back_location_y -= plane_size) {
            wall_0_back_array[wall_0_back_row_number].inner_plane_array[wall_0_back_column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, FVector(last_wall_0_back_location_x, last_wall_0_back_location_y, last_wall_0_back_location_z), wall_back_rotation, paper_plane_spawn_parameters);
            wall_0_back_array[wall_0_back_row_number].inner_plane_array[wall_0_back_column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
        }
    }
    last_wall_0_back_location_y += plane_size;
    last_wall_0_back_location_z += plane_size;
    initial_wall_0_left_location_x = last_wall_0_back_location_x + (plane_size / 2);
    initial_wall_0_left_location_y = last_wall_0_back_location_y - (plane_size / 2);
    initial_wall_0_left_location_z = last_wall_0_back_location_z;
    wall_0_left_array.SetNum(wall_0_left_row_count);
    for (int32 i = 0; i < wall_0_left_row_count; i++) wall_0_left_array[i].inner_plane_array.SetNum(wall_0_left_column_count);
    last_wall_0_left_location_x = initial_wall_0_left_location_x;
    last_wall_0_left_location_y = initial_wall_0_left_location_y;
    last_wall_0_left_location_z = initial_wall_0_left_location_z;
    temp_location_x = last_wall_0_left_location_x;
    for (int32 wall_0_left_row_number = 0; wall_0_left_row_number < wall_0_left_row_count; wall_0_left_row_number++, last_wall_0_left_location_z += plane_size) {
        last_wall_0_left_location_x = temp_location_x;
        for (int32 wall_0_left_column_number = 0; wall_0_left_column_number < wall_0_left_column_count; wall_0_left_column_number++, last_wall_0_left_location_x += plane_size) {
            wall_0_left_array[wall_0_left_row_number].inner_plane_array[wall_0_left_column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, FVector(last_wall_0_left_location_x, last_wall_0_left_location_y, last_wall_0_left_location_z), wall_left_rotation, paper_plane_spawn_parameters);
            wall_0_left_array[wall_0_left_row_number].inner_plane_array[wall_0_left_column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
        }
    }
    last_wall_0_left_location_x -= plane_size;
    last_wall_0_left_location_z -= plane_size;
    initial_wall_0_front_location_x = last_wall_0_left_location_x + (plane_size / 2);
    initial_wall_0_front_location_y = last_wall_0_left_location_y + (plane_size / 2);
    initial_wall_0_front_location_z = last_wall_0_left_location_z;
    wall_0_front_array.SetNum(wall_0_front_row_count);
    for (int32 i = 0; i < wall_0_front_row_count; i++) wall_0_front_array[i].inner_plane_array.SetNum(wall_0_front_column_count);
    last_wall_0_front_location_x = initial_wall_0_front_location_x;
    last_wall_0_front_location_y = initial_wall_0_front_location_y;
    last_wall_0_front_location_z = initial_wall_0_front_location_z;
    temp_location_y = last_wall_0_front_location_y;
    for (int32 wall_0_front_row_number = 0; wall_0_front_row_number < wall_0_front_row_count; wall_0_front_row_number++, last_wall_0_front_location_z -= plane_size) {
        last_wall_0_front_location_y = temp_location_y;
        for (int32 wall_0_front_column_number = 0; wall_0_front_column_number < wall_0_front_column_count; wall_0_front_column_number++, last_wall_0_front_location_y += plane_size) {
            wall_0_front_array[wall_0_front_row_number].inner_plane_array[wall_0_front_column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, FVector(last_wall_0_front_location_x, last_wall_0_front_location_y, last_wall_0_front_location_z), wall_front_rotation, paper_plane_spawn_parameters);
            wall_0_front_array[wall_0_front_row_number].inner_plane_array[wall_0_front_column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
        }
    }
    last_wall_0_front_location_y -= plane_size;
    last_wall_0_front_location_z += plane_size;
    initial_ceiling_0_location_x = last_wall_0_left_location_x;
    initial_ceiling_0_location_y = last_wall_0_left_location_y + (plane_size / 2);
    initial_ceiling_0_location_z = last_wall_0_left_location_z + (plane_size / 2);
    ceiling_0_array.SetNum(ceiling_0_row_count);
    for (int32 i = 0; i < ceiling_0_row_count; i++) ceiling_0_array[i].inner_plane_array.SetNum(ceiling_0_column_count);
    last_ceiling_0_location_x = initial_ceiling_0_location_x;
    last_ceiling_0_location_y = initial_ceiling_0_location_y;
    last_ceiling_0_location_z = initial_ceiling_0_location_z;
    temp_location_y = last_ceiling_0_location_y;
    for (int32 ceiling_0_row_number = 0; ceiling_0_row_number < ceiling_0_row_count; ceiling_0_row_number++, last_ceiling_0_location_x -= plane_size) {
        last_ceiling_0_location_y = temp_location_y;
        for (int32 ceiling_0_column_number = 0; ceiling_0_column_number < ceiling_0_column_count; ceiling_0_column_number++, last_ceiling_0_location_y += plane_size) {
            ceiling_0_array[ceiling_0_row_number].inner_plane_array[ceiling_0_column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, FVector(last_ceiling_0_location_x, last_ceiling_0_location_y, last_ceiling_0_location_z), ceiling_rotation, paper_plane_spawn_parameters);
            ceiling_0_array[ceiling_0_row_number].inner_plane_array[ceiling_0_column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
        }
    }
    last_ceiling_0_location_x -= plane_size;
    last_ceiling_0_location_y -= plane_size;
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