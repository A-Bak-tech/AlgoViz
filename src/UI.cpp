#include "UI.h"
#include "raylib.h"

void drawUI(const Player& p, const std::string& name, const std::string& bigO) {
    DrawText(TextFormat("%s  |  %s", name.c_str(), bigO.c_str()), 20, 15, 24, RAYWHITE);
    DrawText(TextFormat("Step %d / %d    Speed: %.0f steps/s    %s",
                        (int)p.position() + 1, (int)p.total(), p.stepsPerSecond,
                        p.isPlaying() ? "Playing" : "Paused"),
             20, 45, 18, LIGHTGRAY);
    DrawText(TextFormat("Comparisons: %d    Swaps/Writes: %d",
                        p.current().comparisons, p.current().swaps),
             20, 68, 18, {250, 204, 21, 255});
    DrawText("SPACE play/pause   LEFT/RIGHT step   UP/DOWN speed   R shuffle   TAB next algorithm",
             20, GetScreenHeight() - 30, 16, GRAY);
}