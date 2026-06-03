#include "BossBlindState.h"
#include "RunSessionState.h"
#include <iostream>

std::string BossBlindState::getName() { return "Boss Blind"; }
int BossBlindState::getTargetScore() { return 600; }

// --- IMPLEMENTASI REWARD ---
int BossBlindState::getRewardMoney() { return 5; }

void BossBlindState::handlePlay(RunSessionState& state) {
    std::cout << "\n[PLAY] Memasuki arena Boss Blind!\n";
}

void BossBlindState::handleSkip(RunSessionState& state) {
    std::cout << "\n[SKIP] GAGAL: Boss Blind tidak bisa dilewati begitu saja!\n";
}