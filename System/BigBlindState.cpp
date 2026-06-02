#include "BigBlindState.h"
#include "BossBlindState.h"
#include "RewardCommand.h"     // <--- Ini yang diubah
#include "RunSessionState.h"
#include <iostream>

std::string BigBlindState::getName() { return "Big Blind"; }
int BigBlindState::getTargetScore() { return 600; }

void BigBlindState::handlePlay(RunSessionState& state) {
    std::cout << "\n[PLAY] Memasuki arena Big Blind!\n";
}

void BigBlindState::handleSkip(RunSessionState& state) {
    std::cout << "\n[SKIP] Anda melewati Big Blind. Tag 'Free Reroll' disimpan!\n";
    
    // <--- Nama kelasnya juga disesuaikan menjadi FreeRerollCommand
    state.pendingCommands.push_back(std::make_unique<FreeRerollCommand>());
    state.currentBlind = std::make_unique<BossBlindState>();
}