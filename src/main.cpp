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
    auto reload = [&]() { player.load(algos[algoIndex].fn(data)); };
    reload();

    while (!WindowShouldClose()) {
        player.update(GetFrameTime());

        BeginDrawing();
        ClearBackground({18, 18, 24, 255});
        drawBars(player.current(), {20, 140, (float)width - 40, (float)height - 200}, maxValue);
        UIActions ui = drawUI(player, algos, algoIndex);
        EndDrawing();

        // Handle input (mouse buttons OR keyboard)
        if (ui.togglePlay  || IsKeyPressed(KEY_SPACE)) player.togglePlay();
        if (ui.stepForward || IsKeyPressed(KEY_RIGHT)) player.stepForward();
        if (ui.stepBack    || IsKeyPressed(KEY_LEFT))  player.stepBack();
        if (ui.faster      || IsKeyPressed(KEY_UP))    player.stepsPerSecond = std::min(player.stepsPerSecond * 1.5f, 1000.0f);
        if (ui.slower      || IsKeyPressed(KEY_DOWN))  player.stepsPerSecond = std::max(player.stepsPerSecond / 1.5f, 1.0f);
        if (ui.shuffle     || IsKeyPressed(KEY_R)) {
            data = randomArray(count, maxValue);
            reload();
        }
        if (IsKeyPressed(KEY_TAB)) {
            algoIndex = (algoIndex + 1) % algos.size();
            reload();
        }
        if (ui.selectAlgo >= 0 && (size_t)ui.selectAlgo != algoIndex) {
            algoIndex = (size_t)ui.selectAlgo;
            reload();
        }
    }

    CloseWindow();
    return 0;
}