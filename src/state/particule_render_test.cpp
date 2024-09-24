#include "particule_render_test.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <thread>
#include <vector>



particule_render_test::particule_render_test(StateStack& stack, Config& config)
        : State(stack, config), ParticuleCount(100000), useThreads(true) {
    this->window_width = config.getInt("window", "width");
    this->window_height = config.getInt("window", "height");

    zone_width = window_width / ZONE_COUNT_X;
    zone_height = window_height / ZONE_COUNT_Y;

    particles.reserve(ParticuleCount);
    for (int i = 0; i < ParticuleCount; ++i) {
        particles.push_back(GenerateRandomParticle());
    }
}

void UpdateParticles(std::vector<Particule>& particles, int startIndex, int endIndex, Vector2 mousePosition, float dt) {
    const float maxDistance = 1920.0f;
    const float maxSpeed = 4.0f;
    const float proximityThreshold = 2.0f;

    for (int i = startIndex; i < endIndex; ++i) {
        auto& particle = particles[i];
        Vector2 direction = Vector2Subtract(mousePosition, particle.position);
        float distance = Vector2Length(direction);

        if (distance > 0) {
            float attractionStrength = 0.1f * (1.0f - (distance / maxDistance));
            direction = Vector2Scale(Vector2Normalize(direction), fmaxf(attractionStrength, 0));
            particle.velocity = Vector2Add(particle.velocity, direction);
        }

        if (Vector2Length(particle.velocity) > maxSpeed) {
            particle.velocity = Vector2Scale(Vector2Normalize(particle.velocity), maxSpeed);
        }

        particle.position = Vector2Add(particle.position, Vector2Scale(particle.velocity, dt * 100));

        if (distance < proximityThreshold) {
            particle.velocity = {0, 0};
            particle.position = mousePosition;
        }

        if (particle.position.x < 0) particle.position.x = 1920;
        if (particle.position.x > 1920) particle.position.x = 0;
        if (particle.position.y < 0) particle.position.y = 1080;
        if (particle.position.y > 1080) particle.position.y = 0;
    }
}

Particule particule_render_test::GenerateRandomParticle() {
    Particule p;
    p.position = {(float)GetRandomValue(0, window_width), (float)GetRandomValue(0, window_height)};
    p.velocity = {(float)GetRandomValue(-100, 100) / 100.0f, (float)GetRandomValue(-100, 100) / 100.0f};
    p.color = {static_cast<unsigned char>(GetRandomValue(0, 255)),
               static_cast<unsigned char>(GetRandomValue(0, 255)),
               static_cast<unsigned char>(GetRandomValue(0, 255)),
               255};
    return p;
}

void particule_render_test::handleInput() {
    if (WindowShouldClose()) {
        stateStack.pop();
    }

    if (IsKeyDown(KEY_A) && ParticuleCount > 0) {
        int removeCount = std::min(100, ParticuleCount);
        ParticuleCount -= removeCount;
        particles.resize(ParticuleCount);
    }
    else if (IsKeyDown(KEY_D)) {
        int addCount = 100;
        ParticuleCount += addCount;
        for (int i = 0; i < addCount; ++i) {
            particles.push_back(GenerateRandomParticle());
        }
    }
    else if (IsKeyPressed(KEY_W)) {
        useThreads = !useThreads;
    }
    else if (IsKeyPressed(KEY_Z)){
        ZONE_COUNT_X++;
        NUM_THREADS = ZONE_COUNT_X * ZONE_COUNT_Y;
        zone_width = window_width / ZONE_COUNT_X;
        zone_height = window_height / ZONE_COUNT_Y;
    }
    else if (IsKeyPressed(KEY_X) && ZONE_COUNT_X > 1){
        ZONE_COUNT_X--;
        NUM_THREADS = ZONE_COUNT_X * ZONE_COUNT_Y;
        zone_width = window_width / ZONE_COUNT_X;
        zone_height = window_height / ZONE_COUNT_Y;
    }
    else if (IsKeyPressed(KEY_C)){
        ZONE_COUNT_Y++;
        NUM_THREADS = ZONE_COUNT_X * ZONE_COUNT_Y;
        zone_width = window_width / ZONE_COUNT_X;
        zone_height = window_height / ZONE_COUNT_Y;
    }
    else if (IsKeyPressed(KEY_V) && ZONE_COUNT_Y > 1){
        ZONE_COUNT_Y--;
        NUM_THREADS = ZONE_COUNT_X * ZONE_COUNT_Y;
        zone_width = window_width / ZONE_COUNT_X;
        zone_height = window_height / ZONE_COUNT_Y;
    }
}

void particule_render_test::update(float dt) {
    Vector2 mousePosition = GetMousePosition();
    int numParticles = particles.size();
    int chunkSize = (numParticles + NUM_THREADS - 1) / NUM_THREADS;
    std::vector<std::thread> threads;

    if (useThreads) {
        for (int i = 0; i < NUM_THREADS; ++i) {
            int startIndex = i * chunkSize;
            int endIndex = (i == NUM_THREADS - 1) ? numParticles : (i + 1) * chunkSize;
            threads.emplace_back(UpdateParticles, std::ref(particles), startIndex, endIndex, mousePosition, dt);
        }
        for (auto& t : threads) {
            t.join();
        }
    } else {
        UpdateParticles(particles, 0, numParticles, mousePosition, dt);
    }
}

void particule_render_test::render() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (int x = 0; x < ZONE_COUNT_X; ++x) {
        for (int y = 0; y < ZONE_COUNT_Y; ++y) {
            Rectangle zone = {(float)(x * zone_width), (float)(y * zone_height), (float)zone_width, (float)zone_height};
            DrawRectangleLinesEx(zone, 2, GRAY);
        }
    }

    DrawRectangleLinesEx((Rectangle){0, 0, (float)window_width, (float)window_height}, 4, RED);
    int textSize = 40;
    int textWidth = MeasureText("Beta devbuild", textSize);
    DrawText("Beta devbuild", (window_width - textWidth) / 2, 10, textSize, DARKGRAY);
    DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, DARKGRAY);
    DrawText(TextFormat("Particles: %i", ParticuleCount), 10, 40, 20, DARKGRAY);
    DrawText(TextFormat("Multi-threading: %s", useThreads ? "ON" : "OFF"), 10, 70, 20, DARKGRAY);
    DrawText("Q: Remove particle", 10, 100, 20, DARKGRAY);
    DrawText("D: Add particle", 10, 130, 20, DARKGRAY);
    DrawText("W: Toggle multi-threading", 10, 160, 20, DARKGRAY);
    DrawText("Z: ZONE_COUNT_X ++", 10, 190, 20, DARKGRAY);
    DrawText("X: ZONE_COUNT_X --", 10, 220, 20, DARKGRAY);
    DrawText("C: ZONE_COUNT_Y ++", 10, 250, 20, DARKGRAY);
    DrawText("V: ZONE_COUNT_Y --", 10, 280, 20, DARKGRAY);
    DrawText(TextFormat("ZONE_COUNT_X: %i", ZONE_COUNT_X), 10, 310, 20, DARKGRAY);
    DrawText(TextFormat("ZONE_COUNT_Y: %i", ZONE_COUNT_Y), 10, 340, 20, DARKGRAY);

    for (const auto& particle : particles) {
        DrawPixelV(particle.position, particle.color);
    }

    EndDrawing();
}
