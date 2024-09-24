//
// Created by CLV_wp on 14/09/2024.
//

#include "TCRA.hpp"

TCRA::TCRA() {
    config.load(config.filename);
    InitWindow(960,540,"Alpha DevBuild");
    SetTargetFPS(config.getInt("window","fps"));
    SetWindowSize(config.getInt("window","width"), config.getInt("window","height")); // ADAPTE A L'ECRAN
    if(config.getBool("graphics","fullscreen"))
    {
        SetWindowPosition(0,0);
        ToggleFullscreen();
    }
    //showLoadingScreen();
    //EnableEventWaiting();
    stateStack.push(std::make_unique<MainMenuState>(stateStack,config));
}

TCRA::~TCRA() {
    CloseWindow();
}

void TCRA::run() {
    config.affichage_config();

    if (IsWindowMinimized())
    {
        WaitTime(0.1);
    }
    else{
        while (!stateStack.empty()) {
            stateStack.run();
        }
    }
}
