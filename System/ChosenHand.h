#pragma once
#include <iostream>
#include "Hand.h" // Wajib include induknya

class ChosenHand : public Hand {
public:
    void addChosenCard(Card card) {
        cards.push_back(card);
    }

    void showChosenCards() const {
        std::cout << "Player plays selected cards: \n";
        for (const auto& c : cards) {
            std::cout << "[" << c.rank << c.suit << "] ";
        }
        std::cout << "\n";
    }
};