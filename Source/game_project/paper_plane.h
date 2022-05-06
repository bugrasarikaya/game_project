// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

#include "paper_plane.generated.h"

/**
 * 
 */
UCLASS()
class GAME_PROJECT_API Apaper_plane : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	Apaper_plane();
	UPROPERTY() UPaperSpriteComponent* sprite_component;
	//UPROPERTY() UPaperSprite* sprite_asset;
	UPROPERTY() FString sprite_asset_reference;
private:
	//UPROPERTY() float location_x;
	//UPROPERTY() float location_y;
	//UPROPERTY() float location_z;
	//UPROPERTY() float rotation_pitch;
	//UPROPERTY() float rotation_yaw;
	//UPROPERTY() float rotation_roll;
	//UPROPERTY() float scale;
public:
	//FORCEINLINE float get_location_x() { return location_x; }
	//FORCEINLINE float get_location_y() { return location_y; }
	//FORCEINLINE float get_location_z() { return location_z; }
	//FORCEINLINE float get_rotation_pitch() { return rotation_pitch; }
	//FORCEINLINE float get_rotation_yaw() { return rotation_yaw; }
	//FORCEINLINE float get_rotation_roll() { return rotation_roll; }
	//FORCEINLINE float get_scale() { return scale; }
	//FORCEINLINE float set_location_x(float new_location_x) { location_x = new_location_x; }
	//FORCEINLINE float set_location_y(float new_location_y) { location_y = new_location_y; }
	//FORCEINLINE float set_location_z(float new_location_z) { location_z = new_location_z; }
	//FORCEINLINE float set_rotation_pitch(float new_rotation_pitch) { rotation_pitch = new_rotation_pitch; }
	//FORCEINLINE float set_rotation_yaw(float new_rotation_yaw) { rotation_yaw = new_rotation_yaw; }
	//FORCEINLINE float set_rotation_roll(float new_rotation_roll) { rotation_roll = new_rotation_roll; }
	//FORCEINLINE float set_scale(float new_scale) { scale = new_scale; }
	UFUNCTION() void load_sprite(FString new_sprite_asset_reference);
};
