#pragma once
#include "RunSessionState.h" 
#include <iostream>

class RewardCommand {
public:
    virtual ~RewardCommand() = default; 
    virtual void execute(RunSessionState& state) = 0;
};

// TAG 1: Handy Tag
class HandyTagCommand : public RewardCommand {
public:
    void execute(RunSessionState& state) override {
        int bonus = state.totalPlayedHands * 1;
        state.money += bonus;
        std::cout << "[TAG EXECUTED] Handy Tag! Anda mendapat $" << bonus 
                  << " (" << state.totalPlayedHands << " kartu telah dimainkan di run ini).\n";
    }
};

// TAG 2: Investment Tag
class InvestmentTagCommand : public RewardCommand {
public:
    void execute(RunSessionState& state) override {
        state.hasInvestmentTag = true;
        std::cout << "[TAG EXECUTED] Investment Tag aktif! Anda akan mendapat $25 setelah mengalahkan Boss Blind selanjutnya.\n";
    }
};