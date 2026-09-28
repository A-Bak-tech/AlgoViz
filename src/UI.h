#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include "algorithms/Algorithm.h"

struct UIActions {
    bool togglePlay  = false;
    bool stepBack    = false;
    bool stepForward = false;
    bool slower      = false;
    bool faster      = false;
    bool shuffle     = false;
    int  selectAlgo  = -1;
};

UIActions drawUI(const Player& p, const std::vector<AlgorithmInfo>& algos, size_t current);