//
// Created by CLV_wp on 14/09/2024.
//

#ifndef TEMPLATE_CCP_RAYLIB_APP_TCRA_HPP
#define TEMPLATE_CCP_RAYLIB_APP_TCRA_HPP

#include "state/MainMenuState.hpp"

class TCRA {
public:
    TCRA();
    ~TCRA();

    void run();

private:
    Config config;
    StateStack stateStack;

};


#endif //TEMPLATE_CCP_RAYLIB_APP_TCRA_HPP
