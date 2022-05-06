// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_user_settings.h"
Ugame_user_settings::Ugame_user_settings() {
    UGameUserSettings* game_user_settings = const_cast<UGameUserSettings*>(GetDefault<UGameUserSettings>());
    if (game_user_settings) {
        game_user_settings->SetScreenResolution(game_user_settings->GetDesktopResolution());
        game_user_settings->SetFullscreenMode(EWindowMode::Fullscreen);
        game_user_settings->SetDynamicResolutionEnabled(true);
        game_user_settings->SetVSyncEnabled(true);
        game_user_settings->SetAntiAliasingQuality(0);
        game_user_settings->SaveSettings();
    }
}
