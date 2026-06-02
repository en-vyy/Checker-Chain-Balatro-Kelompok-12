#pragma once
#include <string>
#include "ScorePayload.h"

class Modifier {
public:
    virtual ~Modifier() = default;
    virtual std::string getModifierName() const = 0;
    virtual bool canActivate(const ScorePayload& payload) const = 0;
    virtual void applyEffect(ScorePayload& payload) = 0; 
};