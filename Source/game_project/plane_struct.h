// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "plane_struct.generated.h"

class Astatic_mesh_plane;

UCLASS()
class GAME_PROJECT_API Uplane_struct : public UUserDefinedStruct
{
	GENERATED_BODY()
	
};
USTRUCT()
struct FFplane_struct
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY() TArray<Astatic_mesh_plane*> inner_plane_array;
};