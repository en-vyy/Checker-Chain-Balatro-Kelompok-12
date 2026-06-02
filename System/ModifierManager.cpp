#include "ModifierManager.h"
#include <iostream>

void ModifierManager::addModifier(std::unique_ptr<Modifier> modifier) {
    activeModifiers.push_back(std::move(modifier));
}

void ModifierManager::applyAllModifiers(ScorePayload& payload) {
    for (auto& mod : activeModifiers) {
        if (mod->canActivate(payload)) {
            mod->applyEffect(payload);
            std::cout << "[MODIFIER AKTIF] " << mod->getModifierName() << " bekerja!\n";
        }
    }
}