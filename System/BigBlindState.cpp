#include "BigBlindState.h"
#include "BossBlindState.h"
#include "RewardCommand.h"
#include "RunSessionState.h"
#include <iostream>

std::string BigBlindState::getName() { return "Big Blind"; }
int BigBlindState::getTargetScore() { return 450; }

// --- IMPLEMENTASI REWARD ---
int BigBlindState::getRewardMoney() { return 4; }

void BigBlindState::handlePlay(RunSessionState& state) {
    std::cout << "\n[PLAY] Memasuki arena Big Blind!\n";
}

void BigBlindState::handleSkip(RunSessionState& state) {
    std::cout << "\n[SKIP] Anda melewati Big Blind. Mengambil Handy Tag!\n";
    state.pendingCommands.push_back(std::make_unique<HandyTagCommand>());
    state.currentBlind = std::make_unique<BossBlindState>();
}