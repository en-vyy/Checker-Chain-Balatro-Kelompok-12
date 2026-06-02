#include "BossBlindState.h"
#include "RunSessionState.h"
#include <iostream>

std::string BossBlindState::getName() { return "Boss Blind"; }
int BossBlindState::getTargetScore() { return 1000; }

void BossBlindState::handlePlay(RunSessionState& state) {
    std::cout << "\n[BOSS BLIND] Memulai pertarungan Boss!\n";
}

void BossBlindState::handleSkip(RunSessionState& state) {
    // Boss Blind tidak boleh di-skip
    std::cout << "\n[!] Anda tidak bisa melakukan SKIP pada Boss Blind!\n";
}