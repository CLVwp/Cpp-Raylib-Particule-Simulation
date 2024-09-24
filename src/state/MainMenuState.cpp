#include "MainMenuState.hpp"

MainMenuState::MainMenuState(StateStack &stack, Config &config)
: State(stack, config)
{

    this->window_width = config.getInt("window","width");
    this->window_height = config.getInt("window","height");

}

MainMenuState::~MainMenuState() {

}

void MainMenuState::handleInput() {
    if (WindowShouldClose()) {
        stateStack.pop();
    }
    if(btn_play){
        //stateStack.push(std::make_unique<PlayState>(stateStack, config));
    }
    else if(btn_option){
        //stateStack.push(std::make_unique<OptionsMenuState>(stateStack, config));
    }
    else if(btn_exit){
        stateStack.pop();
    }
}

void MainMenuState::update(float dt) {

}

void MainMenuState::render() {

    BeginDrawing();
    ClearBackground(RAYWHITE);

    btn_play = GuiButton((Rectangle){1920/6,1080/5,240,48},"PLAY");
    btn_option = GuiButton((Rectangle){1920/6,1080/5+ 96,240,48},"SETTINGS");
    btn_exit = GuiButton((Rectangle){1920/6,1080/5+ 96+ 96,240,48},"EXIT");


    DrawRectangleLinesEx((Rectangle) { 0, 0, (float)window_width, (float)window_height },
                         4, RED);
    int textSize = 40;
    int textWidth = MeasureText("ALPHA devbuild", textSize);

    DrawText("TCRA v1", (window_width - textWidth) / 2, 10, textSize, DARKGRAY);
    DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, DARKGRAY);

    EndDrawing();
}


