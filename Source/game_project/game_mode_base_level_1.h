// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GameFramework/HUD.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInterface.h"
#include "plane_struct_field.h"

#include "game_mode_base_level_1.generated.h"

class Astatic_mesh_plane;
UENUM()
enum direction
{
	front, right, back, left,
};
UCLASS()
class GAME_PROJECT_API Agame_mode_base_level_1 : public AGameModeBase
{
	GENERATED_BODY()
public:
	Agame_mode_base_level_1();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;
	UPROPERTY() UWorld* world;
	UPROPERTY() Astatic_mesh_plane* temp_static_mesh_plane;
	UPROPERTY() TArray<Fplane_struct> box_0_array;
	UPROPERTY() TArray<Fplane_struct> stair_0_array;
	UPROPERTY() TSubclassOf<Astatic_mesh_plane> static_mesh_plane_class;
	UPROPERTY() UMaterialInterface* material_asset;
	UPROPERTY() UMaterialInterface* material_asset_2;
	UPROPERTY() UMaterialInterface* material_asset_3;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_class_base;
	UPROPERTY() float plane_size;
	UPROPERTY() int32 box_0_x = 50;
	UPROPERTY() int32 box_0_y = 50;
	UPROPERTY() int32 box_0_z = 30;
	UPROPERTY() int32 stair_0_x = 8;
	UPROPERTY() int32 stair_0_y = 5;
	UPROPERTY() int32 stair_0_z = stair_0_x;
	UPROPERTY() FVector initial_plane_0_location = FVector(0.0f);
	UPROPERTY() FVector initial_stair_0_location = FVector(0.0f);
	UPROPERTY() FRotator floor_rotation = FRotator(0.0f);
	UPROPERTY() FRotator ceiling_rotation = FRotator(180.0f, 0.0f, 0.0f);
	UPROPERTY() FRotator wall_left_rotation = FRotator(0.0f, 0.0f, 90.0f);
	UPROPERTY() FRotator wall_right_rotation = FRotator(0.0f, 180.0f, 90.0f);
	UPROPERTY() FRotator wall_back_rotation = FRotator(0.0f, 270.0f, 90.0f);
	UPROPERTY() FRotator wall_front_rotation = FRotator(0.0f, 90.0f, 90.0f);
	UPROPERTY() FVector stair_scale = FVector(1.0f, 0.25f, 1.0f);
	UFUNCTION() void set_num(TArray<Fplane_struct>& box_array, int32 face_count, int32 x, int32 y, int32 z);
	UFUNCTION() void spawn_box(TArray<Fplane_struct>& box_array, FVector initial_location, float distance, int32 x, int32 y, int32 z, bool inside);
	UFUNCTION() void spawn_stair(TArray<Fplane_struct>& stair_array, FVector initial_location, float distance, int32 x, int32 y, int32 z, FVector scale, TEnumAsByte<direction> stair_direction);

};
