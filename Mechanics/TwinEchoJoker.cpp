#include "TwinEchoJoker.h"
#include <iostream>

std::string TwinEchoJoker::getModifierName() const { return "Twin Echo Joker"; }

bool TwinEchoJoker::canActivate(const ScorePayload& payload) const {
    return payload.handRankName == "Two Pair"; 
}

void TwinEchoJoker::applyEffect(ScorePayload& payload) {
    payload.multiplier += 10;
    std::cout << "  -> [TWIN ECHO] +10 Mult (Kombinasi Two Pair)\n";
}