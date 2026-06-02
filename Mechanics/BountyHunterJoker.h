#pragma once
#include "Modifier.h"

class BountyHunterJoker : public Modifier {
public:
    std::string getModifierName() const override;
    bool canActivate(const ScorePayload& payload) const override;
    void applyEffect(ScorePayload& payload) override;
};