#pragma once
#include "RunSessionState.h" // <--- Ini wajib ada agar error "incomplete type" hilang
#include <iostream>

// KELAS INDUK
class RewardCommand {
public:
    virtual ~RewardCommand() = default; 
    virtual void execute(RunSessionState& state) = 0;
};

// ANAK 1
class BonusHandCommand : public RewardCommand {
public:
    void execute(RunSessionState& state) override {
        state.remainingPlays += 1;
        std::cout << "[REWARD EXECUTED] Anda mendapatkan +1 Kesempatan Play!\n";
    }
};

// ANAK 2
class FreeRerollCommand : public RewardCommand {
public:
    void execute(RunSessionState& state) override {
        state.freeRerolls += 1;
        std::cout << "[REWARD EXECUTED] Anda mendapatkan +1 Free Reroll!\n";
    }
};