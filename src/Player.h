#pragma once
#include <vector>
#include "Step.h"

class Player {
public:
    void load(std::vector<Step> s);
    void update(float dt);
    void togglePlay();
    void stepForward();
    void stepBack();
    void reset();

    const Step& current() const { return steps[index]; }
    bool isPlaying() const { return playing; }
    bool isDone() const { return index + 1 >= steps.size(); }
    size_t position() const { return index; }
    size_t total() const { return steps.size(); }

    float stepsPerSecond = 30.0f;

private:
    std::vector<Step> steps;
    size_t index = 0;
    bool playing = false;
    float timer = 0.0f;
};