#include "Player.h"
#include <utility>

void Player::load(std::vector<Step> s) {
    steps = std::move(s);
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