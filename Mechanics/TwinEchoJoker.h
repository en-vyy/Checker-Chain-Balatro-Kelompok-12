#pragma once
#include "Modifier.h"

class TwinEchoJoker : public Modifier {
public:
    std::string getModifierName() const override;
    bool canActivate(const ScorePayload& payload) const override;
    void applyEffect(ScorePayload& payload) override;
};