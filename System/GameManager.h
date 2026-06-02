#pragma once

#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"

// --- TAMBAHKAN 3 BARIS INI ---
#include "RunSessionState.h"
#include "BlindState.h"
#include "RewardCommand.h"

class GameManager {
public:
    void runSession(); 

private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    
    // --- INI YANG PALING PENTING DAN KETINGGALAN ---
    RunSessionState sessionState; 
};