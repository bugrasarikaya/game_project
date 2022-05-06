// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GameFramework/HUD.h"
#include "Engine/Engine.h"

#include "game_mode_base_level_1.generated.h"

class Apaper_plane;

UCLASS()
class GAME_PROJECT_API Agame_mode_base_level_1 : public AGameModeBase
{
	GENERATED_BODY()
public:
	Agame_mode_base_level_1();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	UPROPERTY() TSubclassOf<Apaper_plane> paper_plane_class;
	UPROPERTY() UWorld* world;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_class_base;
};
