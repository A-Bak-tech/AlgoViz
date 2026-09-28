#include "Player.h"
#include <utility>

void Player::load(std::vector<Step> s) {
    steps = std::move(s);
    int comparisons = 0, swaps = 0;
    for (auto& st : steps) {
        if (st.cmpA != -1)  ++comparisons;
        if (st.swapA != -1) ++swaps;
        st.comparisons = comparisons;
        st.swaps = swaps;
    }
    index = 0;
    playing = false;
    timer = 0.0f;
}

void Player::update(float dt) {
    if (!playing || steps.empty()) return;
    timer += dt;
    const float interval = 1.0f / stepsPerSecond;
    while (timer >= interval) {
        timer -= interval;
        if (isDone()) { playing = false; timer = 0.0f; return; }
        ++index;
    }
}

void Player::togglePlay() {
    if (isDone()) index = 0;
    playing = !playing;
}

void Player::stepForward() { playing = false; if (!isDone()) ++index; }
void Player::stepBack()    { playing = false; if (index > 0) --index; }
void Player::reset()       { playing = false; index = 0; timer = 0.0f; }