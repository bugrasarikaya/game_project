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
    material_asset_2 = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_inst_type_3_part_1.plane_material_inst_type_3_part_1"));
    material_asset_3 = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/test.test"));
    game_mode_class_base = LoadClass<AGameModeBase>(world, TEXT("/Script/game_project.game_projectGameModeBase"));
    //UE_LOG(LogTemp, Warning, TEXT("Constructor"));
}
void Agame_mode_base_level_1::BeginPlay() {
    FString current_level_name = world->GetMapName();
    current_level_name.RemoveFromStart(world->StreamingLevelsPrefix);
    FString new_level_name = "level_1";
    if (current_level_name != new_level_name) world->ServerTravel(new_level_name, false);
    FTransform local_to_world;
    temp_static_mesh_plane = GetWorld()->SpawnActor<Astatic_mesh_plane>();
    plane_size = ((temp_static_mesh_plane->GetStaticMeshComponent()->CalcBounds(local_to_world).BoxExtent).X) * 2; // plane_size = 10
    temp_static_mesh_plane->Destroy();
    set_num(box_0_array, 6, box_0_x, box_0_y, box_0_z);
    spawn_box(box_0_array, initial_plane_0_location, plane_size, box_0_x, box_0_y, box_0_z, true);
    set_num(stair_0_array, 6, stair_0_x, stair_0_y, stair_0_z);
    spawn_stair(stair_0_array, initial_stair_0_location, plane_size, stair_0_x, stair_0_y, stair_0_z, stair_scale, front);
 //   FActorSpawnParameters paper_plane_spawn_parameters;
	//paper_plane_spawn_parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}
void Agame_mode_base_level_1::Tick(float delta_time) {
    Super::Tick(delta_time);
}
void Agame_mode_base_level_1::EndPlay(EEndPlayReason::Type reason) {
    Super::EndPlay(reason);
    //UE_LOG(LogTemp, Warning, TEXT("LOL"));
    //for (int32 i = 0; i < 10; i++) delete lol[i];
    //delete lol;
}
void Agame_mode_base_level_1::set_num(TArray<Fplane_struct>& box_array, int32 face_count, int32 x, int32 y, int32 z) {
    box_array.SetNum(face_count);
    for (int32 face_number = 0; face_number < face_count; face_number++) {
        if (face_number < 2) {
            box_array[face_number].row.SetNum(x);
            for (int32 i = 0; i < x; i++) box_array[face_number].row[i].column.SetNum(y);
        }
        else if (face_number < 4) {
            box_array[face_number].row.SetNum(x);
            for (int32 i = 0; i < x; i++) box_array[face_number].row[i].column.SetNum(z);
        }
        else if (face_number < 6) {
            box_array[face_number].row.SetNum(y);
            for (int32 i = 0; i < y; i++) box_array[face_number].row[i].column.SetNum(z);
        }
    }
}
void Agame_mode_base_level_1::spawn_box(TArray<Fplane_struct>& box_array, FVector initial_location, float distance, int32 x, int32 y, int32 z, bool inside) {
    FVector location, temp_location;
    for (int32 face_number = 0; face_number < 6; face_number++) {
        if (face_number == 0) {
            location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
            temp_location.Y = location.Y;
            for (int32 row_number = 0; row_number < x; row_number++, location.X += distance) {
                location.Y = temp_location.Y;
                for (int32 column_number = 0; column_number < y; column_number++, location.Y += distance) {
                    box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? floor_rotation : ceiling_rotation);
                    if(box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                }
            }
        }
        else if (face_number == 1) {
            location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (z * distance));
            temp_location.Y = location.Y;
            for (int32 row_number = 0; row_number < x; row_number++, location.X += distance) {
                location.Y = temp_location.Y;
                for (int32 column_number = 0; column_number < y; column_number++, location.Y += distance) {
                    box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? ceiling_rotation : floor_rotation);
                    if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                }
            }
        }
        else if (face_number == 2) {
            location = FVector(initial_location.X, initial_location.Y - (distance / 2), initial_location.Z + (distance / 2));
            temp_location.Z = location.Z;
            for (int32 row_number = 0; row_number < x; row_number++, location.X += distance) {
                location.Z = temp_location.Z;
                for (int32 column_number = 0; column_number < z; column_number++, location.Z += distance) {
                    box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_left_rotation : wall_right_rotation);
                    if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                }
            }
        }
        else if (face_number == 3) {
            location = FVector(initial_location.X, initial_location.Y - (distance / 2) + (y * distance), initial_location.Z + (distance / 2));
            temp_location.Z = location.Z;
            for (int32 row_number = 0; row_number < x; row_number++, location.X += distance) {
                location.Z = temp_location.Z;
                for (int32 column_number = 0; column_number < z; column_number++, location.Z += distance) {
                    box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_right_rotation : wall_left_rotation);
                    if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                }
            }
        }
        else if (face_number == 4) {
            location = FVector(initial_location.X - (distance / 2), initial_location.Y, initial_location.Z + (distance / 2));
            temp_location.Z = location.Z;
            for (int32 row_number = 0; row_number < y; row_number++, location.Y += distance) {
                location.Z = temp_location.Z;
                for (int32 column_number = 0; column_number < z; column_number++, location.Z += distance) {
                    box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_back_rotation: wall_front_rotation);
                    if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                }
            }
        }
        else if (face_number == 5) {
            location = FVector(initial_location.X - (distance / 2) + (x * distance), initial_location.Y, initial_location.Z + (distance / 2));
            temp_location.Z = location.Z;
            for (int32 row_number = 0; row_number < y; row_number++, location.Y += distance) {
                location.Z = temp_location.Z;
                for (int32 column_number = 0; column_number < z; column_number++, location.Z += distance) {
                    box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_front_rotation : wall_back_rotation);
                    if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                }
            }
        }
    }
}
void Agame_mode_base_level_1::spawn_stair(TArray<Fplane_struct>& stair_array, FVector initial_location, float distance, int32 x, int32 y, int32 z, FVector scale, TEnumAsByte<direction> stair_direction) {
    FVector location, temp_location;
    if (stair_direction == front) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < x; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                    location.Z += (distance / 4);
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < x; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                    location.Z += (distance / 4);
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2), initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < x; row_number++, location.X += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2) + (y * distance), initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < x; row_number++, location.X += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X - (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < z; column_number++, location.X += distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < z; column_number++, location.X += distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
        }
    }
    else if (stair_direction == right) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                        location.Z += (distance / 4);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                        location.Z += (distance / 4);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2), initial_location.Z + ((distance / 4) / 2));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < z; column_number++, location.Y += distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2) + distance, initial_location.Z + ((distance / 4) / 2));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < z; column_number++, location.Y += distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < y; row_number++, location.Y += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2) - (x * distance), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < y; row_number++, location.Y += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
        }
    }
    else if (stair_direction == back) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                    location.Z += (distance / 4);
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                    location.Z += (distance / 4);
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2), initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2) + (y * distance), initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X - (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < z; column_number++, location.X -= distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < z; column_number++, location.X -= distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
        }
    }
    else if (stair_direction == left) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < y; column_number++, location.Y -= distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                        location.Z += (distance / 4);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < y; column_number++, location.Y -= distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                        location.Z += (distance / 4);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y + (distance / 2), initial_location.Z + ((distance / 4) / 2));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < z; column_number++, location.Y -= distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y + (distance / 2) - distance, initial_location.Z + ((distance / 4) / 2));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < x; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < z; column_number++, location.Y -= distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < y; row_number++, location.Y -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2) - (x * distance), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < y; row_number++, location.Y -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
        }
    }
}