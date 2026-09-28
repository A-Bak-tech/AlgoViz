#include "Renderer.h"

void drawBars(const Step& s, Rectangle area, int maxValue) {
    const int n = static_cast<int>(s.array.size());
    if (n == 0) return;

    const float gap = 2.0f;
    const float w = (area.width - gap * (n - 1)) / n;

    for (int i = 0; i < n; ++i) {
        const float h = static_cast<float>(s.array[i]) / maxValue * area.height;

        Color c = {100, 149, 237, 255};                                         // default: blue
        if (i < (int)s.sorted.size() && s.sorted[i]) c = {80, 200, 120, 255};   // sorted: green
        if (i == s.cmpA || i == s.cmpB)              c = {250, 204, 21, 255};   // comparing: yellow
        if (i == s.swapA || i == s.swapB)            c = {239, 68, 68, 255};    // swapping: red

        DrawRectangleRec({area.x + i * (w + gap), area.y + area.height - h, w, h}, c);
    }
}