#include "BountyHunterJoker.h"
#include <iostream>

std::string BountyHunterJoker::getModifierName() const { return "Bounty Hunter Joker"; }

bool BountyHunterJoker::canActivate(const ScorePayload& payload) const {
    return payload.handRankName == "Two Pair";
}

void BountyHunterJoker::applyEffect(ScorePayload& payload) {
    payload.baseScore += 150;
    std::cout << "  -> [BOUNTY HUNTER] +150 Base Score (Kombinasi Two Pair)\n";
}