#include "SmallBlindState.h"
#include "BigBlindState.h"     // Agar tahu mau pindah ke mana
#include "RewardCommand.h"     // Memanggil wujud hadiah
#include "RunSessionState.h"   // Memanggil wujud data
#include <iostream>

std::string SmallBlindState::getName() { return "Small Blind"; }
int SmallBlindState::getTargetScore() { return 300; }

void SmallBlindState::handlePlay(RunSessionState& state) {
    std::cout << "\n[PLAY] Memasuki arena Small Blind!\n";
}

void SmallBlindState::handleSkip(RunSessionState& state) {
    std::cout << "\n[SKIP] Anda melewati Small Blind. Tag 'Bonus Hand' disimpan!\n";
    
    // Memanggil BonusHandCommand dari file RewardCommand.h
    state.pendingCommands.push_back(std::make_unique<BonusHandCommand>());
    state.currentBlind = std::make_unique<BigBlindState>();
}