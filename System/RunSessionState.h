#pragma once
#include <vector>
#include <memory>

class BlindState;      // Forward declaration
class RewardCommand;   // <--- Ini wajib ada agar error "not declared in this scope" hilang

struct RunSessionState {
    int ante = 1;
    int totalScore = 0;
    int remainingPlays = 4;       
    int remainingDiscards = 3;    
    int freeRerolls = 0;

    std::unique_ptr<BlindState> currentBlind;
    std::vector<std::unique_ptr<RewardCommand>> pendingCommands;
};