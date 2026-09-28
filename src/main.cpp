#include "raylib.h"
#include "Player.h"
#include "Renderer.h"
#include "UI.h"
#include "algorithms/Algorithm.h"
#include <algorithm>
#include <random>

static std::vector<int> randomArray(int n, int maxValue) {
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(5, maxValue);
    std::vector<int> a(n);
    for (int& x : a) x = dist(rng);
    return a;
}

int main() {
    const int width = 1280, height = 720, count = 60, maxValue = 100;
    InitWindow(width, height, "AlgoViz");
    SetTargetFPS(60);

    const auto& algos = getAlgorithms();
    size_t algoIndex = 0;
    std::vector<int> data = randomArray(count, maxValue);

    Player player;
    player.load(algos[algoIndex].fn(data));

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) player.togglePlay();
        if (IsKeyPressed(KEY_RIGHT)) player.stepForward();
        if (IsKeyPressed(KEY_LEFT))  player.stepBack();
        if (IsKeyPressed(KEY_UP))    player.stepsPerSecond = std::min(player.stepsPerSecond * 1.5f, 1000.0f);
        if (IsKeyPressed(KEY_DOWN))  player.stepsPerSecond = std::max(player.stepsPerSecond / 1.5f, 1.0f);
        if (IsKeyPressed(KEY_R)) {
            data = randomArray(count, maxValue);
            player.load(algos[algoIndex].fn(data));
        }
        if (IsKeyPressed(KEY_TAB)) {
            algoIndex = (algoIndex + 1) % algos.size();
            player.load(algos[algoIndex].fn(data));
        }

        player.update(GetFrameTime());

        BeginDrawing();
        ClearBackground({18, 18, 24, 255});
        drawUI(player, algos[algoIndex].name, algos[algoIndex].bigO);
        drawBars(player.current(), {20, 90, (float)width - 40, (float)height - 140}, maxValue);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}