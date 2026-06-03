#pragma once
#include <vector>
#include <memory>

class BlindState;      
class RewardCommand;   

struct RunSessionState {
    int ante = 1;
    int totalScore = 0;
    int remainingPlays = 4;       
    int remainingDiscards = 3;    
    int money = 4;
    
    // --- VARIABEL TRACKER TAG BARU ---
    int totalPlayedHands = 0;       // Untuk Handy Tag
    bool hasInvestmentTag = false;  // Untuk Investment Tag

    std::unique_ptr<BlindState> currentBlind;
    std::vector<std::unique_ptr<RewardCommand>> pendingCommands;
};