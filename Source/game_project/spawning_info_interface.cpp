// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "spawning_info_interface.h"

// Add default functionality here for any Ispawning_info_interface functions that are not pure virtual.
Ispawning_info_interface::Ispawning_info_interface() {
    TArray<FVector> location_info_array = { FVector(0.0f) };
    TArray<FRotator> rotation_info_array = { FRotator(0.0f) };
    check(location_info_array.Num() == rotation_info_array.Num());
   // FVector *plane_location_info_array = { FVector(0.0f), FVector(0.0f };

}