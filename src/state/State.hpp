#ifndef ALPHA_STATE_HPP
#define ALPHA_STATE_HPP

#include "raygui.h"
#include "../config/config.hpp"

class StateStack;

class State {
public:
    explicit State(StateStack& stack, Config& config) : stateStack(stack), config(config) {}
    virtual ~State() = default;
    virtual void run() = 0;

protected:
    StateStack& stateStack;
    Config& config;
private:

    virtual void handleInput() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
};


class StateStack {
    public:
        void push(std::unique_ptr<State> state) {
            stack.push(std::move(state));
        }
        void pop() {
            if (!stack.empty()) {
                stack.pop();
            }
        }
        void run() {
            if (!stack.empty()) {
                stack.top()->run();
            }
        }
        bool empty() const {
            return stack.empty();
        }

    private:
        std::stack<std::unique_ptr<State>> stack;
};

#endif //ALPHA_STATE_HPP
