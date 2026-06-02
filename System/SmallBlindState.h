#pragma once
#include "BlindState.h"

class SmallBlindState : public BlindState {
public:
    std::string getName() override;
    int getTargetScore() override;
    void handlePlay(RunSessionState& state) override;
    void handleSkip(RunSessionState& state) override;
};