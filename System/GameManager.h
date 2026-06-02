#pragma once

#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"
#include "RunSessionState.h"
#include "BlindState.h"
#include "RewardCommand.h"

// --- TAMBAHAN UNTUK SISTEM MODIFIER ---
#include "ModifierManager.h"

class GameManager {
public:
    GameManager(); // Konstruktor untuk setup awal Joker
    void runSession(); 
    ModifierManager& getModifierManager() { return modifierManager; }

private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    RunSessionState sessionState; 
    
    ModifierManager modifierManager; // Inisialisasi Manager
};