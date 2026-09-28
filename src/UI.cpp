#include "UI.h"
#include "raylib.h"

static bool button(Rectangle r, const char* label, bool active = false) {
    const bool hover = CheckCollisionPointRec(GetMousePosition(), r);
    const Color bg = active ? Color{100, 149, 237, 255}
                   : hover  ? Color{60, 60, 75, 255}
                            : Color{40, 40, 52, 255};
    DrawRectangleRounded(r, 0.25f, 6, bg);

    const int fontSize = 18;
    const int textW = MeasureText(label, fontSize);
    DrawText(label, (int)(r.x + (r.width - textW) / 2), (int)(r.y + (r.height - fontSize) / 2),
             fontSize, RAYWHITE);

    return hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}

UIActions drawUI(const Player& p, const std::vector<AlgorithmInfo>& algos, size_t current) {
    UIActions a;
    const auto& info = algos[current];

    // Header
    DrawText(TextFormat("%s  |  %s", info.name.c_str(), info.bigO.c_str()), 20, 15, 24, RAYWHITE);
    DrawText(TextFormat("Step %d / %d    Speed: %.0f steps/s    %s",
                        (int)p.position() + 1, (int)p.total(), p.stepsPerSecond,
                        p.isPlaying() ? "Playing" : "Paused"),
             20, 45, 18, LIGHTGRAY);
    DrawText(TextFormat("Comparisons: %d    Swaps/Writes: %d",
                        p.current().comparisons, p.current().swaps),
             20, 68, 18, {250, 204, 21, 255});

    // Algorithm picker
    float x = 20;
    for (size_t i = 0; i < algos.size(); ++i) {
        if (button({x, 95, 170, 30}, algos[i].name.c_str(), i == current)) a.selectAlgo = (int)i;
        x += 180;
    }

    // Playback controls
    const float y = (float)GetScreenHeight() - 50;
    const float w = 110, h = 34, gap = 10;
    x = 20;
    if (button({x, y, w, h}, "<< Step"))                                  a.stepBack = true;    x += w + gap;
    if (button({x, y, w, h}, p.isPlaying() ? "Pause" : "Play", p.isPlaying())) a.togglePlay = true; x += w + gap;
    if (button({x, y, w, h}, "Step >>"))                                  a.stepForward = true; x += w + gap;
    if (button({x, y, w, h}, "Slower"))                                   a.slower = true;      x += w + gap;
    if (button({x, y, w, h}, "Faster"))                                   a.faster = true;      x += w + gap;
    if (button({x, y, w, h}, "Shuffle"))                                  a.shuffle = true;     x += w + gap;

    DrawText("Keys: SPACE  LEFT/RIGHT  UP/DOWN  R  TAB", (int)x + 10, (int)y + 9, 16, GRAY);
    return a;
}