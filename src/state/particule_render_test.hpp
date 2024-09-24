#ifndef BETA_PARTICULE_RENDER_TEST_HPP
#define BETA_PARTICULE_RENDER_TEST_HPP

#include "State.hpp"
#include <vector>

struct Particule {
    Vector2 position;
    Vector2 velocity;
    Color color;
};

class particule_render_test : public State {
public:
    particule_render_test(StateStack& stack, Config& config);

    void run() override {
        if (!this->stateStack.empty()) {
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

    Particule GenerateRandomParticle();

    int ZONE_COUNT_X = 4;
    int ZONE_COUNT_Y = 3;
    int NUM_THREADS = ZONE_COUNT_X * ZONE_COUNT_Y;

    int ParticuleCount;
    std::vector<Particule> particles;
    int zone_width;
    int zone_height;
    bool useThreads;
};

#endif // BETA_PARTICULE_RENDER_TEST_HPP
