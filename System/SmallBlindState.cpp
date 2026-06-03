#include "SmallBlindState.h"
#include "BigBlindState.h"
#include "RewardCommand.h"
#include "RunSessionState.h"
#include <iostream>

std::string SmallBlindState::getName() { return "Small Blind"; }
int SmallBlindState::getTargetScore() { return 300; }

// --- IMPLEMENTASI REWARD ---
int SmallBlindState::getRewardMoney() { return 3; }

void SmallBlindState::handlePlay(RunSessionState& state) {
    std::cout << "\n[PLAY] Memasuki arena Small Blind!\n";
}

void SmallBlindState::handleSkip(RunSessionState& state) {
    std::cout << "\n[SKIP] Anda melewati Small Blind. Mengambil Investment Tag!\n";
    state.pendingCommands.push_back(std::make_unique<InvestmentTagCommand>());
    state.currentBlind = std::make_unique<BigBlindState>();
}