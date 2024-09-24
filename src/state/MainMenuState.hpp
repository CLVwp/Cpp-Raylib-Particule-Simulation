#ifndef ALPHA_MAINMENUSTATE_HPP
#define ALPHA_MAINMENUSTATE_HPP

#include "State.hpp"
#include "particule_render_test.hpp"


class MainMenuState : public State {
public:
    MainMenuState(StateStack& stack,Config& config);
    ~MainMenuState();
    void run() override {
        if(!this->stateStack.empty())
        {
            this->update(GetFrameTime());
            this->render();
            this->handleInput();
        }
    }
private:
    int window_width;
    int window_height;
    void handleInput() override;
    void update(float dt) override;
    void render() override;
    bool btn_play=false;
    bool btn_option=false;
    bool btn_exit=false;
};



#endif //ALPHA_MAINMENUSTATE_HPP
