// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "GameFramework/GameModeBase.h"

#include "game_instance.generated.h"

/**
 * 
 */
UCLASS()
class GAME_PROJECT_API Ugame_instance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	Ugame_instance();
	virtual void Init() override;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_class_base;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_level_1_class;
};
