#pragma once
#include "BlindState.h"

class SmallBlindState : public BlindState {
public:
    std::string getName() override;
    int getTargetScore() override;
    int getRewardMoney() override; 
    void handlePlay(RunSessionState& state) override;
    void handleSkip(RunSessionState& state) override;
};