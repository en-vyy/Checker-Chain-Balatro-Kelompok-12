#pragma once
#include <vector>
#include <memory>
#include "Modifier.h"
#include "ScorePayload.h"

class ModifierManager {
private:
    std::vector<std::unique_ptr<Modifier>> activeModifiers;

public:
    void addModifier(std::unique_ptr<Modifier> modifier);
    void applyAllModifiers(ScorePayload& payload);
};