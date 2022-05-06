// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "paper_plane.h"

Apaper_plane::Apaper_plane() {
	sprite_component = GetRenderComponent();
	sprite_component->SetupAttachment(RootComponent);
	//if (!sprite_asset_reference.IsEmpty()) {
	//	sprite_asset = LoadObject<UPaperSprite>(GetWorld(), *sprite_asset_reference);
	//	sprite_component->SetSprite(sprite_asset);
	//}
	//sprite_component->SetRelativeLocation(FVector(location_x, location_y, location_z));
	//sprite_component->SetRelativeRotation(FRotator(rotation_pitch, rotation_yaw, rotation_roll));
	//sprite_component->SetRelativeScale3D(FVector(scale));
}
void Apaper_plane::load_sprite(FString new_sprite_asset_reference) {
	sprite_component->SetSprite(LoadObject<UPaperSprite>(GetWorld(), *new_sprite_asset_reference));
}