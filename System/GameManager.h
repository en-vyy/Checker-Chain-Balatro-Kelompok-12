#pragma once

#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"
#include "RunSessionState.h"
#include "BlindState.h"
#include "RewardCommand.h"

// --- TAMBAHAN UNTUK SISTEM MODIFIER & SHOP ---
#include "ModifierManager.h"
#include "ShopManager.h" // <--- INI YANG HILANG SEBELUMNYA

class GameManager {
public:
    GameManager(); 
    void runSession(); 
    ModifierManager& getModifierManager() { return modifierManager; }

private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    RunSessionState sessionState; 
    
    ModifierManager modifierManager; 
    ShopManager shopManager; // <--- DAN INI JUGA HILANG SEBELUMNYA
};