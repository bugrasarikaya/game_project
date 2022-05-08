// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "static_mesh_plane.h"

Astatic_mesh_plane::Astatic_mesh_plane() {
	if (!static_mesh_asset_reference.IsEmpty()) {
		static_mesh_asset = LoadObject<UStaticMesh>(GetWorld(), *static_mesh_asset_reference);
		GetStaticMeshComponent()->SetStaticMesh(static_mesh_asset);
		GetStaticMeshComponent()->SetCastShadow(false);
	}
}
